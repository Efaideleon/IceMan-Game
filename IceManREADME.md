# IceMan-Game

## You Have to Create Classes for All Actors

The Iceman game has a number of different Game Objects, including:

- The Iceman
- Regular Protesters
- Hardcore Protesters
- Squirts of water (that can be shot by the Iceman)
- Barrels of oil
- Boulders
- Gold Nuggets
- Sonar kits
- Water refills (that can be picked up to refill the Iceman’s squirt gun)
- Ice

Each of these game objects can occupy a slot in the oil field and interact with other game objects within the oil field.

Now of course, many of your game objects will share things in common – for instance, every one of the objects in the game (Regular Protesters, the Iceman, Ice, Boulders, etc.) has an x,y coordinate. Many game objects have the ability to perform an action – to do something (e.g., move or shoot) – during each tick of the game. Many of them can be potentially annoyed (e.g., the Iceman and Protesters can be by annoyed by Squirts of water or bonked by Boulders, etc.) and could be irritated to the point of quitting during a tick. All of them need some attribute that indicates whether or not they are still active/alive (or they became inactive/died during the current tick), etc.

It is therefore your job to determine the commonalities between your different game objects and make sure to factor out common behaviors and traits and move these into appropriate base classes, rather than duplicate these items across your derived classes – this is in fact one of the tenets of object oriented programming.

Your grade on this project will largely depend upon your ability to create an intelligent set of classes that follow good object-oriented design principles. Your classes MUST NEVER duplicate code or member variables – if you find yourself writing the same (or largely similar) code across multiple classes, then this is an indication that you should define a common base class and migrate this common functionality/data to the base class. Duplication of code is the root of all evil in programming – it leads to bugs, inconsistencies, code bloat, etc. and should be avoided whenever possible.

**Hint:** When you notice this specification repeating the same text nearly exactly in the following sections (e.g., in the Regular Protester section and the Hardcore Protester section, or in the Gold Nugget or Sonar Kit sections) you MUST make sure to identify common behaviors and move these into proper base classes. NEVER duplicate behaviors across classes that can be moved into a base class!

You MUST derive all of your game objects directly or indirectly from a base class that we provide called GraphObject, e.g.:

```cpp
class Actor: public GraphObject {
public:
    // ...
    class Protester: public Actor {
    public:
        // ...
    };
    class HardcoreProtester: public Protester {
    public:
        // ...
    };
};
```
GraphObject is a class that we have defined that helps hide a lot of the ugly logic required to graphically display your actors on the screen. If you don’t derive your classes from our GraphObject base class, then you won’t see anything displayed on the screen!
```cpp
The GraphObject class provides the following methods that you may use in your classes:

    GraphObject(int imageID, int startX, int startY,
                DIRECTION startDirection, float size = 1.0,
                unsigned int depth = 0);

    void setVisible(bool shouldIDisplay);
    void getX() const;
    void getY() const;
    void moveTo(int x, int y);

    DIRECTION getDirection() const;    // Directions: up, down, left, right
    void setDirection(DIRECTION d);    // Directions: up, down, left, right
```
You may use any of these methods in your derived classes, but you must not use any other methods found inside of GraphObject in your other classes (even if they are public in our class). You must not redefine any of these methods in your derived classes since they are not defined as virtual in our base class.

```cpp
GraphObject(
    int imageID,
    int startX,
    int startY,
    DIRECTION startDirection,
    float size = 1.0,
    unsigned int depth = 0
);
```
When you construct a new GraphObject, you must specify the following parameters:

1. An `imageID` that indicates what graphical image (aka sprite) our graphics engine should display on the screen. One of the following IDs, found in `GameConstants.h`, MUST be passed in for the `imageID` value:

- `IID_PLAYER`
- `IID_PROTESTER`
- `IID_HARD_CORE_PROTESTER`
- `IID_WATER_SPURT`
- `IID_BOULDER`
- `IID_BARREL`
- `IID_ICE`
- `IID_GOLD`
- `IID_SONAR`
- `IID_WATER_POOL`

    - for the Iceman
    - a regular protester
    - a hardcore protester
    - for a squirt of water from the Iceman
    - a barrel of oil
    - a 1x1 square of ice
    - a gold nugget
    - a sonar kit
    - a water pool to refill the squirt gun

2. You must specify the initial x,y location of the object. The `x` value may range from 0 to `VIEW_WIDTH-SPRITE_WIDTH` inclusive, and the `y` value may range from 0 to `VIEW_HEIGHT-SPRITE_HEIGHT` inclusive. Notice that you pass the coordinates as `x,y` (i.e., column, row and not row, column.).

3. You must specify the initial direction that each game object will be facing. Acceptable values include: `up`, `down`, `left`, and `right`. The definitions for these values may be found in the `GraphObject` class within `GraphObject.h`.

4. You must specify the size of the image. Most images (e.g., Protesters, Gold Nuggets, the Iceman, etc.) will have a size of `1.0`, which is the equivalent of a 4 squares by 4 squares on the screen. In contrast, Ice will always have a size of `.25` making it 1 square by 1 square.

5. You must specify the depth of the image. This value indicates whether the image is in the foreground (`0`), in the background (`10`) or somewhere in between. If two images are displayed at the same location, the graph object with the smaller depth value will be drawn on top of the graph object with the larger depth value, either partially or completely obscuring it. We will specify what the depth should be for each of your GraphObject-derived classes in the sections below.

`setVisible(bool shouldIDisplay)`

New `GraphObjects` start out invisible and are NOT displayed on the screen until the programmer calls the `setVisible()` method with a value of `true` for the parameter.

`setVisible(bool shouldIDisplay)` is used to tell our graphical system whether or not to display a particular `GraphObject` on the screen. If you call `setVisible(true)` on a `GraphObject`, then your object will be displayed on screen automatically by our framework (e.g., a Regular Protester image will be drawn to the screen at the `GraphObject’s` specified `x,y` coordinates if the object’s `imageID` is `IID_PROTESTER`). If you call `setVisible(false)` then your `GraphObject` will not be displayed on the screen.

NOTE: When you create a new game object, always remember that if you want it to be displayed on the screen, you must call its `setVisible()` method with a value of `true`!

`int getX() const`
`int getY() const`

These methods are used to determine a `GraphObject’s` current location on the screen. Since each `GraphObject` maintains an `x,y` location, this means that your derived classes must not also have `x,y` member variables, but instead use those in the `GraphObject` base class.

`void moveTo(int x, int y)`

The `moveTo()` method must be used to update the location of a `GraphObject` within the oil field. For example, if a Regular Protester’s movement logic dictates that it should move to the right, you must do something like the following:

`moveTo(getX()+1, y);` // move one square to the right

You must use the `moveTo()` method to adjust the location of a `GameObject` in the game if you want that object to be properly animated. As with the `GraphObject` constructor, note that the order of the parameters to `moveTo` is `x,y` (col,row) and NOT `y,x` (row,col).

`DIRECTION getDirection() const`
`void setDirection(DIRECTION d)`

These two methods are used to get and set the current direction the `GraphObject` is facing. Valid values include `up`, `down`, `left`, and `right`. Changing the direction causes our graphics engine to automatically rotate the image appropriately before displaying it on the screen.

Now that you know about our `GraphObject` base class, you’ll need to derive all of your game object classes based on this class (either directly, or indirectly).

# Create the StudentWorld Class

Your `StudentWorld` class is responsible for orchestrating virtually all game play – it keeps track of the whole game world (the Ice of the oil field, and all of its inhabitants such as Protesters, the Iceman, Boulders, Goodies, etc.). It is responsible for initializing the game world at the start of the game, asking all of your game’s actors to do something during each tick of the game, and destroying all of the actors in the game world when the user loses a life or when actors disappear (e.g., a Regular Protester leaves the oil field after being sufficiently annoyed by being repeatedly squirted).

Your `StudentWorld` class must be derived from our `GameWorld` class (found in `GameWorld.h`) and must implement at least these three methods (which are defined as pure virtual in our `GameWorld` class):

- `virtual int init() = 0;`
- `virtual int move() = 0;`
- `virtual void cleanUp() = 0;`

The code that you write must never call any of these three functions. Instead, our provided game framework will call these functions for you. So you have to implement them correctly, but you won’t ever call them yourself in your code.

When a new level starts (e.g., at the start of a game, or when the player completes a level and advances to the next level), our game framework will call the `init()` method that you defined in your `StudentWorld` class. You don’t call this function; instead, our provided framework code calls it for you.

Your `init()` method is responsible for creating the current level’s oil field and populating it with Ice, Boulders, Barrels of Oil, and Gold Nuggets (we’ll show you how below), and constructing a virtual representation of the current level in your `StudentWorld` class, using one or more data structures that you come up with. This function must return the value `GWSTATUS_CONTINUE_GAME` (defined in `GameConstants.h`).

The `init()` method is automatically called by our provided code either (a) when the game first starts, (b) when the player completes the current level and advances to a new level (that needs to be initialized), or (c) when the player loses a life (but has more lives left) and the game is ready to restart at the current level.

