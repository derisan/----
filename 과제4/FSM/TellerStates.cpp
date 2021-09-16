#include "TellerStates.h"

#include "Log.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Teller.h"
#include "Random.h"
#include "CrudeTimer.h"
#include "EntityManager.h"

TellerGlobalState* TellerGlobalState::Instance()
{
	static TellerGlobalState instance;
	return &instance;
}

void TellerGlobalState::Execute(Teller* teller)
{
	if (!teller->IsBusy() && Random::RandFloat() < 0.2f)
	{
		teller->GetFSM()->ChangeState(DoBankingWork::Instance());
	}
}

bool TellerGlobalState::OnMessage(Teller* teller, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgIWantDeposit:
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		TELLER_LOG("예금해드리겠습니다. 잠시만 기다려 주십시오, {0}님.", EntityMgr->GetNameOfEntity(msg.Sender));

		Dispatcher->DispatchMessageEx(1.5, teller->GetID(), msg.Sender, MsgDepositComplete);

		return true;

	default:
		return false;
	}
}

DoBankingWork* DoBankingWork::Instance()
{
	static DoBankingWork instance;
	return &instance;
}

void DoBankingWork::Enter(Teller* teller)
{
	if (!teller->IsBusy())
	{
		TELLER_LOG("고객님 1번 창구로 오세요.");

		Dispatcher->DispatchMessageEx(1.5, teller->GetID(), teller->GetID(), MsgDepositComplete);

		teller->SetBusy(true);
	}
}

void DoBankingWork::Execute(Teller* teller)
{
	TELLER_LOG("입금을 진행 중입니다. 잠시만 기다려주세요.");
}

void DoBankingWork::Exit(Teller* teller)
{
	TELLER_LOG("고객님, 안녕히 가십시오.");
}

bool DoBankingWork::OnMessage(Teller* teller, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgDepositComplete:
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		TELLER_LOG("고객님 요청하신 입금이 완료되었습니다!");
		teller->SetBusy(false);
		teller->GetFSM()->ChangeState(OrganizeDocuments::Instance());

		return true;

	default:
		return false;
	}
}

HaveTeaTime* HaveTeaTime::Instance()
{
	static HaveTeaTime instance;
	return &instance;
}

void HaveTeaTime::Enter(Teller* teller)
{
	TELLER_LOG("너무도 기다려온 간식 시간이다!");
}

void HaveTeaTime::Execute(Teller* teller)
{
	if (teller->IsHungry())
	{
		TELLER_LOG("쩝쩝. 과자는 맛있어. 커피도 맛있어.");
		teller->SetHunger(0);
		teller->GetFSM()->ChangeState(OrganizeDocuments::Instance());
	}
}

void HaveTeaTime::Exit(Teller* teller)
{

}

bool HaveTeaTime::OnMessage(Teller* teller, const Telegram& msg)
{
	return false;
}

OrganizeDocuments* OrganizeDocuments::Instance()
{
	static OrganizeDocuments instance;
	return &instance;
}

void OrganizeDocuments::Enter(Teller* teller)
{
	TELLER_LOG("서류 작업을 시작해 볼까.");
}

void OrganizeDocuments::Execute(Teller* teller)
{
	TELLER_LOG("서류가 너무 많아!");

	if (teller->IsHungry())
	{
		teller->GetFSM()->ChangeState(HaveTeaTime::Instance());
	}
}

void OrganizeDocuments::Exit(Teller* teller)
{
	TELLER_LOG("에잇! 서류 작업은 나중에 할래!");
}

bool OrganizeDocuments::OnMessage(Teller* teller, const Telegram& msg)
{
	return false;
}
