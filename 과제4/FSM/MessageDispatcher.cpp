// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#include <cassert>

#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityManager.h"
#include "Log.h"
#include "CrudeTimer.h"

MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;
	return &instance;
}

void MessageDispatcher::DispatchMessageEx(double delay, int sender, int receiver, int msg, void* extraInfo)
{
	BaseEntity* pSender = EntityMgr->GetEntityFromID(sender);
	BaseEntity* pReceiver = EntityMgr->GetEntityFromID(receiver);

	assert(pReceiver && "Error. No receiver.");

	Telegram telegram(0, sender, receiver, msg, extraInfo);

	if (delay <= 0.0f)
	{
		LOG("{0}이(가) {1}에게 즉석 전보 발송. 메세지는 {2}. 발송 시간({3})", EntityMgr->GetNameOfEntity(sender),
			EntityMgr->GetNameOfEntity(receiver), MsgToStr(msg), Timer->GetCurrentTime());

		Discharge(pReceiver, telegram);
	}

	else
	{
		double currentTime = Timer->GetCurrentTime();
		telegram.DispatchTime = currentTime + delay;
		mMsgQueue.insert(telegram);
		
		LOG("{0}을 위해 시간({1})에 기록된 {2}로부터 지연된 전보. 메세지는 {3}", EntityMgr->GetNameOfEntity(receiver),
			Timer->GetCurrentTime(), EntityMgr->GetNameOfEntity(sender), MsgToStr(msg));
	}
}

void MessageDispatcher::Update()
{
	double currentTime = Timer->GetCurrentTime();

	while (!mMsgQueue.empty() &&
		mMsgQueue.begin()->DispatchTime < currentTime &&
		mMsgQueue.begin()->DispatchTime > 0)
	{
		const Telegram& telegram = *mMsgQueue.begin();

		BaseEntity* receiver = EntityMgr->GetEntityFromID(telegram.Receiver);

		LOG("발송 준비된 대기 전보: {0}에게 보내짐. 메세지는 {1}",
			EntityMgr->GetNameOfEntity(telegram.Receiver),
			MsgToStr(telegram.Msg));

		Discharge(receiver, telegram);
		mMsgQueue.erase(mMsgQueue.begin());
	}
}

void MessageDispatcher::Discharge(BaseEntity* receiver, const Telegram& telegram)
{
	if (!receiver->IsMessageHandled(telegram))
	{
		LOG("메세지가 처리되지 않았음.");
	}
}
