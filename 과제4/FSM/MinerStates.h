#pragma once

#include "State.h"

class Miner;

class EnterMineAndDigForNugget : public State<Miner>
{
public:
	static EnterMineAndDigForNugget* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
	virtual bool OnMessage(Miner* miner, const Telegram& msg) override;

	EnterMineAndDigForNugget(const EnterMineAndDigForNugget&) = delete;
	EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&) = delete;

private:
	EnterMineAndDigForNugget() = default;
};

class VisitBankAndDepositGold : public State<Miner>
{
public:
	static VisitBankAndDepositGold* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
	virtual bool OnMessage(Miner* miner, const Telegram& msg) override;

	VisitBankAndDepositGold(const VisitBankAndDepositGold&) = delete;
	VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&) = delete;

private:
	VisitBankAndDepositGold() = default;
};

class GoHomeAndSleepTillRested : public State<Miner>
{
public:
	static GoHomeAndSleepTillRested* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
	virtual bool OnMessage(Miner* miner, const Telegram& msg) override;

	GoHomeAndSleepTillRested(const GoHomeAndSleepTillRested&) = delete;
	GoHomeAndSleepTillRested& operator=(const GoHomeAndSleepTillRested&) = delete;

private:
	GoHomeAndSleepTillRested() = default;
};

class QuenchThirst : public State<Miner>
{
public:
	static QuenchThirst* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
	virtual bool OnMessage(Miner* miner, const Telegram& msg) override;

	QuenchThirst(const QuenchThirst&) = delete;
	QuenchThirst& operator=(const QuenchThirst&) = delete;

private:
	QuenchThirst() = default;
};

class EatStew : public State<Miner>
{
public:
	static EatStew* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
	virtual bool OnMessage(Miner* miner, const Telegram& msg) override;

	EatStew(const EatStew&) = delete;
	EatStew& operator=(const EatStew&) = delete;

private:
	EatStew() = default;
};
