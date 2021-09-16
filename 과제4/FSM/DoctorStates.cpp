// ***********************************************
// **            �ΰ����� ����4. FSM				**
// **            2016180007����               **
// ***********************************************

#include "DoctorStates.h"

#include "Log.h"
#include "Doctor.h"
#include "MessageTypes.h"
#include "EntityManager.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "Random.h"

DoctorGlobalState* DoctorGlobalState::Instance()
{
	static DoctorGlobalState instance;
	return &instance;
}

bool DoctorGlobalState::OnMessage(Doctor* doctor, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgHelpMeDoctor:
		LOG("{0}��(��) �ð�({1})�� ������ �޽���",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		doctor->GetFSM()->ChangeState(TreatPatient::Instance());
		
		return true;

	default:
		return false;
	}
}

TreatPatient* TreatPatient::Instance()
{
	static TreatPatient instance;
	return &instance;
}

void TreatPatient::Enter(Doctor* doctor)
{
	DR_LOG("{0} ��, ����Ƿ� ���ô�.", EntityMgr->GetNameOfEntity(eEntityID::MinerBob));
}

void TreatPatient::Execute(Doctor* doctor)
{
	DR_LOG("���°� ������ �ʳ׿�. �Ϸ�� ���� �̴ϴ�.");
	Dispatcher->DispatchMessageEx(0, doctor->GetID(), eEntityID::MinerBob, MsgNowYouAreOkay);
	doctor->GetFSM()->RevertToPreviousState();
}

void TreatPatient::Exit(Doctor* doctor)
{
	DR_LOG("ġ�ᰡ �������ϴ�. �൵ �� �޾ư�����.");
}

bool TreatPatient::OnMessage(Doctor* doctor, const Telegram& msg)
{
	return false;
}

WritePaper* WritePaper::Instance()
{
	static WritePaper instance;
	return &instance;
}

void WritePaper::Enter(Doctor* doctor)
{

}

void WritePaper::Execute(Doctor* doctor)
{
	DR_LOG("���� ���� ���� �� ��̷ο�.");

	if (Random::RandFloat() < 0.5f)
	{
		doctor->GetFSM()->ChangeState(ReadBook::Instance());
	}
}

void WritePaper::Exit(Doctor* doctor)
{
	DR_LOG("���� ������ ���� ��߰ھ�.");
}

bool WritePaper::OnMessage(Doctor* doctor, const Telegram& msg)
{
	return false;
}

ReadBook* ReadBook::Instance()
{
	static ReadBook instance;
	return &instance;
}

void ReadBook::Enter(Doctor* doctor)
{
	DR_LOG("�Ѱ��ϴ� å�̳� �� �о��.");
}

void ReadBook::Execute(Doctor* doctor)
{
	DR_LOG("å�� ��̷ο�. ¥����. �� ���ο�.");

	if (Random::RandFloat() < 0.5f)
	{
		doctor->GetFSM()->ChangeState(WritePaper::Instance());
	}
}

void ReadBook::Exit(Doctor* doctor)
{
	DR_LOG("å�� �������.");
}

bool ReadBook::OnMessage(Doctor* doctor, const Telegram& msg)
{
	return false;
}
