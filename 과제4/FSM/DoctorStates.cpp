#include "DoctorStates.h"

#include "Log.h"
#include "Doctor.h"
#include "MessageTypes.h"
#include "EntityManager.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"

DoctorGlobalState* DoctorGlobalState::Instance()
{
	static DoctorGlobalState instance;
	return &instance;
}

void DoctorGlobalState::Enter(Doctor* doctor)
{

}

void DoctorGlobalState::Execute(Doctor* doctor)
{
	if (doctor->IsPatientWaiting())
	{
		doctor->GetFSM()->ChangeState(TreatPatient::Instance());
	}
}

void DoctorGlobalState::Exit(Doctor* doctor)
{

}

bool DoctorGlobalState::OnMessage(Doctor* doctor, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgHelpMeDoctor:
		LOG("{0}��(��) �ð�({1})�� ������ �޽���",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		if (doctor->IsBusy())
		{
			DR_LOG("{0} ��, ���� ȯ�ڸ� ������ ���̴� ��ø� ��ٷ��ֽʽÿ�.", EntityMgr->GetNameOfEntity(msg.Sender));
			doctor->AddPatient(msg.Sender);
		}
		else
		{
			doctor->GetFSM()->ChangeState(TreatPatient::Instance());
		}
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
	DR_LOG("{0} ��, ����Ƿ� ���ô�.", EntityMgr->GetNameOfEntity(doctor->GetFirstPatientID()));
}

void TreatPatient::Execute(Doctor* doctor)
{
	DR_LOG("���°� ������ �ʳ׿�. �Ϸ�� ���� �̴ϴ�.");
	Dispatcher->DispatchMessageEx(0, doctor->GetID(), doctor->GetFirstPatientID(), MsgNowYouAreOkay);
	doctor->RemovePatient();
	doctor->GetFSM()->RevertToPreviousState();
}

void TreatPatient::Exit(Doctor* doctor)
{
	DR_LOG("������ �����뿡 ���� ���ּ���. �൵ �޾ư��ð��.");
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
	DR_LOG("ȯ�ڵ� ������ �̷�״� ���� ��߰ڱ�!");
}

void WritePaper::Execute(Doctor* doctor)
{
	DR_LOG("���� ���� ���� �� ��̷ο�.");
}

void WritePaper::Exit(Doctor* doctor)
{
	DR_LOG("ȯ�ڰ� �Ա�. ���� ������ ���� ��߰ھ�.");
}

bool WritePaper::OnMessage(Doctor* doctor, const Telegram& msg)
{
	return false;
}
