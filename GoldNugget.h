#include "Actor.h"

class GoldNugget : public Actor
{
public:
    GoldNugget(int startX, int startY)
        : Actor(IID_GOLD, startX, startY, right, 1.0, 0)
    {
    }
    virtual ~GoldNugget() {}
    virtual void doSomething() {}

private:
    //TO-DO: Add the correct member variables
};