#include "Actor.h"

class WaterPool : public Actor
{
public:
    WaterPool(int startX, int startY)
        : Actor(IID_WATER_POOL, startX, startY, right, 1.0, 0)
    {
    }
    virtual ~WaterPool() {}
    virtual void doSomething() {}

private:
    //TO-DO: Add the correct member variables
};