#include "Actor.h"

class BarrelOfOil : public Actor
{
public:
    BarrelOfOil(int startX, int startY)
        : Actor(IID_BARREL, startX, startY, right, 1.0, 0)
    {
    }
    virtual ~BarrelOfOil() {}
    virtual void doSomething() {}

private:
    //TO-DO: Add the correct member variables
};