Once a new level has been initialized with a call to your `init()` method, our game framework will repeatedly call your `StudentWorld`’s `move()` method, at a rate of roughly 10-20 times per second. Each time your `move()` method is called, it must run a single tick of the game. This means that it is responsible for asking each of the game’s actors (e.g., the Iceman, each Regular Protester or Hardcore Protester, Boulders, etc.) to try to do something: e.g., move themselves and/or perform their specified behavior. Finally, this method is responsible for disposing of (i.e., deleting) actors (e.g., a Squirt from the Iceman’s squirt gun that has run its course, a Regular Protester who has left the oil field, a Boulder that has fallen and crashed into Ice below, etc.) that need to disappear during a given tick. For example, if a Boulder has completed its fall and disintegrated in the Ice below, then its state should be set to “dead,” and the after all of the actors in the game get a chance to do something during the tickThe `move()` method should remove that Boulder from the game world (by deleting its object and removing any reference to the object from the `StudentWorld`’s data structures). Your `move()` method will automatically be called once during each tick of the game by our provided game framework. You will never call the `move()` method yourself.

The `cleanup()` method is called by our framework when the player loses a life (e.g., the Iceman’s hit-points reach zero due to being shouted at by one or more Protesters), or the player successfully completes the current level. The `cleanup()` method is responsible for freeing all actors (e.g., all Regular Protester objects, all Hardcore Protester objects, all Ice and Boulder objects, the Iceman object, all Goodie objects (like Water, Gold Nuggets, Barrels of oil), Squirt objects, etc.) that are currently active in the game. This includes all actors created during either the `init()` method or introduced during subsequent game ticks (e.g., a Hardcore Protester that was added to the oil field during the middle of a level, or a Squirt of water shot by the Iceman just before they complete the level) that have not yet been removed from the game.

You may add as many other public or private methods and private member variables to your `StudentWorld` class as you like (in addition to the above three methods, which you must implement).

Your `StudentWorld` class must be derived from our `GameWorld` class. Our `GameWorld` class provides the following methods for your use:

- `unsigned int getLives() const;`
- `void decLives();`
- `void incLives();`
- `unsigned int getScore() const;`
- `unsigned int getLevel() const;`
- `void increaseScore(unsigned int howMuch);`
- `void setGameStatText(string text);`
- `bool getKey(int& value);`
- `void playSound(int soundID);`

`getLives()` can be used to determine how many lives the player has left. `decLives()` reduces the number of player lives by one. `incLives()` increases the number of player lives by one. `getScore()` can be used to determine the player’s current score. `getLevel()` can be used to determine the player’s current level number.

`increaseScore()` is used by your `StudentWorld` class (or you other classes) to increase the user’s score when the Iceman irritates Protesters with a Squirt, picks up a Barrel or a Goodie of some sort, or bonks a Protester with a Boulder, etc. When your code calls this method, you must specify how many points the player gets (e.g., 100 points for irritating a Regular Protester to the point where it gives up). This means that the game score is controlled by our `GameWorld` object – you must not maintain your own score member variable in your own class(es).

The `setGameStatText()` method is used to specify what text is displayed at the top of the game screen, e.g.: `Lvl: 52 Lives: 3 Hlth: 80% Wtr: 20 Gld: 3 Oil Left: 2 Sonar: 1 Scr: 321000`. You’ll pass in a string to this function that specifies the proper stat values.

`getKey()` can be used to determine if the user has hit a key on the keyboard to move the player or to fire. This method returns `true` if the user hit a key during the current tick, and `false` otherwise (if the user did not hit any key during this tick). The only argument to this method is a variable that will be filled in with the key that was pressed by the user (if any key was pressed). If the player does hit a key, the argument will be set to one of the following values (constants defined in GameConstants.h):
- KEY_PRESS_LEFT
- KEY_PRESS_RIGHT
- KEY_PRESS_UP
- KEY_PRESS_DOWN
- KEY_PRESS_SPACE
- KEY_PRESS_ESCAPE
- KEY_PRESS_TAB
- ‘z’
- ‘Z’

The `playSound()` method can be used to play a sound effect when an important event happens during the game (e.g., a Regular Protester gives up due to being squirted, or the Iceman picks up a Barrel of oil). You can find constants (e.g., `SOUND_PROTESTER_GIVE_UP`) that describe what noise to make inside of the `GameConstants.h` file. Here’s how the `playSound()` method might be used:

`// if a Regular Protester reaches zero hit-points and dies
// then make a dying sound`

`if (theProtesterHasZeroHitPoints())
    GameController::getInstance().playSound(SOUND_PROTESTER_GIVE_UP);`

# init() Details

Your `StudentWorld`'s `init()` method must:

A. Initialize the data structures used to keep track of your game's virtual world.

B. Construct a new oil field that meets the requirements stated in the section below (filled with Ice, Barrels of oil, Boulders, Gold Nuggets, etc.).

C. Allocate and insert a valid `Iceman` object into the game world at the proper location.

Your `init()` method must construct a representation of your virtual world and store this in your `StudentWorld` object. It is required that you keep track of all of the game objects (e.g., actors like Regular Protesters, Gold Nuggets, Barrels of oil, Sonar Kits, Boulders, etc.) with the exception of Ice objects and the `Iceman` object in a single STL collection like a list or vector. To do so, we recommend using a vector of pointers to your game objects, or a list of pointers to your game objects.

If you like, your `StudentWorld` class may keep a separate pointer to the `Iceman` rather than keeping a pointer to the `Iceman` object in this collection along with the other game objects. Similarly, you may store pointers to all Ice objects in a different data structure than the list/vector used for your other game actors (i.e., those objects that actually do something during each tick) if you like. Hint: Keeping all of your Ice objects in a separate 2-D array of Ice pointers will speed things up.

You must not call the `init()` method yourself. Instead, this method will be called by our framework code when it's time for a new game to start (or when the player completes a level, or needs to restart a level).

## Contents of Each Oil Field

First, you must completely fill rows 0 through 59 of the oil field with Ice objects, with the exception of a vertical mine shaft in the middle of the field. Your `Ice` class, which is used to create these `Ice` objects, must be derived in some way from our `GraphObject` class, and have an `imageID` of `IID_ICE`. An `Ice` object is the simplest type of game object in `Iceman`. All it does is display itself to the screen – it doesn't move or perform any other actions on its own. You'll find more details on the requirements for the `Ice` object in its section below.

As mentioned above, a single tunnel, 4 squares wide (occupying columns 30-33 of the oil field), and 56 squares deep (occupying rows 4-59) must lead from the surface of the mine down into its depths, and must be devoid of any `Ice` objects.

The `Iceman` must start the game at location x=30, y=60, just atop the tunnel, at the start of each level (and after the `Iceman` loses a life and restarts a level).

You must distribute the following game objects randomly in the oil field:

- `B` Boulders in each level, where: `int B = min(current_level_number / 2 + 2, 9)`
- `G` Gold Nuggets in each level, where: `int G = max(5-current_level_number / 2, 2)`
- `L` Barrels of oil in each level, where: `int L = min(2 + current_level_number, 21)`

The starting level # is level 0, so level 0 would have 2 Boulders, 5 Nuggets and 2 Barrels of oil. Or, for example, level 2 would have 3 Boulders, 4 Nuggets and 4 Barrels of oil.

No distributed game object may be within a radius (Euclidian distance) of 6 squares of any other distributed game object. For example, if a Boulder were distributed to x=1,y=2, then a Nugget could not be distributed to x=6,y=4 because the two would be 5.39 squares away (less than or equal to 6 squares away). However the same Nugget could be distributed to x=6,y=6 because this would be 6.4 squares away (more than 6.0 squares away). Nuggets and Oil Barrels must be distributed between x=0,y=0 and x=60,y=56 inclusive, meaning that the lower-left corner of any such object must fall within this rectangle. Boulders must be distributed between x=0,y=20 and x=60,y=56, inclusive (so they have room to fall).

All distributed Gold Nuggets must start in a state that is pickup-able by the Iceman, but not by Protesters. All distributed Gold Nuggets must start out in a permanent state.

All distributed Gold Nuggets and Barrels of oil must start out in an invisible state (not displayed on the screen). They will become visible when the Iceman either gets near them (this is detailed within the specs for Nuggets and Barrels) or if the Iceman uses a sonar charge to scan the nearby Ice around him.

There must not be any Ice overlapping the 4x4 square region of each Boulder, so you’ll need to clear this Ice out when you place your Boulders within the oil field (or place your Boulders first, then avoid placing Ice objects where the Boulders are located). The other items must have the area under their 4x4 image completely filled with Ice (in other words, these items must not be distributed at the surface of the oil field or within the mine shaft).

Once your `init()` method has distributed all of the Ice, Iceman, and game objects throughout the oil field, it should return so our game framework can start the game.

## move() Details

The `move()` method must perform the following activities:

1. It must update the status text on the top of the screen with the latest information (e.g., the user’s current score, the remaining bonus score for the level, etc.).

