#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Module.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y 0.0f

#define PIXELS_PER_METER 50.0f
#define METERS_PER_PIXEL 0.02f

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXELS_TO_METERS(p)  ((float) METERS_PER_PIXEL * p)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class Physics : public Module, public b2ContactListener
{
public:
	Physics();

	virtual ~Physics();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	bool CreateMapBox(int x, int y, int w, int h, int collision);

	bool CleanMapBoxes();

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

	bool debug;
	b2World* world;

	int on_collosion;

	bool inScareCrow = false;
	bool inWaterWell = false;
	bool inStatue = false;
	bool statueUsed = false;

	uint save_sound;
	uint water_well_sound;
	uint level_complete_sound;
	uint death_sound;

};

#endif
