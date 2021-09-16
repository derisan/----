// ***********************************************
// **            �ΰ����� ����4. FSM				**
// **            2016180007����               **
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
		LOG("{0}��(��) {1}���� �Ｎ ���� �߼�. �޼����� {2}. �߼� �ð�({3})", EntityMgr->GetNameOfEntity(sender),
			EntityMgr->GetNameOfEntity(receiver), MsgToStr(msg), Timer->GetCurrentTime());

		Discharge(pReceiver, telegram);
	}

	else
	{
		double currentTime = Timer->GetCurrentTime();
		telegram.DispatchTime = currentTime + delay;
		mMsgQueue.insert(telegram);
		
		LOG("{0}�� ���� �ð�({1})�� ��ϵ� {2}�κ��� ������ ����. �޼����� {3}", EntityMgr->GetNameOfEntity(receiver),
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

		LOG("�߼� �غ�� ��� ����: {0}���� ������. �޼����� {1}",
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
		LOG("�޼����� ó������ �ʾ���.");
	}
}
