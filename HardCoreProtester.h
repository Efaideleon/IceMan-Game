#include "Actor.h"

class HardCoreProtester : public Actor
{
public:
    HardCoreProtester(int startX, int startY)
        : Actor(IID_HARD_CORE_PROTESTER, startX, startY, right, 1.0, 0)
    {
    }
    virtual ~HardCoreProtester() {}
    virtual void doSomething() {}

private:
    //TO-DO: Add the correct member variables
};