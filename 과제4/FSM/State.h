#pragma once

class Miner;

template<typename T>
class State
{
public:
	virtual ~State() = default;

	virtual void Enter(T*) = 0;
	virtual void Execute(T*) = 0;
	virtual void Exit(T*) = 0;
};
