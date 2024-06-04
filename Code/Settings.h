#pragma once
#define PI 3.1415
#define THROW_ERR 23000000
#define COUNT_OBJECTS_POS 0
static const char* EXEPTION_LOG_FILENAME = "exeption_Log.txt";
static const char* DATA_FILENAME = "data.bin";

enum ObjectType {
    CREATE_RECTANGLE = 1,
    CREATE_CIRCLE = 2,
    CREATE_CIRCULAR_ARC = 4,
    CREATE_POLYGON = 5,
    CREATE_POLYLINE = 6
};

class Settings
{
};


