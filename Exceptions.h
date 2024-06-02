#pragma once

#include <string>
#include <chrono>
#include <ctime>

class EndOfFile {
public:
    EndOfFile(void);
    ~EndOfFile(void);
};

class IOError {
public:
    IOError(const std::string& error, int pos);
    ~IOError(void);
    std::string getError();

private:
    std::string getCurrentTime();

    std::string m_error;
    int m_pos;
};


