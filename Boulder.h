#include "Actor.h"

class Boulder : public Actor
{
public:
    Boulder(int startX, int startY)
        : Actor(IID_BOULDER, startX, startY, right, 1.0, 0)
    {
    }
    virtual ~Boulder() {}
    virtual void doSomething() {}

private:
    //TO-DO: Add the correct member variables
};