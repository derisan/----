#pragma once

#include "State.h"

class Doctor;

class DoctorGlobalState : public State<Doctor>
{
public:
	static DoctorGlobalState* Instance();

	virtual void Enter(Doctor* doctor) override;
	virtual void Execute(Doctor* doctor) override;
	virtual void Exit(Doctor* doctor) override;
	virtual bool OnMessage(Doctor* doctor, const Telegram& msg) override;

	DoctorGlobalState(const DoctorGlobalState&) = delete;
	DoctorGlobalState& operator=(const DoctorGlobalState&) = delete;

private:
	DoctorGlobalState() = default;
};

class TreatPatient : public State<Doctor>
{
public:
	static TreatPatient* Instance();

	virtual void Enter(Doctor* doctor) override;
	virtual void Execute(Doctor* doctor) override;
	virtual void Exit(Doctor* doctor) override;
	virtual bool OnMessage(Doctor* doctor, const Telegram& msg) override;

	TreatPatient(const TreatPatient&) = delete;
	TreatPatient& operator=(const TreatPatient&) = delete;

private:
	TreatPatient() = default;
};

class WritePaper : public State<Doctor>
{
public:
	static WritePaper* Instance();

	virtual void Enter(Doctor* doctor) override;
	virtual void Execute(Doctor* doctor) override;
	virtual void Exit(Doctor* doctor) override;
	virtual bool OnMessage(Doctor* doctor, const Telegram& msg) override;

	WritePaper(const WritePaper&) = delete;
	WritePaper& operator=(const WritePaper&) = delete;

private:
	WritePaper() = default;
};

