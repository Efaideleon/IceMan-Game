#include "Actor.h"

class Squirt : public Actor
{
public:
    Squirt(int startX, int startY)
        : Actor(IID_WATER_SPURT, startX, startY, right, 1.0, 0)
    {
    }
    virtual ~Squirt() {}
    virtual void doSomething() {}

private:
    //TO-DO: Add the correct member variables
};