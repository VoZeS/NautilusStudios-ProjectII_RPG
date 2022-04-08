#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Animation.h"
#include "Point.h"

struct Particle
{
public:
	Particle();

	Particle(const Particle& p);

	~Particle();

	bool Update();

public:
	// Defines the position in the screen
	iPoint position;

	// Defines the speed at which the particle will move (pixels per second)
	iPoint speed;

	// A set of rectangle sprites
	Animation anim;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool isAlive = false;
	bool isCreated = false;

	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	uint lifetime = 0;
};

#endif