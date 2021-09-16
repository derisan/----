// ***********************************************
// **            �ΰ����� ����4. FSM				**
// **            2016180007����               **
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
	sMinerLogger = spdlog::stdout_color_mt("���� ��");
	sMinerLogger->set_level(spdlog::level::trace);

	sHousewifeLogger = spdlog::stdout_color_mt("�ֺ� ����");
	sHousewifeLogger->set_level(spdlog::level::trace);

	sDoctorLogger = spdlog::stdout_color_mt("�ǻ� ���̽�");
	sDoctorLogger->set_level(spdlog::level::trace);

	sTellerLogger = spdlog::stdout_color_mt("����� ����");
	sTellerLogger->set_level(spdlog::level::trace);

	sBarkeeperLogger = spdlog::stdout_color_mt("�������� ��");
	sBarkeeperLogger->set_level(spdlog::level::trace);

	sDefaultLogger = spdlog::stdout_color_mt("���ø����̼�");
	sDefaultLogger->set_level(spdlog::level::trace);
	sDefaultLogger->set_pattern("%^%n: %v%$");
}
