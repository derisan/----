#include <cassert>

#include "HousewifeStates.h"
#include "Log.h"
#include "Housewife.h"
#include "Random.h"

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
	if (Random::RandFloat() < 0.1f)
	{
		wife->GetFSM()->ChangeState(VisitBathroom::Instance());
	}
}

void WifeGlobalState::Exit(Housewife* wife)
{

}

DoHouseWork* DoHouseWork::Instance()
{
	static DoHouseWork instance;
	return &instance;
}

void DoHouseWork::Enter(Housewife* wife)
{

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
