#include "BarkeeperStates.h"

#include "Barkeeper.h"
#include "Log.h"
#include "MessageTypes.h"
#include "EntityManager.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "Random.h"

BarkeeperGlobalState* BarkeeperGlobalState::Instance()
{
	static BarkeeperGlobalState instance;
	return &instance;
}

void BarkeeperGlobalState::Execute(Barkeeper* barkeeper)
{
	if (Random::RandFloat() < 0.1f && !barkeeper->GetFSM()->IsInState(*TakePill::Instance()))
	{
		barkeeper->GetFSM()->ChangeState(TakePill::Instance());
	}
}

bool BarkeeperGlobalState::OnMessage(Barkeeper* barkeeper, const Telegram& msg)
{
	return false;
}

CleanUpShop* CleanUpShop::Instance()
{
	static CleanUpShop instance;
	return &instance;
}

void CleanUpShop::Enter(Barkeeper* barkeeper)
{
	BK_LOG("힘차게 가게 청소를 시작해볼까!");
}

void CleanUpShop::Execute(Barkeeper* barkeeper)
{
	BK_LOG("가게를 열심히 청소 중이다.");

	if (Random::RandFloat() < 0.5f)
	{
		barkeeper->GetFSM()->ChangeState(MakeCocktail::Instance());
	}
}

void CleanUpShop::Exit(Barkeeper* barkeeper)
{
	BK_LOG("청소를 끝냈다.");
}

bool CleanUpShop::OnMessage(Barkeeper* barkeeper, const Telegram& msg)
{
	return false;
}

MakeCocktail* MakeCocktail::Instance()
{
	static MakeCocktail instance;
	return &instance;
}

void MakeCocktail::Enter(Barkeeper* barkeeper)
{
	BK_LOG("손님이 오셨다.");
	barkeeper->DecreaseStock();
	barkeeper->IncreaseGold();
}

void MakeCocktail::Execute(Barkeeper* barkeeper)
{
	BK_LOG("맛있는 칵테일을 만들었다.");

	if (!barkeeper->IsLiquorEnough())
	{
		barkeeper->GetFSM()->ChangeState(TakeLiquor::Instance());
	}

	else if (barkeeper->IsWealthy())
	{
		barkeeper->GetFSM()->ChangeState(GoBank::Instance());
	}

	else
	{
		barkeeper->GetFSM()->ChangeState(CleanUpShop::Instance());
	}
}

void MakeCocktail::Exit(Barkeeper* barkeeper)
{
	BK_LOG("손님이 나가셨다");
}

bool MakeCocktail::OnMessage(Barkeeper* barkeeper, const Telegram& msg)
{
	return false;
}

GoBank* GoBank::Instance()
{
	static GoBank instance;
	return &instance;
}

void GoBank::Enter(Barkeeper* barkeeper)
{
	if (barkeeper->IsWealthy())
	{
		BK_LOG("많이 팔았다. 은행에 예금하러 가야겠어.");
		
		Dispatcher->DispatchMessageEx(0, barkeeper->GetID(), eEntityID::TellerJane, MsgIWantDeposit);
	}
}

void GoBank::Execute(Barkeeper* barkeeper)
{
	BK_LOG("은행에 사람이 많은 걸. 조금 기다려야겠어.");
}

void GoBank::Exit(Barkeeper* barkeeper)
{
	BK_LOG("은행을 나선다.");
}

bool GoBank::OnMessage(Barkeeper* barkeeper, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgDepositComplete:
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		BK_LOG("예금이 완료되었다.");

		barkeeper->GetFSM()->ChangeState(CleanUpShop::Instance());

		return true;

	default:
		return false;
	}
}

TakeLiquor* TakeLiquor::Instance()
{
	static TakeLiquor instance;
	return &instance;
}

void TakeLiquor::Enter(Barkeeper* barkeeper)
{
	if (!barkeeper->IsLiquorEnough())
	{
		BK_LOG("술이 부족하다. 창고에 왔다.");
	}
}

void TakeLiquor::Execute(Barkeeper* barkeeper)
{
	barkeeper->IncreaseStock();
	BK_LOG("술을 담는다. 현재 재고는 {0}병이다.", barkeeper->GetLiquorStock());

	if (barkeeper->IsLiquorFull())
	{
		barkeeper->GetFSM()->ChangeState(CleanUpShop::Instance());
	}
}

void TakeLiquor::Exit(Barkeeper* barkeeper)
{
	BK_LOG("재고를 가득 채웠다. 창고에서 나간다.");
}

bool TakeLiquor::OnMessage(Barkeeper* barkeeper, const Telegram& msg)
{
	return false;
}

TakePill* TakePill::Instance()
{
	static TakePill instance;
	return &instance;
}

void TakePill::Enter(Barkeeper* barkeeper)
{
	BK_LOG("남는 술을 마셨더니 머리가 아프군.");
}

void TakePill::Execute(Barkeeper* barkeeper)
{
	BK_LOG("숙취 해소엔 역시 상쾌환이지.");
	
	barkeeper->GetFSM()->RevertToPreviousState();
}

void TakePill::Exit(Barkeeper* barkeeper)
{
	BK_LOG("어으~ 개운해.");
}

bool TakePill::OnMessage(Barkeeper* barkeeper, const Telegram& msg)
{
	return false;
}
