#pragma once

#include "BaseEntity.h"


class State;

class Miner : public BaseEntity
{
public:
	Miner(int id);
	virtual ~Miner();

	virtual void Update() override;

	void ChangeState(State* newState);

	eLocation GetLocation() const { return mLocation; }
	void SetLocation(eLocation loc) { mLocation = loc; }

	int GetGoldCarried() const { return mGoldCarried; }
	void SetGoldCarried(int val) {	mGoldCarried = val; }
	void AddToGoldCarried(int val);
	bool IsPocketsFull() const { return mGoldCarried >= kMaxNuggets; }

	int GetMoneyInBank() const { return mMoneyInBank; }
	void SetMoneyInBank(int val) { mMoneyInBank = val; }
	void AddToMoneyInBank(int val);
	bool IsWealthy() const { return mMoneyInBank >= kComfortLevel; }
	
	void BuyAndDrinkWhiskey() { mThirst = 0; mMoneyInBank -= 2; }
	bool IsThirsty() const { return mThirst >= kThirstLevel; }

	void DecreaseFatigue() { mFatigue--; }
	void IncreaseFatigue() { mFatigue++; }
	bool IsFatigued() const { return mFatigue > kTirednessThreshold; }


private:
	const int kComfortLevel = 5;
	const int kMaxNuggets = 3;
	const int kThirstLevel = 5;
	const int kTirednessThreshold = 5;

	State* mCurrentState;

	eLocation mLocation;

	int mGoldCarried;
	int mMoneyInBank;
	int mThirst;
	int mFatigue;
};