2. It must ask all of the actors that are currently active in the game world to do something (e.g., ask a Regular Protester to move itself, ask a Boulder to see if it needs to fall down because Ice beneath it was dug away, give the Iceman a chance to move up, down, left or right, etc.).
   - If an actor does something that causes the Iceman to give up, then the `move()` method should immediately return `GWSTATUS_PLAYER_DIED`.
   - If the Iceman collects all of the Barrels of oil on the level (completing the current level), then the `move()` method should immediately play a sound of `SOUND_FINISHED_LEVEL` and then return a value of `GWSTATUS_FINISHED_LEVEL`.

3. It must then delete any actors that need to be removed from the game during this tick and remove them from your STL container that tracks them. This includes, for example:
   - A Protester that has run to the upper-right-hand corner of the oil field after being sufficiently annoyed (by being squirted by a Squirt or hit by a Boulder) and is ready to “leave” the oil field.
   - A Boulder that has fallen down a shaft and disintegrated upon hitting the bottom (or another Boulder).
   - A Gold Nugget that has been picked up by the Iceman or a Protester and is therefore no longer in the oil field.
   - A Water Pool that has dried up after a period of time.
   - A Squirt from the Iceman’s squirt gun once it’s reached the maximum distance it can travel.
   - Etc.

The `move()` method must return one of three different values when it returns at the end of each tick (all are defined in `GameConstants.h`):
   - `GWSTATUS_PLAYER_DIED`
   - `GWSTATUS_CONTINUE_GAME`
   - `GWSTATUS_FINISHED_LEVEL`

The first return value indicates that the player died during the current tick, and instructs our provided framework code to tell the user the bad news and restart the level if the player has more lives left. If your `move()` method returns this value, then our framework will call your `cleanup()` method to destroy the level, then call your `init()` method to re-initialize the level from scratch. Assuming the player has more lives left, they will be prompted to continue their game, and our framework will then begin calling your `move()` method over and over, once per tick, to let the user play the level again.

The second return value indicates that the tick completed without the player dying BUT the player has not yet completed the current level. Therefore the game play should continue normally for the time being. In this case, the framework will advance to the next tick and call your `move()` method again.

The final return value indicates that the player has completed the current level (that is, gathered all of the Barrels of oil on the level). If your `move()` method returns this value, then the current level is over, and our framework will call your `cleanup()` method to destroy the level, advance to the next level, then call your `init()` method to prepare that level for play, etc...

**IMPORTANT NOTE:** The “skeleton” code that we provide to you is hard-coded to return a `GWSTATUS_PLAYER_DIED` status value from our dummy version of the `move()` method. Unless If you change this value to `GWSTATUS_CONTINUE_GAME` your game will not display anything on the screen! So if your screen just shows up black once the user starts playing, you’ll know why!

Here’s pseudocode for how the `move()` method might be implemented:

```cpp
int StudentWorld::move()
{
    updateDisplayText(); // update the score/lives/level text at screen top
    // The term “Actors” refers to all Protesters, the player, Goodies, // Boulders, Barrels of oil, Holes, Squirts, the Exit, etc.
    // Give each Actor a chance to do something
    for each of the actors in the game world
    {
        if (actor[i] is still active/alive)
        { 
            // ask each actor to do something (e.g. move) 
            tellThisActorToDoSomething(actor[i]);

            if (theplayerDiedDuringThisTick() == true)
                return GWSTATUS_PLAYER_DIED;

            if (theplayerCompletedTheCurrentLevel() == true)
            {
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }

    // Remove newly-dead actors after each tick
    removeDeadGameObjects(); // delete dead game objects
    
    // return the proper result
    if (theplayerDiedDuringThisTick() == true)
        return GWSTATUS_PLAYER_DIED;

    // If the player has collected all of the Barrels on the level, then
    // return the result that the player finished the level 
    if (theplayerCompletedTheCurrentLevel() == true)
    {
        playFinishedLevelSound();
        return GWSTATUS_FINISHED_LEVEL;
    }

    // the player hasn’t completed the current level and hasn’t died
    // let them continue playing the current level
    return GWSTATUS_CONTINUE_GAME;
}
```

## Update the Game Status Line

### Give Each Actor a Chance to Do Something

During each tick of the game each active actor must have an opportunity to do something (e.g., move around, shoot, etc.). Actors include the Iceman, Regular Protesters, Hardcore Protesters, Boulders, Gold Nuggets, Barrels of oil, Water, Squirts from the Iceman’s squirt gun, and Sonar Kits.

Your `move()` method must enumerate each active actor in the oil field (i.e., held by your `StudentWorld` object) and ask it to do something by calling a method in the actor’s object named `doSomething()`. In each actor’s `doSomething()` method, the object will have a chance to perform some activity based on the nature of the actor and its current state: e.g., a Regular Protester might move one step up, the Iceman might shoot a Squirt of water, a Boulder may fall down one square, etc.

To help you with testing, if you press the `f` key during the course of the game, our game controller will stop calling `move()` every tick; it will call `move()` only when you hit a key (except the `r` key). Freezing the activity this way gives you time to examine the screen, and stepping one move at a time when you're ready helps you see if your actors are moving properly. To resume regular game play, press the `r` key.

### Add New Actors During Each Tick

During each tick of the game in your `move()` method, you may need to add new Protesters (Regular or Hardcore) and/or Goodies (Water Pools or Sonar Kits) to the oil field. You must use the following approach to decide whether to add these new actors to the oil field:

1. A new Protester (Regular or Hardcore) may only be added to the oil field after at least T ticks have passed since the last Protester of any type was added, where: `int T = max(25, 200 – current_level_number)`
2. The target number P of Protesters that should be on the oil field is equal to: `int P = min(15, 2 + current_level_number * 1.5)`
3. However, based on #1 above, you can only add a new Protester to the oil field every T ticks, so the actual number of Protesters on the oil field at any particular time may be less than the target number P.
4. The first Protester must be added to the oil field during the very first tick of each level (and any replays of the level).
5. Assuming the appropriate number of ticks T has elapsed since the last Protester was added to the oil field, AND the current number of Protesters on the oil field is less than P, then you must add a new Protester to the oil field during the current tick. All Protesters must start at location x=60,y=60 on the screen. The odds of the Protester being a Hard Core Protester (vs. a Regular Protester) must be determined with this formula: `int probabilityOfHardcore = min(90, current_level_number * 10 + 30)`. There is a 1 in G chance that a new Water Pool or Sonar Kit Goodie will be added to the oil field during any particular tick, where: `int G = current_level_number * 25 + 300`. Assuming a new Goodie should be added, there is a 1/5 chance that you should add a new Sonar Kit, and a 4/5 chance you should add a Water Goodie.

Each new Sonar Kit must be added at x=0, y=60 on the screen.

Each new Water Goodie must be added to a random ice-less spot in the oil field. Water may only be added to a location if the entire 4x4 grid at that location is free of Ice.

Remove Dead Actors after Each Tick

