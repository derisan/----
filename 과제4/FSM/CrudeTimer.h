// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#pragma once

#include <Windows.h>

#pragma comment(lib, "winmm.lib")


#define Timer CrudeTimer::Instance()

class CrudeTimer
{
public:

	CrudeTimer(const CrudeTimer&) = delete;
	CrudeTimer& operator=(const CrudeTimer&) = delete;

	static CrudeTimer* Instance();

	void Update();

	double GetCurrentTime() const { return mCurrentTime; };

private:
	CrudeTimer();

private:
	UINT64 mCurrentTick;
	UINT64 mPrevTick;
	UINT64 mFrequency;

	double mCurrentTime;
};