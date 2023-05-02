#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"

// NOTE: Look into forward declaration
class StudentWorld; // forward declaration

class Actor : public GraphObject
{
public:
    StudentWorld *m_world;
    Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, StudentWorld *world_in)
        : GraphObject(imageID, startX, startY, dir, size, depth)
    {
        m_world = world_in;
    }
    virtual ~Actor()
    {
    }
    virtual void doSomething() = 0;

    StudentWorld *getWorld()
    {
        return m_world;
    }
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
#endif // ACTOR_H_