At the end of each tick your `move()` method must determine which of your actors are no longer alive, remove them from your STL container of active actors, and delete their objects (so you don’t have a memory leak). For example, once a Barrel is picked up by the Iceman during a tick, it should be marked as “not active.” After giving all of the actors a chance to move during the current tick, your `move()` method` would then discover this inactive Barrel (as well as any other objects that have become inactive during this tick) and remove its object pointer from your StudentWorld’s container of active objects. Finally, your `move()` method should delete the object (using the C++ delete command) to free up room in memory for future actors that will be introduced later in the game. (Hint: Each of your actors could have a member variable indicating whether or not it is still active/alive!)

Updating the Display Text

Your `move()` method must update the game statistics at the top of the screen during every tick by calling the `setGameStatText()` method that we provide in our GameWorld class. You could do this by calling a function like the one below from your `StudentWorld’s` `move()` method:

```cpp
void setDisplayText() {
    int level = getCurrentGameLevel();
    int lives = getNumLivesLeft();
    int health = getCurrentHealth();
    int squirts = getSquirtsLeftInSquirtGun();
    int gold = getPlayerGoldCount();
    int barrelsLeft = getNumberOfBarrelsRemainingToBePickedUp();
    int sonar = getPlayerSonarChargeCount();
    int score = getCurrentScore();

    // Next, create a string from your statistics, of the form:
    // Lvl: 52 Lives: 3 Hlth: 80% Wtr: 20 Gld: 3 Oil Left: 2 Sonar: 1 Scr: 321000
    string s = someFunctionYouUseToFormatThingsNicely(level, lives, health,
                                     squirts, gold, barrelsLeft, sonar, score);

    // Finally, update the display text at the top of the screen with your newly created stats
    setGameStatText(s); // calls our provided GameWorld::setGameStatText
}
```

Your status line must meet the following requirements:

Each field must be exactly as wide as shown in the example above:

- The Lvl field must be 2 digits long, with leading spaces (e.g., “_1”, where _ represents a space).
- The Lives field should be 1 digit long (e.g., “2”).
- The Hlth field should be 3 digits long and display the player’s health percentage (not its hit-points!), with leading spaces, and be followed by a percent sign (e.g., “_70%”).
- The Wtr field should be 2 digits long, with a leading space as required (e.g., “_ 7”).
- The Gld field should be 2 digits long, with a leading space as required (e.g., “_ 3”).
- The Oil Left field should be 2 digits long, with a leading space as required (e.g., “_ 4”).
- The Sonar field should be 2 digits long, with a leading space as required (e.g., “_ 2”).
- The Scr must be exactly 6 digits long, with leading zeros (e.g., 003124).

Each statistic must be separated from the last statistic by two spaces. For example, between the “000100” of the score and the “L” in “Level” there must be exactly two spaces.

**cleanUp() Details**

When your `cleanUp()` method is called by our game framework, it means that the Iceman lost a life (e.g., his hit-points/annoyance tolerance reached zero due to being shouted at or being bonked by a Boulder), or has completed the current level. In this case, every actor in the entire oil field (the Iceman and every Protester, Goodies like Nuggets, Sonar Kits and Water, Barrels of oil, Boulders, Ice, etc.) must be deleted and removed from your `StudentWorld`’s container(s) of active objects, resulting in an empty oil field. If the player has more lives left, our provided code will subsequently call your `init()` method to create a new oil field and the level will then continue from scratch with a brand new set of actors (including a newly-generated Iceman!).

You must not call the `cleanUp()` method yourself when the player’s hit points go to zero. Instead, this method will be called by our code.

# The Iceman Class

Here are the requirements you must meet when implementing the Iceman class:

### What an Iceman Object Must Do When It Is Created

When it is first created:
- The Iceman must have an image ID of `IID_PLAYER`.
- The Iceman must always start at location `x=30, y=60`.
- The Iceman, in its default state:
  - Is given 10 hit points.
  - Is given 5 units of water to squirt with his squirt gun (he may pick up additional Water in the oil field).
  - Is given 1 sonar charge.
  - Starts out with zero gold nuggets.
  - Should start facing rightward.

The Iceman has the following graphic parameters:
- It has an image depth of 0 – meaning its graphic image should always be in the foreground (above other images).
- It has a size of 1.0.

In addition to any other initialization that you decide to do in your Iceman class, a Iceman (or one of its base classes) must set itself to be visible using the GraphObject class’s `setVisible()` method, e.g.:

`setVisible(true);`

### What the Iceman Must Do During a Tick

The Iceman must be given an opportunity to do something during every tick (in its `doSomething()` method). When given an opportunity to do something, the Iceman must do the following:

1. The Iceman must check to see if it is currently alive. If not, then its `doSomething()` method must return immediately – none of the following steps should be performed.
2. If the Iceman’s 4x4 image currently overlaps any Ice objects within the oil field, then it will call upon the `StudentWorld` object to:
   * Remove/destroy the Ice objects from the 4x4 area occupied by the Iceman (from x, y to x+3,y+3 inclusive)
   * Make a digging sound by playing the `SOUND_DIG` sound (see the `StudentWorld` section of this document for details on how to play a sound).
3. Otherwise, the `doSomething()` method must check to see if the human player pressed a key (the section below shows how to check if the user pressed a key, and if so, how to determine what key the user pressed).
   * If the user presses the Escape key, this allows the user to abort the current level. In this case, the Iceman object should set itself to completely annoyed (aka dead). The code in your `StudentWorld` class should detect that the Iceman has died and address this appropriately (e.g., replay the level from scratch, or end the game if the player has run out of lives).
   * If the user presses the spacebar key, then the Iceman will fire a Squirt into the oil field, assuming they have sufficient water in their squirt gun to do so. The Iceman will then reduce their water count by 1. To fire a Squirt, the player must create and add a new Squirt object into the oil field at a location that is four squares immediately in front of the Iceman, facing the same direction as the Iceman. So if the Iceman is at x=10,y=7, and he is facing upward, then the new Squirt object would be placed at location x=10, y=11, and the Squirt would be facing upward. Every time the Iceman fires a Squirt, it must play the sound `SOUND_PLAYER_SQUIRT`.
     * If the initial location where the Squirt starts (i.e., 4 squares in front of the Iceman) is occupied by one or more Ice objects or is within a radius of 3.0 of a Boulder object, then the Iceman must still make a squirting noise and will waste 1 unit of water, but the Iceman must not add any Squirt object into the oil field and thus no damage can be done to any Protesters (it’s as if the Iceman shot water against a wall and it immediately dissipated).
     * Hint: One way to implement this is to have your Iceman create a new Squirt object in the proper location and facing the proper direction, and then give it to your `StudentWorld` to manage (i.e., to animate) along with your other game objects.
   * If the player wants their Iceman to turn to face a different direction then it is currently facing (by pressing one of the arrow keys), then the Iceman’s direction should be adjusted to the indicated direction but the Iceman must not move in that direction. For example, if the Iceman is currently facing up, and the player hits the right arrow key, then the Iceman should turn to face right, but not move right.
   * Else, if the Iceman is already facing in a particular direction and the user hits the arrow key to move in that same direction, AND the Iceman is allowed to move in that direction (e.g., there is no Boulder in the way, and the position doesn’t take the Iceman outside of the oil field), then your code must use the GraphObject’s `moveTo()` method to adjust the Iceman’s location by one square in the indicated direction.

Valid coordinates for the Iceman are from `x=0,y=0` to `x=60,y=60`, inclusive. Moreover, the Iceman cannot occupy a square that is less than or equal to a radius of 3 away from the center of any Boulder.

* If the player presses the `Z` or `z` keys and the Iceman has one or more sonar charges remaining in his inventory, then this will cause the Iceman to use his sonar charge to illuminate the contents of the oil field within a radius of `12` of his location:
  * The count of sonar charges held by the Iceman must be decremented by `1`.
  * All hidden game objects (e.g., Gold Nuggets or Barrels of oil) that are within a radius of `12` (e.g., this includes `11.99` squares away) must be made visible via `setVisible()` and revealed to the player.

* If the player presses the `TAB` key and they have one or more units of gold in their inventory, then they must add a Gold Nugget object into the oil field at their current `x,y` location and reduce their gold count by `1` unit. The dropped Gold Nugget must have a temporary state and a lifetime of `100` game ticks, and is only pickup-able by Protesters (either Regular or Hardcore). Such a dropped Nugget will start out in a visible state.

### What the Iceman Must Do When It Is Annoyed
When the Iceman is annoyed (i.e., shouted at by a Protester), its hit-points should be decremented by the appropriate amount (e.g., `2` points). Hint: All objects that can be annoyed should have some type of method that can be called to annoy them.

If the Iceman’s hit-points reach zero or below due to being annoyed, the Iceman must set its object’s state to dead, and then play an “I give up” sound effect: `SOUND_PLAYER_GIVE_UP`. Note: The StudentWorld class should check the Iceman’s status during each tick and if he transitions to a dead state, it should return the appropriate value indicating that the player lost a life.

### Getting Input From the User

Since Iceman is a real-time game, you can’t use the typical `getline` or `cin` approach to get a user's key press within the player’s `doSomething()` method. This would stop your program and wait until the user types in the proper data and hits the Enter key. This would make for a really boring game (requiring the user to hit a directional key then hit Enter, then hit a direction key, then hit Enter, etc.). Instead, you will need to use a special function that we provide in our `GameWorld` class (which your `StudentWorld` class is derived from) called `getKey()` to get input from the user.

This function rapidly checks to see if the user hit a key. If the user hit a key, the function returns true and the int variable passed to it is set to the code for the key. Otherwise, the function immediately returns false, meaning that no key was hit. This function could be used as follows:

```cpp
void Iceman::doSomething()
{
    ...
    int ch;
    if (getWorld()->getKey(ch) == true)
    {
        // user hit a key this tick!

        switch (ch)
        {
            case KEY_PRESS_LEFT:
                ... move player to the left ...;
                break;
            case KEY_PRESS_RIGHT:
                ... move player to the right ...;
                break;
            case KEY_PRESS_SPACE:
                ... add a Squirt in front of the player...;
                break;
            // etc...
        }
    }
    ...
}

