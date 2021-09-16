// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#include "Log.h"

std::shared_ptr<spdlog::logger> Log::sMinerLogger;
std::shared_ptr<spdlog::logger> Log::sHousewifeLogger;
std::shared_ptr<spdlog::logger> Log::sDoctorLogger;
std::shared_ptr<spdlog::logger> Log::sTellerLogger;
std::shared_ptr<spdlog::logger> Log::sBarkeeperLogger;
std::shared_ptr<spdlog::logger> Log::sDefaultLogger;

void Log::Init()
{
	spdlog::set_pattern("%^%n: %v%$");
	sMinerLogger = spdlog::stdout_color_mt("광부 밥");
	sMinerLogger->set_level(spdlog::level::trace);

	sHousewifeLogger = spdlog::stdout_color_mt("주부 엘사");
	sHousewifeLogger->set_level(spdlog::level::trace);

	sDoctorLogger = spdlog::stdout_color_mt("의사 스미스");
	sDoctorLogger->set_level(spdlog::level::trace);

	sTellerLogger = spdlog::stdout_color_mt("은행원 제인");
	sTellerLogger->set_level(spdlog::level::trace);

	sBarkeeperLogger = spdlog::stdout_color_mt("술집주인 존");
	sBarkeeperLogger->set_level(spdlog::level::trace);

	sDefaultLogger = spdlog::stdout_color_mt("어플리케이션");
	sDefaultLogger->set_level(spdlog::level::trace);
	sDefaultLogger->set_pattern("%^%n: %v%$");
}
