#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include "Module.h"
#include "Particle.h"

#include "Defs.h"
#include "Log.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;

class Particles : public Module
{
public:
	Particles();

	virtual ~Particles();

	bool Start();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, uint delay = 0);

	void PlayParticle(ANIM_EFFECT effect, int x, int y);

private:
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

public:
	Particle physic;
	Particle fire;
	Particle lightning;
	Particle water;
	Particle heal;
	Particle buff;
	Particle anti_heal;
};

#endif