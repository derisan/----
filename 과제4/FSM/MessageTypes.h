#pragma once

#include <string>
#include <cassert>

enum eMessage
{
	MsgHiHoneyImHome,
	MsgStewReady,
};


inline std::string MsgToStr(int msg)
{
	switch (msg)
	{
	case MsgHiHoneyImHome:
		return "HiHoneyImHome";

	case MsgStewReady:
		return "StewReady";

	default:
		assert(nullptr && "Error. Unknown message.");
	}

	return "";
}