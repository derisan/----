#pragma once

#include "State.h"

template<typename T>
class StateMachine
{
public:
	StateMachine(T* owner)
		: mOwner(owner)
		, mCurrentState(nullptr)
		, mPreviousState(nullptr)
		, mGlobalState(nullptr) {}

	void SetCurrentState(State<T>* state) { mCurrentState = state; }
	void SetPreviousState(State<T>* state) { mPreviousState = state; }
	void SetGlobalState(State<T>* state) { mGlobalState = state; }

	void Update() 
	{
		if (mGlobalState)
		{
			mGlobalState->Execute(mOwner);
		}

		if (mCurrentState)
		{
			mCurrentState->Execute(mOwner);
		}
	}

	void ChangeState(State<T>* newState)
	{
		mPreviousState = mCurrentState;
		mCurrentState->Exit(mOwner);
		mCurrentState = newState;
		mCurrentState->Enter(mOwner);
	}

	void RevertToPreviousState()
	{
		ChangeState(mPreviousState);
	}

	bool IsInState(const State<T>& state) const
	{
		return typeid(*mCurrentState) == typeid(state);
	}

private:
	T* mOwner;
	State<T>* mCurrentState;
	State<T>* mPreviousState;
	State<T>* mGlobalState;
};