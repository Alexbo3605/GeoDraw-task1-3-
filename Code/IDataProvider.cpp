#include "IDataProvider.h"

IDataProvider::IDataReader::IDataReader(const int maxCur) :
	p_current(0), p_maxCurrent(maxCur)
{}

IDataProvider::IDataReader::~IDataReader(void)
{}

IDataProvider::IDataProvider(void)
{}

IDataProvider::~IDataProvider(void)
{}

