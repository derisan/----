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
		MINER_LOG("금광으로 걸어간다.");
		miner->SetLocation(eLocation::Goldmine);
	}
}

void EnterMineAndDigForNugget::Execute(Miner* miner)
{
	miner->AddToGoldCarried(1);
	miner->IncreaseFatigue();
	MINER_LOG("금덩어리를 집는다.");

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
	MINER_LOG("금광을 떠난다.");
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
		MINER_LOG("은행으로 간다. 네 고객님.");

		miner->SetLocation(eLocation::Bank);
	}
}

void VisitBankAndDepositGold::Execute(Miner* miner)
{
	miner->AddToMoneyInBank(miner->GetGoldCarried());
	miner->SetGoldCarried(0);

	MINER_LOG("금을 맡긴다. 총 저축량은 이제 {0}이다.", miner->GetMoneyInBank());

	if (miner->IsWealthy())
	{
		MINER_LOG("우효! 이제 충분히 부자가 되었다. 나의 귀여운 아내에게로 돌아가자.");
		miner->GetFSM()->ChangeState(GoHomeAndSleepTillRested::Instance());
	}
	else
	{
		miner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}

void VisitBankAndDepositGold::Exit(Miner* miner)
{
	MINER_LOG("은행을 떠난다.");
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
		MINER_LOG("집으로 걸어간다.");
	}
}

void GoHomeAndSleepTillRested::Execute(Miner* miner)
{
	if (!miner->IsFatigued())
	{
		MINER_LOG("정말 환상적인 낮잠이었구나! 금을 더 캐야 할 시간이다.");
		miner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else
	{
		miner->DecreaseFatigue();
		MINER_LOG("쿨쿨...");
	}
}

void GoHomeAndSleepTillRested::Exit(Miner* miner)
{
	MINER_LOG("집을 떠난다.");
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
		MINER_LOG("목이 마르군! 술집으로 걸어간다.");
	}
}

void QuenchThirst::Execute(Miner* miner)
{
	if (miner->IsThirsty())
	{
		miner->BuyAndDrinkWhiskey();
		MINER_LOG("저게 홀짝홀짝 마시기에 대단히 좋은 술이군.");
		miner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}

	else
	{
		MINER_LOG("오류! 오류! 오류!");
	}
}

void QuenchThirst::Exit(Miner* miner)
{
	MINER_LOG("술집을 떠난다. 기분도 좋다.");
}