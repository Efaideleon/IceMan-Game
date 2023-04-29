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

