#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Log
{
public:
	static void Init();

	static std::shared_ptr<spdlog::logger> GetMinerLogger()		{ return sMinerLogger; }
	static std::shared_ptr<spdlog::logger> GetHousewifeLogger() { return sHousewifeLogger; }
	static std::shared_ptr<spdlog::logger> GetDoctorLogger()	{ return sDoctorLogger; }
	static std::shared_ptr<spdlog::logger> GetTellerLogger()	{ return sTellerLogger; }
	static std::shared_ptr<spdlog::logger> GetBarkeeperLogger() { return sBarkeeperLogger; }

private:
	static std::shared_ptr<spdlog::logger> sMinerLogger;
	static std::shared_ptr<spdlog::logger> sHousewifeLogger;
	static std::shared_ptr<spdlog::logger> sDoctorLogger;
	static std::shared_ptr<spdlog::logger> sTellerLogger;
	static std::shared_ptr<spdlog::logger> sBarkeeperLogger;
};


#define MINER_LOG(...)	Log::GetMinerLogger()->trace(__VA_ARGS__)
#define HW_LOG(...)		Log::GetHousewifeLogger()->info(__VA_ARGS__)
#define DR_LOG(...)		Log::GetDoctorLogger()->warn(__VA_ARGS__)
#define TELLER_LOG(...) Log::GetTellerLogger()->error(__VA_ARGS__)
#define BK_LOG(...)		Log::GetBarkeeperLogger()->critical(__VA_ARGS__)
