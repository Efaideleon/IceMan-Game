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
	IceMan *a = new IceMan(INITIAL_X, INITIAL_Y, world_in);
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
	// TO-DO: manage how often and were gold is placed
	Actor *a = new GoldNugget(INITIAL_X, INITIAL_Y, world_in);
	a->setVisible(false);
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
int StudentWorld::init()
{
	// The following functions load the sprites into the game:
	createIceMan(this);
	loadIce(this);
	loadRegularProtester(this);
	loadHardcoreProtester(this);
	loadBarrelOfOil(this);
	loadBoulder(this);
	loadGold(this);
	loadSonarKit(this);
	loadWaterPool(this);

	updateDisplayText();
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	updateDisplayText();

	m_iceMan->doSomething();
	for (int i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->doSomething();
	}

	// Remove dead actors
	removeDeadGameObjects();

	return GWSTATUS_CONTINUE_GAME;
}

//**** Private StudentWorld Logic functions *****
bool StudentWorld::overlapsWithIce(Actor *a)
{
	for (int i = 0; i < m_ice.size(); i++)
	{
		// NOTE: collision boxes are at (x, y) and (x + 3, y + 3)
		if (m_ice[i]->getX() == a->getX() && m_ice[i]->getY() == a->getY() ||
			(m_ice[i]->getX() == a->getX() + 3 && m_ice[i]->getY() == a->getY()) ||
			(m_ice[i]->getX() == a->getX() && m_ice[i]->getY() == a->getY() + 3) ||
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

IceMan *StudentWorld::getIceMan()
{
	return m_iceMan;
}

void StudentWorld::removeDeadGameObjects()
{
	for (int i = 0; i < m_actors.size(); i++)
	{
		if (m_actors[i]->isAlive() == false)
		{
			std::cout << "Removing dead actor" << std::endl;
			m_actors[i]->setVisible(false);
			m_actors.erase(m_actors.begin() + i);
		}
	}
}

void StudentWorld::updateDisplayText()
{
	int level = getLevel();
	int lives = getLives();
	// TO-DO: health is by percentage
	int health = m_iceMan->getHitPoints();
	int water = m_iceMan->getWater();
	int gold = m_iceMan->getGold();
	int sonar = m_iceMan->getSonar();
	// TO-DO: get oil left
	int oilLeft = 1;
	string game_stats_text = "Lvl: " + std::to_string(level) + " Lives: " + std::to_string(lives) +
							 " Hlth: " + std::to_string(health) + " Wtr: " + std::to_string(water) +
							 " Gld: " + std::to_string(gold) + " Sonar: " + std::to_string(sonar) +
							 " Oil Left: " + std::to_string(oilLeft);
	setGameStatText(game_stats_text);
}

// About: This functions creates the game world
GameWorld *createStudentWorld(string assetDir)
{
	GameWorld *gw = new StudentWorld(assetDir);
	return gw;
}



// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

