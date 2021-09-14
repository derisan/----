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
