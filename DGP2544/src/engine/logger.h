#pragma once

#include <iostream>
#include <fstream>

class Logger {

private:
	std::string directory;

	std::ifstream logFileRead;
	std::ofstream logFileWrite;

private:
	void checkFile();

public:
	Logger();
	~Logger();

	void writeLog(char* logMsg);

};