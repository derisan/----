#pragma once

#include "State.h"

class Housewife;

class WifeGlobalState : public State<Housewife>
{
public:
	static WifeGlobalState* Instance();

	virtual void Enter(Housewife* wife) override;
	virtual void Execute(Housewife* wife) override;
	virtual void Exit(Housewife* wife) override;
	virtual bool OnMessage(Housewife* wife, const Telegram& msg) override;

	WifeGlobalState(const WifeGlobalState&) = delete;
	WifeGlobalState& operator=(const WifeGlobalState&) = delete;

private:
	WifeGlobalState() = default;
};

class DoHouseWork : public State<Housewife>
{
public:
	static DoHouseWork* Instance();

	virtual void Enter(Housewife* wife) override;
	virtual void Execute(Housewife* wife) override;
	virtual void Exit(Housewife* wife) override;
	virtual bool OnMessage(Housewife* wife, const Telegram& msg) override;

	DoHouseWork(const DoHouseWork&) = delete;
	DoHouseWork& operator=(const DoHouseWork&) = delete;

private:
	DoHouseWork() = default;
};

class VisitBathroom : public State<Housewife>
{
public:
	static VisitBathroom* Instance();

	virtual void Enter(Housewife* wife) override;
	virtual void Execute(Housewife* wife) override;
	virtual void Exit(Housewife* wife) override;
	virtual bool OnMessage(Housewife* wife, const Telegram& msg) override;

	VisitBathroom(const VisitBathroom&) = delete;
	VisitBathroom& operator=(const VisitBathroom&) = delete;

private:
	VisitBathroom() = default;
};

class CookStew : public State<Housewife>
{
public:
	static CookStew* Instance();

	virtual void Enter(Housewife* wife) override;
	virtual void Execute(Housewife* wife) override;
	virtual void Exit(Housewife* wife) override;
	virtual bool OnMessage(Housewife* wife, const Telegram& msg) override;

	CookStew(const CookStew&) = delete;
	CookStew& operator=(const CookStew&) = delete;

private:
	CookStew() = default;
};