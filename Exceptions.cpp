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

const char* ReadError::getError()
{
	std::string error = m_error + " " + std::to_string(m_pos); 

	return error.c_str();
}