```

# Ice

Here are the requirements you must meet when implementing the Ice class. Ice doesn't really do much. It just sits still in place.

### What Ice Must Do When It Is Created

When it is first created:

-   A Ice object must have an image ID of `IID_ICE`.
-   Each Ice object must have its `x,y` location specified for it -- the `StudentWorld` class can pass in this `x,y` location when constructing a new Ice object (e.g., when constructing the entire oil field).
-   Each Ice object must start out facing rightward.

Ice has the following graphic parameters:

-   It has an image depth of 3 -- meaning its graphic image should always be in the background (all other game objects have smaller depth values).
-   It has a size of .25, meaning it occupies only a 1x1 square in the oil field.

Iceman's `doSomething()` method first gets a pointer to its world via a call to `getWorld()` (a method in one of its base classes that returns a pointer to a `StudentWorld`), and then uses this pointer to call the `getKey()` method.

In addition to any other initialization that you decide to do in your Ice class, a Ice object must set itself to be visible using the `GraphObject` class's `setVisible()` method, e.g.:

```cpp
setVisible(true);
```

### What a Ice Object Must Do During a Tick

It's ice -- what do you expect it to do? It does nothing! As such, it doesn't need to have a `doSomething()` method... Or if it does have one, it doesn't need to do anything.

### What a Ice Object Must Do When It Is Annoyed

Ice objects cannot be annoyed (i.e., when a Squirt collides with them). After all, if you were Ice, would you be annoyed if you were squirted with water?

Boulders
========

You must create a class to represent a Boulder. Boulders basically sit around until the Ice underneath them has been dug away, and then after a short delay, they fall down until they hit the bottom of the shaft and disintegrate. Here are the requirements you must meet when implementing the Boulder class.

What a Boulder object Must Do When It Is Created
------------------------------------------------

When it is first created:

-   The Boulder object must have an image ID of `IID_BOULDER`.
-   A Boulder object must have its x,y location specified for it -- the `StudentWorld` class can pass in this x,y location when constructing a new Boulder object.
-   Boulders start out in a stable state (more on this below).
-   Boulders start out facing downward.
-   Boulders have the following graphic parameters:
    -   They have an image depth of 1 -- behind actors like Protesters, but above Ice.
    -   They have a size of 1.0

In addition to any other initialization that you decide to do in your Boulder class, a Boulder object must set itself to be visible using the GraphObject class's `setVisible()` method, e.g.:

```cpp
setVisible(true);
```

What the Boulder Object Must Do During a Tick
---------------------------------------------

Each time the Boulder object is asked to do something (during a tick), it should:

-   Check to see if it's still alive. If not, its `doSomething()` method should immediately return.
-   If the Boulder is currently in the stable state, then it must check to see if there is any Ice in the 4 squares immediately below it. For example, if the Boulder is at location x=20,y=30, it would check squares (20,29), (21,29), (22,29) and (23,29) for Ice. If there is any Ice below the Boulder, it does nothing -- after all it's a dumb rock. However, if none of the 4 squares beneath the Boulder have any Ice, then the Boulder must transition into a waiting state:
    -   It must enter a waiting state for the next 30 ticks.
-   If the Boulder is in a waiting state and 30 ticks have elapsed, then it must transition into a falling state and play the sound `SOUND_FALLING_ROCK`.
-   If the Boulder is in a falling state, then:
    -   It must continue to move downward one square during each tick until it either (a) hits the bottom of the oil field (i.e., it tries to move to y=-1), (b) runs into the top of another Boulder, or (c) it runs into Ice (i.e., by moving down a square, the Boulder would overlap over one or more Ice objects). When any of the above conditions are met the Boulder must set its state to dead so it can be removed from the game at the end of the current tick.
    -   If the Boulder comes within a radius of 3 (i.e. less than or equal to 3 squares, so 2.99 would count) of any Protester(s) or the Iceman while falling, it must cause 100 points of annoyance to those actors (effectively completely annoying them in one fell swoop). The Boulder will continue falling down as described above, even if it annoys one or more Protesters on its way down (i.e., it won't stop falling if it runs into a Protester). However, if the Boulder annoys the Iceman, the player will instantly lose a life.

What a Boulder Must Do When It Is Annoyed
-----------------------------------------

Boulders cannot be annoyed!

## Squirt

You must create a class to represent a Squirt from a squirt gun. A Squirt object will be introduced into the oil field by the Iceman when he shoots his squirt gun, and will then travel 4 squares in its initially-facing direction or until it hits any Ice, a Protester of any type, or a Boulder. Here are the requirements you must meet when implementing the Squirt class.

### What a Squirt object Must Do When It Is Created

When it is first created:
- The Squirt object must have an image ID of `IID_WATER_SPURT`.
- All Squirt objects must have their `x,y` location specified for them by the Iceman.
- All Squirt objects must have their direction specified for them by the Iceman.
- All Squirt objects start off with an initial travel distance of 4 squares
- All Squirt objects have the following graphic parameters:
  - They have an image depth of 1 – behind actors like Protesters, but above Ice
  - They have a size of 1.0
- In addition to any other initialization that you decide to do in your Squirt class, a Squirt object must set itself to be visible using the GraphObject class’s `setVisible()` method, e.g.: `setVisible(true);`

### What the Squirt Object Must Do During a Tick

Each time the Squirt object is asked to do something (during a tick):
- If a Squirt is within a radius of 3.0 of one or more Protesters (up to and including a distance of 3.0 squares away), it will cause 2 points of annoyance to these Protester(s), and then immediately set its state to dead, so it can be removed from the oil field at the end of the tick.
- If a Squirt has traveled through its full travel distance, then it immediately sets its state to dead, so it can be removed from the oil field at the end of the current tick.
- Otherwise, the Squirt must check to see if it can move one square in its currently-facing direction. If this target location is occupied by either Ice or a Boulder, then the Squirt immediately sets its state to dead so it can be removed from the oil field at the end of the current tick.
- Otherwise, the Squirt moves one square forward in its currently-facing direction, and then returns.

### What a Squirt Must Do When It Is Annoyed

Squirts can’t be annoyed, silly.

Barrel of Oil
=============

You must create a class to represent a Barrel of oil that needs to be picked up by the Iceman. Here are the requirements you must meet when implementing the Barrel class.

What a Barrel object Must Do When It Is Created
-----------------------------------------------

When it is first created:

1.  All Barrels must have an image ID of `IID_BARREL`.
2.  All Barrels must have their x,y location specified for them when they are created.
3.  All Barrels must start off facing rightward.
4.  All Barrels start out invisible -- they must be discovered (by the Iceman walking in close proximity to them) before they become visible.
5.  Barrels have the following graphic parameters:

-   They have an image depth of 2 -- behind actors like Protesters, but above Ice
-   They have a size of 1.0

What the Barrel Object Must Do During a Tick
--------------------------------------------

Each time the Barrel object is asked to do something (during a tick):

-   The object must check to see if it is currently alive. If not, then its `doSomething()` method must return immediately -- none of the following steps should be performed.
-   Otherwise, if the Barrel is not currently visible AND the Iceman is within a radius of 4.0 of it (<= 4.00 units away), then:
    -   The Barrel must make itself visible with the `setVisible()` method.
    -   The Barrel's `doSomething()` method must immediately return.
-   Otherwise, if the Barrel is within a radius of 3.0 (<= 3.00 units away) from the Iceman, then the Barrel will activate, and:
    -   The Barrel must set its state to dead (so that it will be removed by your StudentWorld class from the game at the end of the current tick).
    -   The Barrel must play a sound effect to indicate that the player picked up the Goodie: `SOUND_FOUND_OIL`.
    -   The Barrel must increase the player's score by 1000 points.
    -   If necessary, the Barrel may inform the StudentWorld object that it was picked up. Once all Barrels on the level have been picked up, the player finishes the level and may advance to the next level.

What a Barrel Must Do When It Is Annoyed
----------------------------------------

Barrels can't be attacked and will not block Squirts from the Iceman's squirt gun (they pass right over the Barrels).

Gold Nugget
-----------

You must create a class to represent a Gold Nugget. If the Iceman picks up a Gold Nugget, he can then drop it into the oil field at a later time to bribe a Protester (of either type). Here are the requirements you must meet when implementing the Gold Nugget class.

### What a Gold Nugget object Must Do When It Is Created

-   When it is first created:
-   All Gold Nuggets must have an image ID of `IID_GOLD`.
-   All Gold Nuggets must have their x,y location specified for them when they are created.
-   All Gold Nuggets must start off facing rightward.
-   A Gold Nugget may either start out invisible or visible -- this must be specified by the code that creates the Nugget, depending on the context of its creation. Nuggets buried within the Ice of the oil field always start out invisible, whereas Nuggets dropped by the Iceman start out visible.
-   A Gold Nugget will either be pickup-able by the Iceman or pickup-able by Protesters, but not both. This state must be specified by the code that creates the Gold Nugget object.
-   A Gold Nugget will either start out in a permanent state (where they will remain in the oil field until they are picked up by the Iceman or the level ends) or a temporary state (where they will only remain in the oil field for a limited number of ticks before disappearing or being picked up by a Protester). This state must be specified by the code that creates the Gold Nugget object.

Gold Nuggets have the following graphic parameters:

-   They have an image depth of 2 -- behind actors like Protesters, but above Ice.
-   They have a size of 1.0.

### What the Gold Nugget Object Must Do During a Tick

Each time the Gold Nugget object is asked to do something (during a tick):

-   The object must check to see if it is currently alive. If not, then its `doSomething()` method must return immediately -- none of the following steps should be performed.
-   Otherwise, if the Gold Nugget is not currently visible AND the Iceman is within a radius of 4.0 of it (<= 4.00 units away), then:
    -   The Gold Nugget must make itself visible with the `setVisible()` method.
    -   The Gold Nugget `doSomething()` method must immediately return.
-   Otherwise, if the Gold Nugget is pickup-able by the Iceman and it is within a radius of 3.0 (<= 3.00 units away) from the Iceman, then the Gold Nugget will activate, and:
    -   The Gold Nugget must set its state to dead (so that it will be removed by your `StudentWorld` class from the game at the end of the current tick).
    -   The Gold Nugget must play a sound effect to indicate that the Iceman picked up the Goodie: `SOUND_GOT_GOODIE`.
    -   The Gold Nugget increases the player's score by 10 points (This increase can be performed by the Iceman class or the Gold Nugget class).
    -   The Gold Nugget must tell the Iceman object that it just received a new Nugget so it can update its inventory.
-   Otherwise, if the Gold Nugget is pickup-able by Protesters and it is within a radius of 3.0 (<= 3.00 units away) from a Protester, then the Gold Nugget will activate, and:
    -   The Gold Nugget must set its state to dead (so that it will be removed by your `StudentWorld` class from the game at the end of the current tick

### What a Gold Nugget Must Do When It Is Annoyed
  - Gold Nuggets can't be attacked and will not block Squirts from the Iceman's squirt gun (they pass right over the Nuggets).

  Sonar Kit
=========

You must create a class to represent a `Sonar Kit`. If the `Iceman` picks up a `Sonar Kit`, he can use it to scan the oil field at a later time to locate buried Gold Nuggets and Barrels of oil. Here are the requirements you must meet when implementing the `Sonar Kit` class.

### What a Sonar Kit Object Must Do When It Is Created

When it is first created:

-   All `Sonar Kits` must have an image ID of `IID_SONAR`.
-   All `Sonar Kits` must have their x,y location specified for them when they are created.
-   All `Sonar Kits` must start off facing rightward.
-   All `Sonar Kits` starts out visible.
-   A `Sonar Kit` is only pickup-able by the `Iceman`.
-   A `Sonar Kit` will always start out in a temporary state (where they will only remain in the oil field for a limited number of ticks before disappearing) -- the number of ticks `T` a `Sonar Kit` will exist can be determined from the following formula:
```cpp
T = max(100, 300 – 10*current_level_number)
```

- `Sonar Kits` have the following graphic parameters:

    -   They have an image depth of 2 -- behind actors like Protesters, but above Ice.
    -   They have a size of 1.0

In addition to any other initialization that you decide to do in your `Sonar Kit` class, a `Sonar Kit` object must set itself to be visible using the `GraphObject` class's `setVisible()` method, e.g.:
```cpp
setVisible(true);
```

### What the Sonar Kit Object Must Do During a Tick

Each time the `Sonar Kit` object is asked to do something (during a tick):

-   The object must check to see if it is currently alive. If not, then its `doSomething()` method must return immediately -- none of the following steps should be performed.
-   Otherwise, if the `Sonar Kit` is within a radius of 3.0 (<= 3.00 units away) from the `Iceman`, then the `Sonar Kit` will activate, and:
    -   The `Sonar Kit` must set its state to dead (so that it will be removed by your `StudentWorld` class from the game at the end of the current tick).
    -   The `Sonar Kit` must play a sound effect to indicate that the `Iceman` picked up the `Goodie`: `SOUND_GOT_GOODIE`.
    -   The `Sonar Kit` must tell the `Iceman` object that it just received a new `Sonar Kit` so it can update its inventory.
    -   The `Sonar Kit` increases the player's score by 75 points (This increase can be performed by the `Iceman` class or the `Sonar Kit` class).
-   Since the `Sonar Kit` is always in a temporary state, it will check to see if its tick lifetime has elapsed, and if so it must set its state to dead (so that it will be removed by your `StudentWorld` class from the game at the end of the current tick).

### What a Sonar Kit Must Do When It Is Annoyed

`Sonar Kits` can't be annoyed and will not block Squirts from the `Iceman's` squirt gun.

