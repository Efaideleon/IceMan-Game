#include "StudentWorld.h"
#include <string>
#include "Actor.cpp"
using namespace std;
/*
 *===============================================================
 *	About: This functions load the sprites/objects into the game
 *===============================================================
 */
void StudentWorld::createIceMan(StudentWorld *world_in)
{
	int INITIAL_X = 30;
	int INITIAL_Y = 60;
	Actor *a = new IceMan(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_iceMan = a;
}

void StudentWorld::loadIce(StudentWorld *world_in)
{
	for (int x = 0; x < VIEW_WIDTH; x++)
	{
		for (int y = 0; y < 60; y++)
		{
			Actor *a = new Ice(x, y, world_in);
			a->setVisible(true);
			m_ice.push_back(a);
		}
	}
}

void StudentWorld::loadRegularProtester(StudentWorld *world_in)
{
	int INITIAL_X = 10;
	int INITIAL_Y = 60;
	// NOTE: check for game constant for starting position
	Actor *a = new RegularProtester(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_actors.push_back(a);
}

void StudentWorld::loadHardcoreProtester(StudentWorld *world_in)
{
	int INITIAL_X = 40;
	int INITIAL_Y = 60;
	// NOTE: check for game constant for starting position
	Actor *a = new HardCoreProtester(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_actors.push_back(a);
}

void StudentWorld::loadBoulder(StudentWorld *world_in)
{
	int INITIAL_X = 30;
	int INITIAL_Y = 30;
	// NOTE: check for game constant for starting position
	Actor *a = new Boulder(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_actors.push_back(a);
}

void StudentWorld::loadGold(StudentWorld *world_in)
{
	int INITIAL_X = 30;
	int INITIAL_Y = 20;
	// NOTE: check for game constant for starting position
	Actor *a = new GoldNugget(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_actors.push_back(a);
}

void StudentWorld::loadBarrelOfOil(StudentWorld *world_in)
{
	int INITIAL_X = 30;
	int INITIAL_Y = 40;
	// NOTE: check for game constant for starting position
	Actor *a = new BarrelOfOil(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_actors.push_back(a);
}

void StudentWorld::loadSonarKit(StudentWorld *world_in)
{
	int INITIAL_X = 10;
	int INITIAL_Y = 55;
	// NOTE: check for game constant for starting position
	Actor *a = new SonarKit(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_actors.push_back(a);
}

void StudentWorld::loadWaterPool(StudentWorld *world_in)
{
	int INITIAL_X = 50;
	int INITIAL_Y = 15;
	// NOTE: check for game constant for starting position
	Actor *a = new WaterPool(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_actors.push_back(a);
}

void StudentWorld::loadSquirt(StudentWorld *world_in)
{
	int INITIAL_X = 40;
	int INITIAL_Y = 10;
	// NOTE: check for game constant for starting position
	Actor *a = new Squirt(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(true);
	m_actors.push_back(a);
}

//====================================================
//	   StudentWorld Public Methods Implementation
//====================================================
int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	m_iceMan->doSomething();
	return GWSTATUS_CONTINUE_GAME;
}

//**** Private StudentWorld Logic functions *****
bool StudentWorld::overlapsWithIce(Actor *a)
{
	for (int i = 0; i < m_ice.size(); i++)
	{
		// NOTE: collision boxes are at (x, y) and (x + 3, y + 3)
		if (m_ice[i]->getX() == a->getX() && m_ice[i]->getY() == a->getY() ||
		   (m_ice[i]->getX() == a->getX() + 3 && m_ice[i]->getY() == a->getY() + 3))
		{
			return true;
		}
	}
	return false;
}

void StudentWorld::removeIce(Actor *a)
{
	auto it = m_ice.begin();
	// Removing Ice blocks in 3x3 square
	for (int x = a->getX(); x < a->getX() + 4; x++)
	{
		for (int y = a->getY(); y < a->getY() + 4; y++)
		{
			for (auto it2 = it; it2 != m_ice.end(); it2++)
			{
				if ((*it2)->getX() == x && (*it2)->getY() == y)
				{
					(*it2)->setVisible(false);
					it = m_ice.erase(it2);
					break;
				}
			}
		}
	}
}
// About: This functions creates the game world
GameWorld *createStudentWorld(string assetDir)
{
	GameWorld *gw = new StudentWorld(assetDir);
	return gw;
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
