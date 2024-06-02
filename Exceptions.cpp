#include "Exceptions.h"

EndOfFile::EndOfFile(void)
{}

EndOfFile::~EndOfFile(void)
{}

IOError::IOError(const std::string& error, int pos) :
    m_error(error), m_pos(pos)
{}

IOError::~IOError(void)
{}

std::string IOError::getError() {
    std::string currentTime = getCurrentTime();
    std::string error = currentTime + "-- " + m_error + " Line --> " + std::to_string(m_pos);
    return error;
}

std::string IOError::getCurrentTime() {

    static constexpr size_t TIME_BUFFER_SIZE = 26;
   

    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char timeBuffer[TIME_BUFFER_SIZE];

    if (ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime) != 0) {
        strcpy_s(timeBuffer, sizeof(timeBuffer), "Error getting time ");
    }

    std::string timeStr = timeBuffer;
    timeStr.pop_back();
    return timeStr;
}