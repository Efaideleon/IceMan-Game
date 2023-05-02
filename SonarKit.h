#include "Actor.h"

class SonarKit : public Actor
{
public:
    SonarKit(int startX, int startY)
        : Actor(IID_SONAR, startX, startY, right, 1.0, 0)
    {
    }
    virtual ~SonarKit() {}
    virtual void doSomething() {}

private:
    //TO-DO: Add the correct member variables
};