Water Pool
==========

You must create a class to represent a Water Pool. If the Iceman picks up Water, he can use it to increase the contents of his squirt gun. Here are the requirements you must meet when implementing the Water Pool class.

What a Water Pool object Must Do When It Is Created
---------------------------------------------------

When it is first created:

-   All Water Pools must have an image ID of `IID_WATER_POOL`.
-   All Water Pools must have their `x`,`y` location specified for them when they are created.
-   All Water Pools must start off facing rightward.
-   All Water Pools start out visible.
-   A Water Pool is only pickup-able by the Iceman.
-   A Water Pool will always start out in a temporary state (where they will only remain in the oil field for a limited number of ticks before disappearing) -- the number of ticks `T` that a Water Pool will exist can be determined from the following formula: `T = max(100, 300 -- 10*current_level_number)`
-   Water Pools have the following graphic parameters:
    -   They have an image depth of 2 -- behind actors like Protesters, but above Ice
    -   They have a size of 1.0

In addition to any other initialization that you decide to do in your Water Pool class, a Water Pool object must set itself to be visible using the GraphObject class's `setVisible()` method, e.g.:

```cpp
setVisible(true);
```

What a Water Pool Object Must Do During a Tick
----------------------------------------------

Each time a Water pool object is asked to do something (during a tick):

-   The object must check to see if it is currently alive. If not, then its `doSomething()` method must return immediately -- none of the following steps should be performed.
-   Otherwise, if the Water pool is within a radius of 3.0 (<= 3.00 units away) from the Iceman, then the Water pool will activate, and:
    -   The Water pool must set its state to dead (so that it will be removed by your StudentWorld class from the game at the end of the current tick).
    -   The Water pool must play a sound effect to indicate that the Iceman picked up the Goodie: `SOUND_GOT_GOODIE`.
    -   The Water pool must tell the Iceman object that it just received 5 new squirts of water so it can update its inventory.
    -   The Water pool increases the player's score by 100 points (This increase can be performed by the Iceman class or the Sonar Kit class).
-   Since the Pool of Water is always in a temporary state, it will check to see if its tick lifetime has elapsed, and if so it must set its state to dead (so that it will be removed by your StudentWorld class from the game at the end of the current tick).

What a Water Pool Must Do When It Is Annoyed
--------------------------------------------

Water Pools can't be annoyed and will not block Squirts from the Iceman's squirt gun.

# Regular Protesters

You must create a class to represent a Regular Protester. Here are the requirements you must meet when implementing a Regular Protester class.

## What a Regular Protester object Must Do When It Is Created

When it is first created:

- Each Regular Protester must have an image ID of `IID_PROTESTER`.
- Each Regular Protester must start out facing left.
- Each Regular Protester must decide how many squares, `numSquaresToMoveInCurrentDirection`, it will decide to move left before possibly switching its direction. This value must be: `8 <= numSquaresToMoveInCurrentDirection <= 60`
- Each Regular Protester starts out with 5 hit-points.
- Each Regular Protester starts out NOT in a leave-the-oil-field state.
- Each Regular Protester have the following graphic parameters:
  - It has an image depth of 0 – they’re always in the foreground.
  - It has a size of 1.0.

In addition to any other initialization that you decide to do in your Regular Protester class, a Regular Protester object must set itself to be visible using the `GraphObject` class’s `setVisible()` method, e.g.:

```cpp
setVisible(true);
```

What a Regular Protester Must Do During a Tick
----------------------------------------------

Regular Protesters, unlike the player, don't necessarily get to take an action during every tick of the game (this is to make the game easier to play, since if Regular Protesters moved once every tick, they'd move much faster than the typical player can think and hit the keys on the keyboard). The Regular Protester must therefore compute a value indicating how often they're allowed to take an action (e.g., once every N ticks). This number of ticks (also known as "resting ticks") may be computed as follows:

```cpp
int ticksToWaitBetweenMoves = max(0, 3 – current_level_number/4)
```

So if the value of ticksToWaitBetweenMoves was 3, then the Regular Protester must "rest" for 3 ticks and may perform its normal behavior every 4th tick. If the value is zero, then the Regular Protester does something during every tick of the game.

### Here is what a Regular Protester must do during *every* tick:

