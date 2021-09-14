#include <cassert>

#include "HousewifeStates.h"
#include "Log.h"
#include "Housewife.h"
#include "Random.h"
#include "MessageTypes.h"
#include "EntityManager.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"

WifeGlobalState* WifeGlobalState::Instance()
{
	static WifeGlobalState instance;
	return &instance;
}

void WifeGlobalState::Enter(Housewife* wife)
{

}

void WifeGlobalState::Execute(Housewife* wife)
{
	if (Random::RandFloat() < 0.1f && 
		!wife->GetFSM()->IsInState(*VisitBathroom::Instance()))
	{
		wife->GetFSM()->ChangeState(VisitBathroom::Instance());
	}
}

void WifeGlobalState::Exit(Housewife* wife)
{

}

bool WifeGlobalState::OnMessage(Housewife* wife, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgHiHoneyImHome:
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		HW_LOG("여보, 맛있는 시골식 국을 만들어 드릴게요.");
		wife->GetFSM()->ChangeState(CookStew::Instance());
		return true;

	default:
		return false;
	}
}

DoHouseWork* DoHouseWork::Instance()
{
	static DoHouseWork instance;
	return &instance;
}

void DoHouseWork::Enter(Housewife* wife)
{
	HW_LOG("집안일을 좀더 할 시간이군!");
}

void DoHouseWork::Execute(Housewife* wife)
{
	switch (Random::RandInt(0, 2))
	{
	case 0:
		HW_LOG("바닥을 닦는다.");
		break;

	case 1:
		HW_LOG("설거지를 한다.");
		break;

	case 2:
		HW_LOG("잠자리를 준비한다.");
		break;

	default:
		assert(nullptr && "ERROR! Unknown number.");
	}
}

void DoHouseWork::Exit(Housewife* wife)
{

}

bool DoHouseWork::OnMessage(Housewife* wife, const Telegram& msg)
{
	return false;
}

VisitBathroom* VisitBathroom::Instance()
{
	static VisitBathroom instance;
	return &instance;
}

void VisitBathroom::Enter(Housewife* wife)
{
	HW_LOG("화장실로 걸어간다. 깨긋이 소변을 봐야겠다.");
}

void VisitBathroom::Execute(Housewife* wife)
{
	HW_LOG("아! 시원하다!");
	wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(Housewife* wife)
{
	HW_LOG("화장실에서 나온다.");
}

bool VisitBathroom::OnMessage(Housewife* wife, const Telegram& msg)
{
	return false;
}

CookStew* CookStew::Instance()
{
	static CookStew instance;
	return &instance;
}

void CookStew::Enter(Housewife* wife)
{
	if (!wife->IsCooking())
	{
		HW_LOG("국을 오븐에 넣는다.");

		Dispatcher->DispatchMessageEx(1.5,
			wife->GetID(),
			wife->GetID(),
			MsgStewReady);

		wife->SetCooking(true);
	}
}

void CookStew::Execute(Housewife* wife)
{
	HW_LOG("저녁밥을 차리느라 부산을 떤다.");
}

void CookStew::Exit(Housewife* wife)
{
	HW_LOG("식탁 위에 국을 올려 놓는다.");
}

bool CookStew::OnMessage(Housewife* wife, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgStewReady:
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		HW_LOG("국이 준비됐군요! 듭시다.");

		Dispatcher->DispatchMessageEx(0.0f, wife->GetID(), eEntityID::MinerBob,
			MsgStewReady);

		wife->SetCooking(false);
		wife->GetFSM()->ChangeState(DoHouseWork::Instance());

		return true;

	default:
		return false;
	}
}
