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

bool DoctorGlobalState::OnMessage(Doctor* doctor, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case MsgHelpMeDoctor:
		LOG("{0}이(가) 시간({1})에 수신한 메시지",
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
	DR_LOG("{0} 씨, 진료실로 갑시다.", EntityMgr->GetNameOfEntity(eEntityID::MinerBob));
}

void TreatPatient::Execute(Doctor* doctor)
{
	DR_LOG("상태가 나쁘지 않네요. 하루면 나을 겁니다.");
	Dispatcher->DispatchMessageEx(0, doctor->GetID(), eEntityID::MinerBob, MsgNowYouAreOkay);
	doctor->GetFSM()->RevertToPreviousState();
}

void TreatPatient::Exit(Doctor* doctor)
{
	DR_LOG("치료가 끝났습니다. 약도 꼭 받아가세요.");
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
