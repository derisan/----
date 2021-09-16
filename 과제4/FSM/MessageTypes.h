// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

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
	MsgIWantDeposit
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

	case MsgIWantDeposit:
		return "IWantDeposit";

	default:
		assert(nullptr && "Error. Unknown message.");
	}

	return "";
}