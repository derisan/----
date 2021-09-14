#include "MinerStates.h"

#include "Log.h"
#include "Miner.h"

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

	if (miner->IsPocketsFull())
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
		MINER_LOG("������ �ɾ��.");
	}
}

void GoHomeAndSleepTillRested::Execute(Miner* miner)
{
	if (!miner->IsFatigued())
	{
		MINER_LOG("���� ȯ������ �����̾�����! ���� �� ĳ�� �� �ð��̴�.");
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
	MINER_LOG("���� ������.");
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