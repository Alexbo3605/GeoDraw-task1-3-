#include "SFMLObjectsFactory.h"

std::unique_ptr<BaseObject> SFMLObjectsFactory::factory(const BaseObject* obj)
{
    try
    {
		if (typeid(obj) == typeid(Circle))
		{
            return std::make_unique<SFMLCircleDecorator>(obj);
		}
		else if (typeid(obj) == typeid(CircularArc))
		{
            return std::make_unique<SFMLCircularArcDecorator>(obj);
		}
        else if (typeid(obj) == typeid(Polygon))
        {
            return std::make_unique<SFMLPolygonDecorator>(obj);
        }
        else if (typeid(obj) == typeid(Polyline))
        {
            return std::make_unique<SFMLPolylineDecorator>(obj);
        }
        else if (typeid(obj) == typeid(Rectangle))
        {
            return std::make_unique<SFMLRectangleDecorator>(obj);
        }
    }
    catch (std::bad_alloc)
    {
        std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
        if (logFile.is_open()) {
            logFile << "function 'SFMLObjectsFactory::factory' memory was not allocated" << std::endl;
            logFile.close();
        }
        return nullptr;
    }
    return nullptr;
}
