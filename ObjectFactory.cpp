#include "ObjectFactory.h"

BaseObject* ObjectFactory::factory(const int num)
{
    try
    {
        switch (num) 
        {
        case 1:
            return new Rectangle();
        case 2:
            return new Circle();
        case 4:
            return new CircularArc();
        case 5:
            return new Polygon();
        case 6:
            return new Polyline();
        default:
            /*return new Unknown();*/
            return nullptr;
        }
    }//після створення перевіряти че не нул якщо нул то робити Unknown
    catch (std::bad_alloc& exception)
    {
        std::cerr << "function 'ObjectFactory::factory' memory was not allocated" << '\n';
        return nullptr;
    }   
}
