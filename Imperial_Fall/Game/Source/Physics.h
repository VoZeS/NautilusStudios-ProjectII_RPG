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
	Physics(bool enabled);

	virtual ~Physics();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	bool CreateMapBox(int x, int y, int w, int h, int collision);

	bool CreateDynamicBox(int x, int y, int w, int h);

	bool CleanMapBoxes();

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

	bool debug;
	b2World* world;

	int on_collosion;

	bool inRenato = false;
	bool inCurandero = false;
	bool inHerrero = false;
	bool inGranjero = false;
	bool inAldeano = false;

	//Soukoban Puzzles Colliders River Booleans
	bool isActive_S1 = true;
	bool isActive_S2 = true;
	bool isActive_S3 = true;
	bool isActive_S4 = true;
	bool isActive_S5 = true;
	bool isActive_S6 = true;

	bool GetInNPC(int npc)
	{
		bool ret;

		switch (npc)
		{
		case 1: ret = inRenato; break;
		case 2: ret = inCurandero; break;
		case 3: ret = inHerrero; break;
		case 4: ret = inGranjero; break;
		case 5: ret = inAldeano; break;
		}

		return ret;
	}

	uint save_sound;

};

#endif
