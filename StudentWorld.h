#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "GameController.h"

#include <iostream>
#include <vector>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	// About: This functions initializes the game world.
	virtual int init();

	virtual int move();

	virtual void cleanUp()
	{
	}

	// Helper Logic Functions:
	bool overlapsWithIce(Actor *a);
	void removeIce(Actor *a);
	IceMan *getIceMan();
	void removeDeadGameObjects();
private:
	// Private Member Variables:
	IceMan *m_iceMan;
	std::vector<Actor *> m_actors;
	std::vector<Actor *> m_ice;
	// Private Helper Functions:
	void updateDisplayText();
	// load functions:
	void createIceMan(StudentWorld *world_in);
	void loadIce(StudentWorld *world_in);
	void loadRegularProtester(StudentWorld *world_in);  // TO-DO: Implement this function, probably in move()
	void loadHardcoreProtester(StudentWorld *world_in); // TO-DO: Implement this function, probably in move()
	void loadBoulder(StudentWorld *world_in);
	void loadGold(StudentWorld *world_in);
	void loadBarrelOfOil(StudentWorld *world_in);
	void loadSonarKit(StudentWorld *world_in);
	void loadWaterPool(StudentWorld *world_in); // TO-DO: Implement this function, probably in move()
	void loadSquirt(StudentWorld *world_in);	  // TO-DO: Implement this function, probably in move(). Should be called by the IceMan?
};

#endif // STUDENTWORLD_H_
