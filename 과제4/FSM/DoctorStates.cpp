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
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
			EntityMgr->GetNameOfEntity(msg.Receiver),
			Timer->GetCurrentTime());

		if (doctor->IsBusy())
		{
			DR_LOG("{0} 씨, 지금 환자를 돌보는 중이니 잠시만 기다려주십시오.", EntityMgr->GetNameOfEntity(msg.Sender));
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
	DR_LOG("{0} 씨, 진료실로 갑시다.", EntityMgr->GetNameOfEntity(doctor->GetFirstPatientID()));
}

void TreatPatient::Execute(Doctor* doctor)
{
	DR_LOG("상태가 나쁘지 않네요. 하루면 나을 겁니다.");
	Dispatcher->DispatchMessageEx(0, doctor->GetID(), doctor->GetFirstPatientID(), MsgNowYouAreOkay);
	doctor->RemovePatient();
	doctor->GetFSM()->RevertToPreviousState();
}

void TreatPatient::Exit(Doctor* doctor)
{
	DR_LOG("수납은 접수대에 가서 해주세요. 약도 받아가시고요.");
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
	DR_LOG("환자도 없으니 미뤄뒀던 논문을 써야겠군!");
}

void WritePaper::Execute(Doctor* doctor)
{
	DR_LOG("역시 논문을 쓰는 건 흥미로워.");
}

void WritePaper::Exit(Doctor* doctor)
{
	DR_LOG("환자가 왔군. 논문은 다음에 마저 써야겠어.");
}

bool WritePaper::OnMessage(Doctor* doctor, const Telegram& msg)
{
	return false;
}
