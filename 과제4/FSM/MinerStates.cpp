// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
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
		MINER_LOG("금광으로 걸어간다.");
		miner->SetLocation(eLocation::Goldmine);
	}
}

void EnterMineAndDigForNugget::Execute(Miner* miner)
{
	miner->AddToGoldCarried(1);
	miner->IncreaseFatigue();
	MINER_LOG("금덩어리를 집는다.");

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
	MINER_LOG("금광을 떠난다.");
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
		MINER_LOG("피곤이 싹 달아나 버렸네! 금을 더 캐야 할 시간이다.");
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
	
}

bool GoHomeAndSleepTillRested::OnMessage(Miner* miner, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgStewReady:
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		MINER_LOG("좋아요 여보, 내 곧 가리다!");
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
	MINER_LOG("냄새 정말 좋구려, {0}", EntityMgr->GetNameOfEntity(eEntityID::HousewifeElsa));
}

void EatStew::Execute(Miner* miner)
{
	MINER_LOG("맛도 정말 좋군!");
	miner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* miner)
{
	MINER_LOG("고마워 여보. 하던 일을 다시 하는 것이 좋겠군.");
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
	MINER_LOG("병원에서 진료를 받는 중이다.");
}

void OhImSick::Exit(Miner* miner)
{
	MINER_LOG("감사합니다. 의사 선생님!");
}

bool OhImSick::OnMessage(Miner* miner, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgNowYouAreOkay:
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		miner->GetFSM()->RevertToPreviousState();

		return true;

	default:
		return false;
	}
}
