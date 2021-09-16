// ***********************************************
// **            �ΰ����� ����4. FSM				**
// **            2016180007����               **
// ***********************************************

#include "MinerStates.h"

#include "CrudeTimer.h"
#include "Log.h"
#include "Miner.h"
#include "MessageTypes.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "Random.h"

EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
	static EnterMineAndDigForNugget instance;
	return &instance;
}

void EnterMineAndDigForNugget::Enter(Miner* miner)
{
	if (miner->GetLocation() != eLocation::Goldmine)
	{
		MINER_LOG("�ݱ����� �ɾ��.");
		miner->SetLocation(eLocation::Goldmine);
	}
}

void EnterMineAndDigForNugget::Execute(Miner* miner)
{
	miner->AddToGoldCarried(1);
	miner->IncreaseFatigue();
	MINER_LOG("�ݵ���� ���´�.");

	if (Random::RandFloat() < 0.2f)
	{
		miner->GetFSM()->ChangeState(OhImSick::Instance());
	}

	else if (miner->IsPocketsFull())
	{
		miner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
	}

	else if (miner->IsThirsty())
	{
		miner->GetFSM()->ChangeState(QuenchThirst::Instance());
	}
}

void EnterMineAndDigForNugget::Exit(Miner* miner)
{
	MINER_LOG("�ݱ��� ������.");
}

bool EnterMineAndDigForNugget::OnMessage(Miner* miner, const Telegram& msg)
{
	return false;
}

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;
	return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* miner)
{
	if (miner->GetLocation() != eLocation::Bank)
	{
		MINER_LOG("�������� ����. �� ����.");

		miner->SetLocation(eLocation::Bank);
	}
}

void VisitBankAndDepositGold::Execute(Miner* miner)
{
	miner->AddToMoneyInBank(miner->GetGoldCarried());
	miner->SetGoldCarried(0);

	MINER_LOG("���� �ñ��. �� ���෮�� ���� {0}�̴�.", miner->GetMoneyInBank());

	if (miner->IsWealthy())
	{
		MINER_LOG("��ȿ! ���� ����� ���ڰ� �Ǿ���. ���� �Ϳ��� �Ƴ����Է� ���ư���.");
		miner->GetFSM()->ChangeState(GoHomeAndSleepTillRested::Instance());
	}
	else
	{
		miner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}

void VisitBankAndDepositGold::Exit(Miner* miner)
{
	MINER_LOG("������ ������.");
}

bool VisitBankAndDepositGold::OnMessage(Miner* miner, const Telegram& msg)
{
	return false;
}

GoHomeAndSleepTillRested* GoHomeAndSleepTillRested::Instance()
{
	static GoHomeAndSleepTillRested instance;
	return &instance;
}

void GoHomeAndSleepTillRested::Enter(Miner* miner)
{
	if (miner->GetLocation() != eLocation::Shack)
	{
		miner->SetLocation(eLocation::Shack);
		
		Dispatcher->DispatchMessageEx(0.0f,
			miner->GetID(),
			eEntityID::HousewifeElsa,
			MsgHiHoneyImHome);
	}
}

void GoHomeAndSleepTillRested::Execute(Miner* miner)
{
	if (!miner->IsFatigued())
	{
		MINER_LOG("�ǰ��� �� �޾Ƴ� ���ȳ�! ���� �� ĳ�� �� �ð��̴�.");
		miner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else
	{
		miner->DecreaseFatigue();
		MINER_LOG("����...");
	}
}

void GoHomeAndSleepTillRested::Exit(Miner* miner)
{
	
}

bool GoHomeAndSleepTillRested::OnMessage(Miner* miner, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgStewReady:
		LOG("{0}��(��) �ð�({1})�� ������ �޽���",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		MINER_LOG("���ƿ� ����, �� �� ������!");
		miner->GetFSM()->ChangeState(EatStew::Instance());

		return true;

	default:
		return false;
	}
}

QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Miner* miner)
{
	if (miner->GetLocation() != eLocation::Saloon)
	{
		miner->SetLocation(eLocation::Saloon);
		MINER_LOG("���� ������! �������� �ɾ��.");
	}
}

void QuenchThirst::Execute(Miner* miner)
{
	if (miner->IsThirsty())
	{
		miner->BuyAndDrinkWhiskey();
		MINER_LOG("���� Ȧ¦Ȧ¦ ���ñ⿡ ����� ���� ���̱�.");
		miner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}

	else
	{
		MINER_LOG("����! ����! ����!");
	}
}

void QuenchThirst::Exit(Miner* miner)
{
	MINER_LOG("������ ������. ��е� ����.");
}

bool QuenchThirst::OnMessage(Miner* miner, const Telegram& msg)
{
	return false;
}

EatStew* EatStew::Instance()
{
	static EatStew instance;
	return &instance;
}

void EatStew::Enter(Miner* miner)
{
	MINER_LOG("���� ���� ������, {0}", EntityMgr->GetNameOfEntity(eEntityID::HousewifeElsa));
}

void EatStew::Execute(Miner* miner)
{
	MINER_LOG("���� ���� ����!");
	miner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* miner)
{
	MINER_LOG("���� ����. �ϴ� ���� �ٽ� �ϴ� ���� ���ڱ�.");
}

bool EatStew::OnMessage(Miner* miner, const Telegram& msg)
{
	return false;
}

OhImSick* OhImSick::Instance()
{
	static OhImSick instance;
	return &instance;
}

void OhImSick::Enter(Miner* miner)
{
	Dispatcher->DispatchMessageEx(0, miner->GetID(), eEntityID::DoctorSmith, MsgHelpMeDoctor);
}

void OhImSick::Execute(Miner* miner)
{
	MINER_LOG("�������� ���Ḧ �޴� ���̴�.");
}

void OhImSick::Exit(Miner* miner)
{
	MINER_LOG("�����մϴ�. �ǻ� ������!");
}

bool OhImSick::OnMessage(Miner* miner, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgNowYouAreOkay:
		LOG("{0}��(��) �ð�({1})�� ������ �޽���",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		miner->GetFSM()->RevertToPreviousState();

		return true;

	default:
		return false;
	}
}
