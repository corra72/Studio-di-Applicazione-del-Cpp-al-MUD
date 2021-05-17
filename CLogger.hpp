#pragma once
#include <string>
#include <chrono>
#include <fstream>

enum class ESeverity {
	VERBOSE,
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

class CLogger {
protected:
	std::fstream InternalStream;
public:
	ESeverity Level;

	CLogger();
	CLogger(const char* fileName);
	CLogger(const char* fileName, ESeverity minLevel);

	virtual ~CLogger();

	virtual void log(ESeverity severity, std::string className, std::string methodName , std::string message);

};
