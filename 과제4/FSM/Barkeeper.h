// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#pragma once

#include "BaseEntity.h"
#include "StateMachine.h"

class Barkeeper :
    public BaseEntity
{
public:
	Barkeeper(int id);
	virtual ~Barkeeper();

	virtual void Update() override;
	virtual bool IsMessageHandled(const Telegram& telegram) override;

	bool IsLiquorEnough() const { return mLiquorStock > 0; }
	bool IsLiquorFull() { return mLiquorStock >= kStockLimit; }
	void SetLiquorStock(int val) { mLiquorStock = val; }
	int GetLiquorStock() const { return mLiquorStock; }
	void IncreaseStock() { mLiquorStock++; }
	void DecreaseStock() { mLiquorStock--; }

	bool IsWealthy() const { return mGold >= kGoldLimit; }
	int GetGold() const { return mGold; }
	void SetGold(int val) { mGold = val; }
	void IncreaseGold() { mGold++; }

	StateMachine<Barkeeper>* GetFSM() const { return mStateMachine; }

private:
	StateMachine<Barkeeper>* mStateMachine;

	const int kStockLimit = 3;
	const int kGoldLimit = 4;

	int mLiquorStock;
	int mGold;
};

