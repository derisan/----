#pragma once

#include <set>

#include "Telegram.h"

class BaseEntity;

#define Dispatcher MessageDispatcher::Instance()

class MessageDispatcher
{
public:
	MessageDispatcher(const MessageDispatcher&) = delete;
	MessageDispatcher& operator=(const MessageDispatcher&) = delete;

	static MessageDispatcher* Instance();

	void DispatchMessageEx(double delay, int sender, int receiver, int msg, void* extraInfo = nullptr);
	void Update();

private:
	MessageDispatcher() = default;

	void Discharge(BaseEntity* receiver, const Telegram& telegram);

private:

	std::set<Telegram> mMsgQueue;
};