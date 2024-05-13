#pragma once

#include <string>

class EndOfFile
{
public:
    EndOfFile(void);
    ~EndOfFile(void);
};

class ReadError {

public:
    ReadError(std::string error, int pos);
        
   
    const char* getError();

private:
    std::string m_error;
    int m_pos;

};
