#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
//==========================================
// Class for each Sprite/Object in the game:
//==========================================
class IceMan : public Actor
{
public:
    IceMan(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_PLAYER, startX, startY, right, 1.0, 0, world_in)
    {
        m_hitPoints = 10;
        m_water = 5;
        m_sonar = 1;
        m_gold = 0;
        m_alive = true;
    }
    ~IceMan() {}
    void doSomething()
    {
        // Check to see if it is currently alive
        if (!m_alive)
            return;
        // Check to see if IceMan overlaps with Ice
        if (getWorld()->overlapsWithIce(this))
        {
            // If so, break the ice
            getWorld()->removeIce(this);
        }
        //Handling the user input to move the IceMan
        int ch;
        if (getWorld()->getKey(ch) == true)
        {
            switch (ch)
            {
            case KEY_PRESS_LEFT:
                if (getDirection() == left)
                {
                    if (getX() > 0)
                        moveTo(getX() - 1, getY());
                }
                else
                    setDirection(left);
                break;
            case KEY_PRESS_RIGHT:
                if (getDirection() == right)
                {
                    if (getX() < 60)
                        moveTo(getX() + 1, getY());
                }
                else
                    setDirection(right);
                break;
            case KEY_PRESS_UP:
                if (getDirection() == up)
                {
                    if (getY() < 60)
                        moveTo(getX(), getY() + 1);
                }
                else
                    setDirection(up);
                break;
            case KEY_PRESS_DOWN:
                if (getDirection() == down)
                {
                    if (getY() > 0)
                        moveTo(getX(), getY() - 1);
                }
                else
                    setDirection(down);
                break;
            }
        }
    }
private:
    int m_hitPoints;
    int m_water;
    int m_sonar;
    int m_gold;
    bool m_alive;
};

class Ice : public Actor
{
public:
    Ice(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_ICE, startX, startY, right, 0.25, 0, world_in)
    {
    }
    ~Ice() {}
    void doSomething() {}

private:
    // TO-DO: Add the correct member variables
};

class RegularProtester : public Actor
{
public:
    RegularProtester(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_PROTESTER, startX, startY, right, 1.0, 0, world_in)
    {
    }
    ~RegularProtester() {}
    void doSomething() {}
};

class HardCoreProtester : public Actor
{
public:
    HardCoreProtester(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_HARD_CORE_PROTESTER, startX, startY, right, 1.0, 0, world_in)
    {
    }
    ~HardCoreProtester() {}
    void doSomething() {}

private:
    // TO-DO: Add the correct member variables
};

class Squirt : public Actor
{
public:
    Squirt(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_WATER_SPURT, startX, startY, right, 1.0, 0, world_in)
    {
    }
    ~Squirt() {}
    void doSomething() {}

private:
    // TO-DO: Add the correct member variables
};

class BarrelOfOil : public Actor
{
public:
    BarrelOfOil(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_BARREL, startX, startY, right, 1.0, 0, world_in)
    {
    }
    ~BarrelOfOil() {}
    void doSomething() {}

private:
    // TO-DO: Add the correct member variables
};

class Boulder : public Actor
{
public:
    Boulder(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_BOULDER, startX, startY, right, 1.0, 0, world_in)
    {
    }
    ~Boulder() {}
    void doSomething() {}

private:
    // TO-DO: Add the correct member variables
};

class GoldNugget : public Actor
{
public:
    GoldNugget(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_GOLD, startX, startY, right, 1.0, 0, world_in)
    {
    }
    ~GoldNugget() {}
    void doSomething() {}

private:
    // TO-DO: Add the correct member variables
};

class SonarKit : public Actor
{
public:
    SonarKit(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_SONAR, startX, startY, right, 1.0, 0, world_in)
    {
    }
    ~SonarKit() {}
    void doSomething() {}

private:
    // TO-DO: Add the correct member variables
};

class WaterPool : public Actor
{
public:
    WaterPool(int startX, int startY, StudentWorld *world_in)
        : Actor(IID_WATER_POOL, startX, startY, right, 1.0, 0, world_in)
    {
    }
    ~WaterPool() {}
    void doSomething() {}

private:
    // TO-DO: Add the correct member variables
};

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
