#include "logger.h"

Logger::Logger() {

	directory = "log_export.txt";

	logFileRead = std::ifstream(directory.c_str());
	logFileWrite = std::ofstream(directory.c_str());

	checkFile();

	std::cout << "Logger ready" << std::endl;

}

Logger::~Logger() {
	std::cout << "\nLogger system shut down" << std::endl;
	std::cout << "All logs dumpped at: " << directory.c_str() << std::endl;
}

void Logger::checkFile() {

	if (logFileRead.is_open()) {

		std::remove(directory.c_str());

		logFileWrite.open(directory.c_str(), std::ios::app);
		logFileWrite << "\n" << std::endl;
		logFileWrite.close();

	}

}

void Logger::writeLog(char* logMsg) {

	logFileWrite.open(directory.c_str(), std::ios::app);

	logFileWrite << logMsg << std::endl;

	logFileWrite.close();

}