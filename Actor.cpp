#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <thread>
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
        // Handling the user input to move the IceMan
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
    // Mutators
    void increaseGoldNuggetCount()
    {
        m_gold++;
    }

    // Accessors
    int getHitPoints()
    {
        return m_hitPoints;
    }

    int getWater()
    {
        return m_water;
    }

    int getSonar()
    {
        return m_sonar;
    }

    int getGold()
    {
        return m_gold;
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
        : Actor(IID_PROTESTER, startX, startY, left, 1.0, 0, world_in)
    {
        numSquaresToMoveInCurrentDirection = 8 + rand() % 53; // Random number between 8 and 60, !Could cause bug?!
        ticksToWaitBetweenMoves = std::max(0, (3) - (0 / 4)); // TO-DO: Implement this formula, 0 is the current level
        hitPoints = 5;
        restingTickCount = 0;
        leaveOilField = false;
        resting = false;
    }
    ~RegularProtester() {}
    void doSomething()
    { // All functions include a isAlive() check and setDead()
        if (!isAlive())
            return;

        if (atExit())
        {
            setDead();
            return;
        }

        if (resting)
        {
            updateRestingTickCount();
            return;
        }

        setLeaveOilField();
        // if the regular protester is leaving the oil field
        if (true)
        {
            // NOTE: There must be an if statement to check if the shortest path has been found
            // TO-DO: Implement this
            if (!thread_started)
            {
                startThread();
                thread_started = true;
            }
            if(thread_isFinished)
            {
                stopThread();
                thread_started = false;
            }
            // NOTE: This is where finding the exit and moving towards it will be implemented
            return;
        }
        resetRestingTickCount();
    }

private:
    void findPathToExit()
    {
        // TO-DO: Implement this
        // NOTE: This where find the path to exit using BFS will be implemented
        // NOTE: This should use a seperate data structure
        // IDEA: First figure out the shortest path
        // IDEA: Then move the protester along the shortest path
        
        StudentWorld::MazeSolver maze_solver(getX(), getY(), m_world);
        
        for (int i = 0; i < 30; i++)
        {
            moveTo(getX() + 1, getY());
            std::cout << "finding path to exit" << std::endl;   
            // this 100 needs to be changed to a variable
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        setDead();
        thread_isFinished = true;
    }

    void startThread()
    {
        thread_isFinished = false;
        worker = std::thread(&RegularProtester::findPathToExit, this);
    }

    void stopThread()
    {
        worker.join();
    }

    void resetRestingTickCount()
    {
        restingTickCount = ticksToWaitBetweenMoves;
        resting = true;
    }

    void updateRestingTickCount()
    {
        restingTickCount--;
        if (restingTickCount <= 0)
            resting = false;
    }

    bool atExit()
    {
        if (getX() == 60 && getY() == 60)
            return true;
        return false;
    }

    void setLeaveOilField()
    {
        if (hitPoints <= 0)
            leaveOilField = true;
    }

    // TO-DO: implement functions to decrease the protester's hit points
    bool thread_isFinished;
    bool thread_started;
    std::thread worker;
    int numSquaresToMoveInCurrentDirection;
    int hitPoints;
    bool leaveOilField;
    int ticksToWaitBetweenMoves;
    int restingTickCount;
    bool resting;
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
    void doSomething()
    {
        if ((abs(m_world->getIceMan()->getX() - getX()) <= 4 &&
             abs(m_world->getIceMan()->getY() - getY()) <= 4) &&
            isVisible() == false)
        {
            setVisible(true);
        }

        if (abs(m_world->getIceMan()->getX() - getX()) <= 3 &&
            abs(m_world->getIceMan()->getY() - getY()) <= 3)
        {
            setDead();
            std::cout << "GoldNugget picked up" << std::endl;
            // TO-DO: Increase the IceMan's gold nugget count
            m_world->getIceMan()->increaseGoldNuggetCount();
        }
    }

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
