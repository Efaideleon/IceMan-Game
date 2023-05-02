#include "Actor.h"

class Ice : public Actor
{
public:
    Ice(int startX, int startY)
        : Actor(IID_ICE, startX, startY, right, 0.25, 0)
    {
    }
    virtual ~Ice() {}
    virtual void doSomething() {}

private:
    //TO-DO: Add the correct member variables
};