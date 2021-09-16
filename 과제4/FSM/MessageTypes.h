#pragma once

#include <string>
#include <cassert>

enum eMessage
{
	MsgHiHoneyImHome,
	MsgStewReady,
	MsgHelpMeDoctor,
	MsgNowYouAreOkay,
	MsgDepositComplete,
};


inline std::string MsgToStr(int msg)
{
	switch (msg)
	{
	case MsgHiHoneyImHome:
		return "HiHoneyImHome";

	case MsgStewReady:
		return "StewReady";

	case MsgHelpMeDoctor:
		return "HelpMeDoctor";

	case MsgNowYouAreOkay:
		return "YouAreOkay";

	case MsgDepositComplete:
		return "DepositComplete";

	default:
		assert(nullptr && "Error. Unknown message.");
	}

	return "";
}