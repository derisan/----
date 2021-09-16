// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#pragma once

class Miner;
struct Telegram;

template<typename T>
class State
{
public:
	virtual ~State() = default;

	virtual void Enter(T*) = 0;
	virtual void Execute(T*) = 0;
	virtual void Exit(T*) = 0;

	virtual bool OnMessage(T*, const Telegram&) = 0;
};
