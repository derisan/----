#pragma once

class Miner;

class State
{
public:
	virtual ~State() = default;

	virtual void Enter(Miner* miner) = 0;
	virtual void Execute(Miner* miner) = 0;
	virtual void Exit(Miner* miner) = 0;
};

class EnterMineAndDigForNugget : public State
{
public:
	static EnterMineAndDigForNugget* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;

	EnterMineAndDigForNugget(const EnterMineAndDigForNugget&) = delete;
	EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&) = delete;

private:
	EnterMineAndDigForNugget() = default;
};

class VisitBankAndDepositGold : public State
{
public:
	static VisitBankAndDepositGold* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;

	VisitBankAndDepositGold(const VisitBankAndDepositGold&) = delete;
	VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&) = delete;

private:
	VisitBankAndDepositGold() = default;
};

class GoHomeAndSleepTillRested : public State
{
public:
	static GoHomeAndSleepTillRested* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;

	GoHomeAndSleepTillRested(const GoHomeAndSleepTillRested&) = delete;
	GoHomeAndSleepTillRested& operator=(const GoHomeAndSleepTillRested&) = delete;

private:
	GoHomeAndSleepTillRested() = default;
};

class QuenchThirst : public State
{
public:
	static QuenchThirst* Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;

	QuenchThirst(const QuenchThirst&) = delete;
	QuenchThirst& operator=(const QuenchThirst&) = delete;

private:
	QuenchThirst() = default;
};
