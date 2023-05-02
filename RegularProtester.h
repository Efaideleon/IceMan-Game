#include "Actor.h"
#include "StudentWorld.h"

class StudentWorld::RegularProtester : public Actor
{
public:
    RegularProtester(int startX, int startY)
        : Actor(IID_PROTESTER, startX, startY, right, 1.0, 0)
    {
    }
    virtual ~RegularProtester() {}
    virtual void doSomething() {
        cout << "Regular Protester doSomething() called" << endl;
    }

private:
    //TO-DO: Add the correct member variables
};