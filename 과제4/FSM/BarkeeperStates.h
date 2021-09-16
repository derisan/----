#pragma once

#include "State.h"

class Barkeeper;

class BarkeeperGlobalState : public State<Barkeeper>
{
public:
	static BarkeeperGlobalState* Instance();

	virtual void Enter(Barkeeper* barkeeper) override {};
	virtual void Execute(Barkeeper* barkeeper) override;
	virtual void Exit(Barkeeper* barkeeper) override {};
	virtual bool OnMessage(Barkeeper* barkeeper, const Telegram& msg) override;

	BarkeeperGlobalState(const BarkeeperGlobalState&) = delete;
	BarkeeperGlobalState& operator=(const BarkeeperGlobalState&) = delete;

private:
	BarkeeperGlobalState() = default;
};

class CleanUpShop : public State<Barkeeper>
{
public:
	static CleanUpShop* Instance();

	virtual void Enter(Barkeeper* barkeeper) override;
	virtual void Execute(Barkeeper* barkeeper) override;
	virtual void Exit(Barkeeper* barkeeper) override;
	virtual bool OnMessage(Barkeeper* barkeeper, const Telegram& msg) override;

	CleanUpShop(const CleanUpShop&) = delete;
	CleanUpShop& operator=(const CleanUpShop&) = delete;

private:
	CleanUpShop() = default;
};

class MakeCocktail : public State<Barkeeper>
{
public:
	static MakeCocktail* Instance();

	virtual void Enter(Barkeeper* barkeeper) override;
	virtual void Execute(Barkeeper* barkeeper) override;
	virtual void Exit(Barkeeper* barkeeper) override;
	virtual bool OnMessage(Barkeeper* barkeeper, const Telegram& msg) override;

	MakeCocktail(const MakeCocktail&) = delete;
	MakeCocktail& operator=(const MakeCocktail&) = delete;

private:
	MakeCocktail() = default;
};

class GoBank : public State<Barkeeper>
{
public:
	static GoBank* Instance();

	virtual void Enter(Barkeeper* barkeeper) override;
	virtual void Execute(Barkeeper* barkeeper) override;
	virtual void Exit(Barkeeper* barkeeper) override;
	virtual bool OnMessage(Barkeeper* barkeeper, const Telegram& msg) override;

	GoBank(const GoBank&) = delete;
	GoBank& operator=(const GoBank&) = delete;

private:
	GoBank() = default;
};

class TakeLiquor : public State<Barkeeper>
{
public:
	static TakeLiquor* Instance();

	virtual void Enter(Barkeeper* barkeeper) override;
	virtual void Execute(Barkeeper* barkeeper) override;
	virtual void Exit(Barkeeper* barkeeper) override;
	virtual bool OnMessage(Barkeeper* barkeeper, const Telegram& msg) override;

	TakeLiquor(const TakeLiquor&) = delete;
	TakeLiquor& operator=(const TakeLiquor&) = delete;

private:
	TakeLiquor() = default;
};