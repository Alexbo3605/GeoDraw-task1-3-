#include "Exceptions.h"

EndOfFile::EndOfFile(void)
{
}

EndOfFile::~EndOfFile(void)
{
}


ReadError::ReadError(std::string error, const int pos) : 
	m_error(error), m_pos(pos)
{

}

std::string ReadError::getError()
{
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char timeBuffer[26];
   
    if (ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime) != 0) {
        strcpy_s(timeBuffer, sizeof(timeBuffer), "Error getting time ");
    }

    std::string timeStr = timeBuffer;
    timeStr.pop_back();
    std::string error = timeStr + "-- " + m_error + " " + std::to_string(m_pos);
    return error;
}
