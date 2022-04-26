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

#define MAX_COINS 9

struct Miscelenea
{
	b2Body* body;
	int number;
};

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

	bool CreateMiscelanea(int x, int y, int w, int h, int collision);

	bool CleanMapBoxes();

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

	bool debug;
	b2World* world;

	Miscelenea coins_in_floor[MAX_COINS];

	int on_collosion;

	bool inRenato = false;
	bool inCurandero = false;
	bool inHerrero = false;
	bool inGranjero = false;
	bool inAldeano = false;
	bool inCoins = false;

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

	bool coin_picked = false;
	int coins_number = 0;
	void DestroyCoins();
	void ResetMiscelanea();

	uint save_sound;

};

#endif
