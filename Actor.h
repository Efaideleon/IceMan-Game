#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"

class StudentWorld; // forward declaration
class IceMan; // forward declaration
class Actor : public GraphObject
{
private:
    bool alive;
public:
    StudentWorld *m_world;
    Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, StudentWorld *world_in)
        : GraphObject(imageID, startX, startY, dir, size, depth)
    {
        m_world = world_in;
        alive = true;
    }
    virtual ~Actor()
    {
    }
    virtual void doSomething() = 0;

    // Accessors
    StudentWorld *getWorld()
    {
        return m_world;
    }

    bool isAlive()
    {
        return alive;
    }

    // Mutators
    void setDead()
    {
        alive = false;
    }
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
#endif // ACTOR_H_
