#pragma once

#include <cmath>
#include <iostream>

const double kSmallestDelay = 0.25;

struct Telegram
{
	int Sender;
	int Receiver;
	int Msg;
	double DispatchTime;
	void* ExtraInfo;

	Telegram()
		: Sender(-1)
		, Receiver(-1)
		, Msg(-1)
		, DispatchTime(-1)
		, ExtraInfo(nullptr) {}

	Telegram(double time, int sender, int receiver,
		int msg, void* info = nullptr)
		: Sender(sender)
		, Receiver(receiver)
		, Msg(msg)
		, DispatchTime(time)
		, ExtraInfo(info) {}
};

inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return (fabs(t1.DispatchTime - t2.DispatchTime) < kSmallestDelay) &&
		(t1.Sender == t2.Sender) &&
		(t1.Receiver == t2.Receiver) &&
		(t1.Msg == t2.Msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}

	else
	{
		return  (t1.DispatchTime < t2.DispatchTime);
	}
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
	os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
		<< "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;

	return os;
}

template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}