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
		LOG("{0}��(��) �ð�({1})�� ������ �޽���",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		HW_LOG("����, ���ִ� �ð�� ���� ����� �帱�Կ�.");
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
	HW_LOG("�������� ���� �� �ð��̱�!");
}

void DoHouseWork::Execute(Housewife* wife)
{
	switch (Random::RandInt(0, 2))
	{
	case 0:
		HW_LOG("�ٴ��� �۴´�.");
		break;

	case 1:
		HW_LOG("�������� �Ѵ�.");
		break;

	case 2:
		HW_LOG("���ڸ��� �غ��Ѵ�.");
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
	HW_LOG("ȭ��Ƿ� �ɾ��. ������ �Һ��� ���߰ڴ�.");
}

void VisitBathroom::Execute(Housewife* wife)
{
	HW_LOG("��! �ÿ��ϴ�!");
	wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(Housewife* wife)
{
	HW_LOG("ȭ��ǿ��� ���´�.");
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
		HW_LOG("���� ���쿡 �ִ´�.");

		Dispatcher->DispatchMessageEx(1.5,
			wife->GetID(),
			wife->GetID(),
			MsgStewReady);

		wife->SetCooking(true);
	}
}

void CookStew::Execute(Housewife* wife)
{
	HW_LOG("������� �������� �λ��� ����.");
}

void CookStew::Exit(Housewife* wife)
{
	HW_LOG("��Ź ���� ���� �÷� ���´�.");
}

bool CookStew::OnMessage(Housewife* wife, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgStewReady:
		LOG("{0}��(��) �ð�({1})�� ������ �޽���",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		HW_LOG("���� �غ�Ʊ���! ��ô�.");

		Dispatcher->DispatchMessageEx(0.0f, wife->GetID(), eEntityID::MinerBob,
			MsgStewReady);

		wife->SetCooking(false);
		wife->GetFSM()->ChangeState(DoHouseWork::Instance());

		return true;

	default:
		return false;
	}
}
