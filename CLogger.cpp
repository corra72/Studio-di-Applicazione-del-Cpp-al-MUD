#include <fstream>
#include "CLogger.hpp"

CLogger::CLogger()
{
	Level = ESeverity::WARNING;
	InternalStream.open("Data.bin", std::ios::app);
}

CLogger::CLogger(const char* fileName)
{
	Level = ESeverity::WARNING;
	InternalStream.open(fileName, std::ios::app);
}

CLogger::CLogger(const char* fileName, ESeverity minLevel)
{
	Level = minLevel;
	InternalStream.open(fileName, std::ios::app);
}

CLogger::~CLogger()
{
	if (InternalStream.is_open())
		InternalStream.close();
}

void CLogger::log(ESeverity severity, std::string className, std::string methodName, std::string message)
{
	// non so come si usa, ma in pratica dovrebbe riportare il time corrente da salvare nel log
	auto start = std::chrono::system_clock::now();
	// Qui ci va la procedura per salvare il log su disco

	if (severity >= Level) {
		
	}

}
