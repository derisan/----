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
	BK_LOG("������ ���� û�Ҹ� �����غ���!");
}

void CleanUpShop::Execute(Barkeeper* barkeeper)
{
	BK_LOG("���Ը� ������ û�� ���̴�.");

	if (Random::RandFloat() < 0.5f)
	{
		barkeeper->GetFSM()->ChangeState(MakeCocktail::Instance());
	}
}

void CleanUpShop::Exit(Barkeeper* barkeeper)
{
	BK_LOG("û�Ҹ� ���´�.");
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
	BK_LOG("�մ��� ���̴�.");
	barkeeper->DecreaseStock();
	barkeeper->IncreaseGold();
}

void MakeCocktail::Execute(Barkeeper* barkeeper)
{
	BK_LOG("���ִ� Ĭ������ �������.");

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
	BK_LOG("�մ��� �����̴�");
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

}

void GoBank::Execute(Barkeeper* barkeeper)
{

}

void GoBank::Exit(Barkeeper* barkeeper)
{

}

bool GoBank::OnMessage(Barkeeper* barkeeper, const Telegram& msg)
{
	return false;
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
		BK_LOG("���� �����ϴ�. â�� �Դ�.");
	}
}

void TakeLiquor::Execute(Barkeeper* barkeeper)
{
	barkeeper->IncreaseStock();
	BK_LOG("���� ��´�. ���� ���� {0}���̴�.", barkeeper->GetLiquorStock());

	if (barkeeper->IsLiquorFull())
	{
		barkeeper->GetFSM()->ChangeState(CleanUpShop::Instance());
	}
}

void TakeLiquor::Exit(Barkeeper* barkeeper)
{
	BK_LOG("��� ���� ä����. â���� ������.");
}

bool TakeLiquor::OnMessage(Barkeeper* barkeeper, const Telegram& msg)
{
	return false;
}