1. The Regular Protester must check to see if it is currently alive. If not, then its `doSomething()` method must return immediately -- none of the following steps should be performed.
2.  If the Regular Protester is in a "rest state" during the current tick, it must do nothing other than update its resting tick count, and immediately return.
3.   Otherwise, if the Regular Protester is in a leave-the-oil-field state (because their hit points reached zero due to being repeatedly squirted by the Iceman's squirt gun or bonked by a falling Boulder), then:
    - If the Regular Protester is at its exit point (at `location x=60, y=60`) then it will immediately set its status to dead so that it will be removed from the game at the end of the current tick (by your StudentWorld class).
    - Otherwise, the Regular Protester must move one square closer to its exit point (at `x=60, y=60`). It must determine what direction to move based on a queue-based maze-searching algorithm like the one we learned in class. This should be done using concurrent programming (i.e., threads, async). The Regular Protester may not walk through Ice or Boulders to reach its exit point (meaning that none of the 16 squares that comprise the 4x4 Regular Protester icon may overlap with an Ice object and that he Regular Protester must not come within (within means `<=`) a distance of 3.0 units of any Boulders).
    - Hint: It’s inefficient for every single Regular Protester to try to figure out its own optimal path to the exit, so see if you can figure out a way to compute a single data structure that enables all Protesters to quickly determine their optimal path to their common exit point of `60,60`, no matter where they are located in the oil field.

c. After moving one step toward their exit point, the Regular Protester will return immediately. It will not perform any of the following steps.

4. Otherwise, the Regular Protester will check to see if they are within a distance of 4 units of the Iceman, AND they are currently facing in the Iceman’s direction2. If both are true and the Regular Protester hasn’t shouted within its last non-resting 15 ticks3, then the Regular Protester will:
    a. Play the shouting sound: `SOUND_PROTESTER_YELL`
    b. Inform the Iceman that he’s been annoyed for a total of 2 annoyance points (deducting 2 points from the Iceman’s hit points, and possibly causing the Iceman to become sufficiently annoyed to quit the level (aka die)).
    c. Update some state variable in a manner that prevents this Regular Protester from shouting again for at least 15 non-resting ticks.
    d. Return immediately.

   >  Footnote
    > 2.  For example, if the Iceman is at location `x=0,y=10` and the Regular Protester is facing left at location `x=4`, with a `6<=y<=14`, then the Regular Protester would be facing the Iceman. Similarly, a Regular Protester at `x=3`, `y=9` facing up would also be facing the Iceman.
     > 3. `A non-resting tick` is one in which the Protester was not resting, and its `doSomething() method` actually was able to perform a substantive activity like moving, shouting, etc.

5. Otherwise, if the Regular Protester:
- Is in a straight horizontal or vertical line of sight to the Iceman (even if the Regular Protester isn’t currently facing the Iceman), and
- Is more than 4 units away from the Iceman – that is, the radius from the Regular Protester and the Iceman is greater than 4.0 units away, and
- Could actually move the entire way to the Iceman with no Ice or Boulders blocking its path4 (assuming it kept walking straight over the next N turns),
#### Then the Regular Protester will:
- Change its direction to face in the direction of the Iceman, AND then take one step toward him.
- The Regular Protester will set its `numSquaresToMoveInCurrentDirection` value to zero, forcing it to pick a new direction/distance to move during its next non-resting tick (unless of course, the Regular Protester still sees theIceman in its line of sight, in which case it will continue to move toward the Iceman).
#### Then the Regular Protester will immediately return.
 6. Otherwise, the Regular Protester can’t directly see the Iceman. As such, it will decrement its `numSquaresToMoveInCurrentDirection` variable by one. If the Regular Protester has finished walking `numSquaresToMoveInCurrentDirection` steps in its currently-selected direction (i.e., `numSquaresToMoveInCurrentDirection <= 0`), then:
   - The Regular Protester will pick a random new direction to move (up, down, left or right).
   -  If the random direction is blocked either by Ice or a Boulder such that it can’t take even a single step in that chosen direction, then it will select a different direction and check it for blockage (it will continue checking directions until it has picked a direction that is not blocked).
   -  The Regular Protester will then change its direction to this new chosen direction.
   - The Regular Protester will then pick a new value for `numSquaresToMoveInCurrentDirection` that will govern how far it should move in the selected direction over the next `numSquaresToMoveInCurrentDirection` non-resting ticks. The value must be such that: `8 <= numSquaresToMoveInCurrentDirection <= 60`.
   - The Regular Protester will then continue with step 8.

7. Otherwise, if the Regular Protester:

a.  Is sitting at an intersection where it could turn and move at least one square in a perpendicular direction from its currently facing direction (e.g., it is currently facing left, and is at a junction where it could turn and move one step either upward/downward without being blocked by Ice or a Boulder), and
b.  The Regular Protester hasn't made a perpendicular turn in the last 200 non-resting ticks.

#### Then the Regular Protester will:

-  Determine which of the two perpendicular directions are viable (a viable direction is one that allows movement of at least one square without the Regular Protester being blocked by Ice or a Boulder).
-  Pick a viable perpendicular direction. If both perpendicular directions are viable, then pick one of the two choices randomly.
-  Set its direction to the selected perpendicular direction.
-  Pick a new value for `numSquaresToMoveInCurrentDirection` that will govern how far it should move in the selected perpendicular direction over the next `numSquaresToMoveInCurrentDirection` non-resting ticks. The value must be such that: `8 <= numSquaresToMoveInCurrentDirection <= 60`.
-  Remember that it made a perpendicular turn so that it doesn't make another perpendicular turn for at least 200 more non-resting ticks.
-  Continue on with the next step.
-  Finally, the Regular Protester will then attempt to take one step in its currently facing direction (which, by the way, might have just been changed by one of the last few steps above).
-  If the Regular Protester is for some reason blocked from taking a step in its currently facing direction, it will set the `numSquaresToMoveInCurrentDirection` to zero, resulting in a new direction being chosen during the Regular Protester's next non-resting tick (but not the current tick -- the Regular Protester must do nothing during the current tick).```

    > Note that only Ice and Boulders block a Regular Protester from moving.

Regular Protesters can occupy the same square as all other game objects including the Iceman and other Protesters.

#### What the Regular Protester Must Do When It Is Annoyed

-   A Regular Protester can't be further annoyed once it is in a leave-the-oil-field state -- this means it can't be squirted or bonked by Boulders while in this state.

-   When the Regular Protester is annoyed (e.g., by being hit by a Squirt object fired by the Iceman or being bonked by a Boulder), its hit-points should be decremented by the appropriate amount (the amount is specified elsewhere in this document).

-   If, after its hit-points have been decremented, the Regular Protester hasn't been completely annoyed (to the point it wants to leave the oil field) then it must play a sound of: `SOUND_PROTESTER_ANNOYED`. It will then be "stunned" and placed in a resting state for N resting ticks, where:

    `N = max(50, 100 -- current_level_number * 10)`

    > Note: This essentially extends the Regular Protester's normal resting state to N ticks. Remember, that when in a resting state, the Regular Protester will immediately return when its `doSomething()` method is called.

-   On the other hand, if the Regular Protester's hit-points reach zero or below due to being annoyed for any reason, the Regular Protester:

    -   Transitions into a leave-the-oil-field state.
    -   Plays an "I give up" sound effect: `SOUND_PROTESTER_GIVE_UP`.
    -   Sets its resting tick count to zero, ensuring that it will do something on the very next game tick, even if it was previously stunned or otherwise in a resting state.
    -   If the Regular Protester was annoyed due to being bonked by a Boulder, then it will increase the player's score by 500 points.
    -   On the other hand, if the Regular Protester was annoyed due to being squirted repeatedly, then it will increase the player's score by 100 points.

#### What the Regular Protester Must Do When It Picks up a Gold Nugget

Hardcore Protesters
-------------------

You must create a class to represent a Hardcore Protester. Here are the requirements you must meet when implementing a Hardcore Protester class.

### What a Hardcore Protester object Must Do When It Is Created

When it is first created:

-   Each Hardcore Protester must have an image ID of `IID_HARD_CORE_PROTESTER`.
-   Each Hardcore Protester must start out facing left.
-   Each Hardcore Protester must decide how many squares, `numSquaresToMoveInCurrentDirection`, it will decide to move left before possibly switching its direction. This value must be: `8 <= numSquaresToMoveInCurrentDirection <= 60`
-   Each Hardcore Protester starts out with 20 hit-points.
-   Each Hardcore Protester starts out NOT in a leave-the-oil-field state.
-   Each Hardcore Protester have the following graphic parameters:
    -   It has an image depth of 0 -- they're always in the foreground
    -   It has a size of 1.0

In addition to any other initialization that you decide to do in your Hardcore Protesters class, a Hardcore Protester object must set itself to be visible using the GraphObject class's `setVisible()` method, e.g.:

When a Gold Nugget has activated due to being stepped upon by a Regular Protester, it will notify the Regular Protester that it has picked up a Nugget. The Regular Protester must do the following in response to being notified that it has just stepped upon a Nugget:

-   The Regular Protester plays an "I'm rich" sound effect: `SOUND_PROTESTER_FOUND_GOLD`.
-   The Regular Protester increases the player's score by 25 points for the bribery.
-   The Regular Protester will immediately be bribed and transition into a leave-the-oil-field state.
```cpp
setVisible(true);
```
### What a Hardcore Protester Must Do During a Tick
Hardcore Protesters, unlike the player, don't necessarily get to take an action during every tick of the game (this is to make the game easier to play, since if Hardcore Protesters moved once every tick, they'd move much faster than the typical user can think and hit the keys on the keyboard). The Hardcore Protester must therefore compute a value indicating how often they're allowed to take an action (e.g., once every N ticks). This number of ticks (also known as "resting ticks") may be computed as follows:
```cpp
int  ticksToWaitBetweenMoves  = max(0, 3 -- current_level_number/4)
```
So if the value of `ticksToWaitBetweenMoves` was 3, then the Hardcore Protester must "rest" for 3 ticks and may perform its normal behavior every 4th tick. If the value is zero, then the Hardcore Protester does something during every tick of the game.

Here is what a Hardcore Protester must do during *every* tick:

The Hardcore Protester must check to see if it is currently alive. If not, then its `doSomething()` method must return immediately -- none of the following steps should be performed.

If the Hardcore Protester is in a "rest state" during the current tick, it must do nothing other than update its resting tick count, and immediately return.

