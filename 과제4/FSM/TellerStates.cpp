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
		LOG("{0}��(��) �ð�({1})�� ������ �޽���",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		TELLER_LOG("�����ص帮�ڽ��ϴ�. ��ø� ��ٷ� �ֽʽÿ�, {0}��.", EntityMgr->GetNameOfEntity(msg.Sender));

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
		TELLER_LOG("���� 1�� â���� ������.");

		Dispatcher->DispatchMessageEx(1.5, teller->GetID(), teller->GetID(), MsgDepositComplete);

		teller->SetBusy(true);
	}
}

void DoBankingWork::Execute(Teller* teller)
{
	TELLER_LOG("�Ա��� ���� ���Դϴ�. ��ø� ��ٷ��ּ���.");
}

void DoBankingWork::Exit(Teller* teller)
{
	TELLER_LOG("����, �ȳ��� ���ʽÿ�.");
}

bool DoBankingWork::OnMessage(Teller* teller, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgDepositComplete:
		LOG("{0}��(��) �ð�({1})�� ������ �޽���",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		TELLER_LOG("���� ��û�Ͻ� �Ա��� �Ϸ�Ǿ����ϴ�!");
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
	TELLER_LOG("�ʹ��� ��ٷ��� ���� �ð��̴�!");
}

void HaveTeaTime::Execute(Teller* teller)
{
	if (teller->IsHungry())
	{
		TELLER_LOG("����. ���ڴ� ���־�. Ŀ�ǵ� ���־�.");
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
	TELLER_LOG("���� �۾��� ������ ����.");
}

void OrganizeDocuments::Execute(Teller* teller)
{
	TELLER_LOG("������ �ʹ� ����!");

	if (teller->IsHungry())
	{
		teller->GetFSM()->ChangeState(HaveTeaTime::Instance());
	}
}

void OrganizeDocuments::Exit(Teller* teller)
{
	TELLER_LOG("����! ���� �۾��� ���߿� �ҷ�!");
}

bool OrganizeDocuments::OnMessage(Teller* teller, const Telegram& msg)
{
	return false;
}
