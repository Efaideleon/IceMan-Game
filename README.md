# IceMan-Game
Introduction
============

ElCo corporate spies have learned that SanMo is planning to release a new game, called *Iceman*, and would like you to program an exact copy so ElCo can beat SanMo to the market. To help you, ElCo corporate spies have managed to steal a prototype *Iceman* executable file and several source files from the SanMo headquarters, so you can see exactly how your version of the game must work (see posted executable file) and even get a head start on the programming. Of course, such behavior would never be appropriate in real life, but for this project, you'll be a programming villain.

In *Iceman*, the player has to dig underground tunnels through an oil field looking for oil. After the player has gathered all available oil within a particular field, the level is completed and the player advances to a new, more difficult oil field.

Here is an example of what the *Iceman* game looks like:

![Figure #1: A screenshot of the Iceman game.](https://github.com/username/repository/blob/master/img/iceman.png)

You can see the *Iceman* (upper-right), two *Hardcore Protesters* in light blue (*Regular Protesters*, here not shown, are in dark blue, and one *Hardcore Protester* in light blue), several *Boulders*, two water pools, a sonar kit, a discovered *Barrel of oil*, and a discovered *Gold Nugget*.

Game Details
============

In *Iceman*, the player starts out a new game with three lives and continues to play until all of his/her lives have been exhausted. There are multiple levels in *Iceman*, beginning with level 0, and each level has its own unique oil field configuration. During each level, the *Iceman* (controlled by the player) must dig and find all of the oil hidden within the oil field in order to move on to the next level.

Upon starting each level, the player's *Iceman* avatar (a miner) is placed at the top-middle of the oil field just above the tunnel. Every time the player starts (or re-starts) a level, the *Iceman* is restored to 100% health, given fresh water for their squirt gun (enough for 5 squirts), and given a single sonar charge that they can use to search for nearby items within the ice. Each oil field has a number of *Boulders*, *Gold Nuggets*, and *Barrels* of oil randomly distributed throughout the field. Only the *Boulders* will be visible initially -- the other items must be discovered by the *Iceman* before they become visible. The player must use the arrow keys to move the *Iceman* left, right, up and down through the oil field; the *Iceman* digs through any ice in the direction of motion. The *Iceman* may move/dig anywhere in the oil field except for locations occupied by *Boulders*.

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

