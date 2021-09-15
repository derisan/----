#pragma once

#include <deque>

#include "BaseEntity.h"
#include "StateMachine.h"

class Doctor : public BaseEntity
{
public:
	Doctor(int id);
	virtual ~Doctor();

	virtual void Update() override;
	virtual bool IsMessageHandled(const Telegram& telegram) override;

	bool IsPatientWaiting() const { return !mPatients.empty(); }
	bool IsBusy() const;
	int  GetFirstPatientID() const { return mPatients.front(); }
	void AddPatient(int id) { mPatients.push_back(id); }
	void RemovePatient() { mPatients.pop_front(); }

	StateMachine<Doctor>* GetFSM() const { return mStateMachine; }


private:
	StateMachine<Doctor>* mStateMachine;

	std::deque<int> mPatients;
};

