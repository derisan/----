#include "CrudeTimer.h"
#include "Log.h"


CrudeTimer* CrudeTimer::Instance()
{
	static CrudeTimer instance;
	return &instance;
}


CrudeTimer::CrudeTimer()
	: mCurrentTime(0.0f)
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFrequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mPrevTick));
}


void CrudeTimer::Update()
{
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mCurrentTick));

	double dt = (mCurrentTick - mPrevTick) / static_cast<double>(mFrequency);
	mCurrentTime += dt;

	mPrevTick = mCurrentTick;
}

