// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#pragma once

#include "State.h"

class Teller;

class TellerGlobalState : public State<Teller>
{
public:
	static TellerGlobalState* Instance();

	virtual void Enter(Teller* teller) override {};
	virtual void Execute(Teller* teller) override;
	virtual void Exit(Teller* teller) override {};
	virtual bool OnMessage(Teller* teller, const Telegram& msg) override;

	TellerGlobalState(const TellerGlobalState&) = delete;
	TellerGlobalState& operator=(const TellerGlobalState&) = delete;

private:
	TellerGlobalState() = default;
};

class DoBankingWork : public State<Teller>
{
public:
	static DoBankingWork* Instance();

	virtual void Enter(Teller* teller) override;
	virtual void Execute(Teller* teller) override;
	virtual void Exit(Teller* teller) override;
	virtual bool OnMessage(Teller* teller, const Telegram& msg) override;

	DoBankingWork(const DoBankingWork&) = delete;
	DoBankingWork& operator=(const DoBankingWork&) = delete;

private:
	DoBankingWork() = default;
};

class HaveTeaTime : public State<Teller>
{
public:
	static HaveTeaTime* Instance();

	virtual void Enter(Teller* teller) override;
	virtual void Execute(Teller* teller) override;
	virtual void Exit(Teller* teller) override;
	virtual bool OnMessage(Teller* teller, const Telegram& msg) override;

	HaveTeaTime(const HaveTeaTime&) = delete;
	HaveTeaTime& operator=(const HaveTeaTime&) = delete;

private:
	HaveTeaTime() = default;
};

class OrganizeDocuments : public State<Teller>
{
public:
	static OrganizeDocuments* Instance();

	virtual void Enter(Teller* teller) override;
	virtual void Execute(Teller* teller) override;
	virtual void Exit(Teller* teller) override;
	virtual bool OnMessage(Teller* teller, const Telegram& msg) override;

	OrganizeDocuments(const OrganizeDocuments&) = delete;
	OrganizeDocuments& operator=(const OrganizeDocuments&) = delete;

private:
	OrganizeDocuments() = default;
};