#pragma once

#include <string>
#include <chrono>
#include <ctime>

class EndOfFile {
public:
    EndOfFile(void);
    ~EndOfFile(void);
};

class ReadError {
public:
    ReadError(std::string error, int pos);
    std::string getError();
private:
    std::string m_error;
    int m_pos;
};

class WriteError {
public:
    WriteError(int pos);
    std::string getError();
private:
    int m_pos;
};