Otherwise, if the Hardcore Protester is in a leave-the-oil-field state (because their hit points reached zero due to being repeatedly squirted by Squirt objects fired from the Iceman's squirt gun or bonked by a falling Boulder), then:

-   If the Hardcore Protester is at its exit point (at location `x=60`, `y=60`) then it will immediately set its status to dead so that it will be removed from the game at the end of the current tick (by your `StudentWorld` class).
-   Otherwise, the Hardcore Protester must move one square closer to its exit point (at `x=60`, `y=60`). It must determine what direction to move based on a queue-based maze-searching algorithm like the one we learned in class. This should be done using concurrent programming (i.e., threads, async). The Hardcore Protester may not walk through Ice or Boulders to reach its exit point (meaning that none of the 16 squares that comprise the 4x4 Hardcore Protester icon may overlap with Ice and that the Hardcore Protester must not come within (within means `<=`) a distance of `3.0` units of any Boulders). Hint: It's inefficient for every single Hardcore Protester to try to figure out its own optimal path to their common exit point of `60,60`, so see if you can figure out a way to compute a single data structure that enables all Protesters to quickly determine their optimal path to their common exit, no matter where they are located in the oil field.
-   After moving one step toward their exit point, the Hardcore Protester will return immediately. It will not perform any of the following steps.

Otherwise, the Hardcore Protester will check to see if they are within a distance of `4` units of the Iceman, AND they are currently facing in the Iceman's direction. If both are true and the Hardcore Protester hasn't shouted within the last non-resting `15` ticks, then the Hardcore Protester will:

-   Play the shouting sound: `SOUND_PROTESTER_YELL`
-   Inform the Iceman that he's been annoyed for a total of `2` annoyance points (deducting `2` points from the Iceman's hit points, and possibly causing the Iceman to become sufficiently annoyed to quit the level (aka die)).
-   Update some state variable in a manner that prevents this Hardcore Protester from shouting again for at least `15` non-resting ticks.
-   Return immediately.

Otherwise, if the Hardcore Protester is more than `4.0` units away from the Iceman, the Hardcore Protester will:

-   Compute a value `M`, such that `M = 16 + current_level_number * 2`
-   If the Hardcore Protester is less than or equal to a total of `M` legal horizontal or vertical moves away from the current location of the Iceman (as can be determined using the same basic queue-based maze-searching algorithm described in Hardcore Protester item 3.b above), then the Hardcore Protester will sense the Iceman's cell phone signal and know where he is. This is true even if the Hardcore Protester has no direct line of sight to the Iceman, so long as he can be reached in M moves without digging through Ice or going through a Boulder. In such a situation, the Hardcore Protester will:

     -  Determine which horizontal/vertical direction to move in (as dictated by its maze-searching algorithm) such that if it were to make such a move it would be one square closer to the Iceman.

     - Change its current direction to face this new direction.

5. For example, if the Iceman is at location `x=0,y=10` and the Regular Protester is facing left at location `x=4`, with `6<=y<=14`, then the Regular Protester would be facing the Iceman. Similarly, a Regular Protester at `x=3, y=9` facing up would also be facing the Iceman.

Move one square in this direction such that after the move it is one square closer to the Iceman’s current location.

Return immediately.

6. Otherwise, if the Hardcore Protester:

- Is in a straight horizontal or vertical line of sight to the Iceman (even if the Hardcore Protester isn’t currently facing the Iceman), and
- Is more than 4 units away from the Iceman – that is the radius from the Hardcore Protester and the Iceman is greater than 4.0 units away, and
- Could actually move the entire way to the Iceman with no Ice or Boulders blocking its path6 (assuming it kept walking straight over the next N turns),

Then the Hardcore Protester will:

- Turn to face the Iceman and take one step toward him.
- The Hardcore Protester will set its `numSquaresToMoveInCurrentDirection` value to zero, forcing it to pick a new direction/distance to move during its next non-resting tick (unless of course, the Hardcore Protester still sees the Iceman in its line of sight).
- Then the Hardcore Protester will immediately return.

Otherwise, the Hardcore Protester will decrement its `numSquaresToMoveInCurrentDirection` variable by one. If the Hardcore Protester has finished walking its `numSquaresToMoveInCurrentDirection` steps in its currently-selected direction (i.e., `numSquaresToMoveInCurrentDirection <= 0`), then:

- The Hardcore Protester will pick a random new direction to move in (up, down, left or right).
- If the random direction is blocked either by Ice or a Boulder such that it can’t take even a single step in that chosen direction, then it will select a different direction and check it for blockage (it will continue checking directions until it has picked a direction that is not blocked).
- The Hardcore Protester will then change its direction to this new chosen direction.
- The Hardcore Protester will then pick a new value for `numSquaresToMoveInCurrentDirection` that will govern how far it should move in the selected direction over the next `numSquaresToMoveInCurrentDirection` non-resting ticks. The value must be such that: `8 <= numSquaresToMoveInCurrentDirection <= 60`.
- The Hardcore Protester will then continue with step 8.

Otherwise, if the Hardcore Protester:

a. Is sitting at an intersection where it could turn and move at least one square in a perpendicular direction from its currently facing direction (e.g., it is currently facing left, and is at a junction where it could turn and move one step either upward/downward without being blocked by Ice or a Boulder), and
6 A Regular Protester cannot move to a location that is within a radius of 3 (`<= 3.0`) units of a Boulder. 

b. The Hardcore Protester hasn’t made a perpendicular turn in the last 200 non-resting ticks. 
#### Then the Hardcore Protester will:

c. Determine which of the two perpendicular directions are viable (a viable direction is one that allows movement of at least one square without the Hardcore Protester being blocked by Ice or a Boulder).
-  Pick a viable perpendicular direction. If both perpendicular directions are viable, then pick one of the two choices randomly.
-    Set its direction to the selected perpendicular direction.
- Pick a new value for `numSquaresToMoveInCurrentDirection` that will govern how far it should move in the selected perpendicular direction over the next `numSquaresToMoveInCurrentDirection` non-resting ticks. The value must be such that: `8 <= numSquaresToMoveInCurrentDirection <= 60`.
-   Remember that it made a perpendicular turn so that it doesn’t make another perpendicular turn for at least 200 more non-resting ticks.
-  Continue on with the next step.
- Finally, the Hardcore Protester will then attempt to take one step in its currently facing direction (which, by the way, might have just been changed by one of the last few steps above).
If the Hardcore Protester is for some reason blocked from taking a step in its currently facing direction, it will set the `numSquaresToMoveInCurrentDirection` to zero, resulting in a new direction being chosen during the Hardcore Protester’s next non-resting tick (but not the current tick – the Hardcore Protester must do nothing during the current tick).

   > Note that only Ice and Boulders block a Hardcore Protester from moving. Hardcore Protesters can occupy the same square as all other game objects including the Iceman and other Protesters.

### What the Hardcore Protester Must Do When It Is Annoyed

A Hardcore Protester can’t be further annoyed once it is in a leave-the-oil-field state – this means it can’t be squirted or bonked by Boulders while in this state.

When the Hardcore Protester is annoyed (e.g., by being squirted by the Iceman or being bonked by a Boulder), its hit-points should be decremented by the appropriate amount (the amount is specified elsewhere in this document).

If, after its hit-points have been decremented, the Hardcore Protester hasn’t been completely annoyed (to the point it wants to leave the oil field) then it must play a sound of: `SOUND_PROTESTER_ANNOYED`. It will then be “stunned” and placed in a resting state for `N` resting ticks, where:
```cpp
N = max(50, 100 – current_level_number * 10)
```

   > Note this essentially extends the Hardcore Protester's normal resting state to `N` ticks. Remember that when in a resting state, the Hardcore Protester will immediately return when its `doSomething()` method is called.

On the other hand, if the Hardcore Protester's hit-points reach zero or below due to being annoyed for any reason, the Hardcore Protester:

-   Transitions into a leave-the-oil-field state.
-   Plays an "I give up" sound effect: `SOUND_PROTESTER_GIVE_UP`.
-   Sets its resting tick count to zero, ensuring that it will do something on the very next game tick, even if it was previously stunned or otherwise in a resting state.

If the Hardcore Protester was annoyed due to being bonked by a Boulder, then it will increase the player's score by 500 points. On the other hand, if the Hardcore Protester was annoyed into submission due to being squirted repeatedly, then it will increase the player's score by 250 points.

### What the Hardcore Protester Must Do When It Picks up a Gold Nugget

When a Gold Nugget has activated due to being stepped upon by a Hardcore Protester, it will notify the Hardcore Protester that it has picked up a Nugget. The Hardcore Protester must do the following in response to being notified that it has just stepped upon a Nugget:

-   The Hardcore Protester plays an "I'm rich!" sound effect: `SOUND_PROTESTER_FOUND_GOLD`.
-   The Hardcore Protester increases the player's score by 50 points for the bribery.
-   The Hardcore Protester will become fixated on the Nugget and will pause to stare at it (just as if he/she were in a resting state -- doing nothing else) for the following number of game ticks:
```cpp
ticks_to_stare = max(50, 100 -- current_level_number * 10)
```
After the specified number of game ticks, the Hardcore Protester will become bored with the Nugget and continue to pursue the Iceman using its normal algorithm, as described above.