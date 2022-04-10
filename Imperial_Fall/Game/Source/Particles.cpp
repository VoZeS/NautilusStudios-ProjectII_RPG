#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Combat_Manager.h"
#include "Combat_Menu.h"
#include "Player.h"
#include "Particles.h"
#include "Defs.h"
#include "Log.h"

Particles::Particles(bool enabled) : Module(enabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

Particles::~Particles()
{

}

bool Particles::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		texture = app->tex->Load("Assets/textures/particles.png");

		int pix = 128;
		float speed = 0.1f;

		// physic
		physic.anim.PushBack({ pix * 0, pix * 0, pix, pix });
		physic.anim.PushBack({ pix * 1, pix * 0, pix, pix });
		physic.anim.PushBack({ pix * 2, pix * 0, pix, pix });
		physic.anim.PushBack({ pix * 3, pix * 0, pix, pix });
		physic.anim.PushBack({ pix * 4, pix * 0, pix, pix });
		physic.anim.PushBack({ pix * 5, pix * 0, pix, pix });
		physic.anim.loop = false;
		physic.anim.speed = speed;

		// fire
		fire.anim.PushBack({ pix * 0, pix * 1, pix, pix });
		fire.anim.PushBack({ pix * 1, pix * 1, pix, pix });
		fire.anim.PushBack({ pix * 2, pix * 1, pix, pix });
		fire.anim.PushBack({ pix * 3, pix * 1, pix, pix });
		fire.anim.PushBack({ pix * 4, pix * 1, pix, pix });
		fire.anim.PushBack({ pix * 5, pix * 1, pix, pix });
		fire.anim.loop = false;
		fire.anim.speed = speed;

		// lightning
		lightning.anim.PushBack({ pix * 0, pix * 2, pix, pix });
		lightning.anim.PushBack({ pix * 1, pix * 2, pix, pix });
		lightning.anim.PushBack({ pix * 2, pix * 2, pix, pix });
		lightning.anim.PushBack({ pix * 3, pix * 2, pix, pix });
		lightning.anim.PushBack({ pix * 4, pix * 2, pix, pix });
		lightning.anim.PushBack({ pix * 5, pix * 2, pix, pix });
		lightning.anim.loop = false;
		lightning.anim.speed = speed;

		// water
		water.anim.PushBack({ pix * 0, pix * 3, pix, pix });
		water.anim.PushBack({ pix * 1, pix * 3, pix, pix });
		water.anim.PushBack({ pix * 2, pix * 3, pix, pix });
		water.anim.PushBack({ pix * 3, pix * 3, pix, pix });
		water.anim.PushBack({ pix * 4, pix * 3, pix, pix });
		water.anim.PushBack({ pix * 5, pix * 3, pix, pix });
		water.anim.loop = false;
		water.anim.speed = speed;

		// heal
		heal.anim.PushBack({ pix * 0, pix * 4, pix, pix });
		heal.anim.PushBack({ pix * 1, pix * 4, pix, pix });
		heal.anim.PushBack({ pix * 2, pix * 4, pix, pix });
		heal.anim.PushBack({ pix * 3, pix * 4, pix, pix });
		heal.anim.PushBack({ pix * 4, pix * 4, pix, pix });
		heal.anim.PushBack({ pix * 5, pix * 4, pix, pix });
		heal.anim.loop = false;
		heal.anim.speed = speed;

		// buff
		buff.anim.PushBack({ pix * 0, pix * 5, pix, pix });
		buff.anim.PushBack({ pix * 1, pix * 5, pix, pix });
		buff.anim.PushBack({ pix * 2, pix * 5, pix, pix });
		buff.anim.PushBack({ pix * 3, pix * 5, pix, pix });
		buff.anim.PushBack({ pix * 4, pix * 5, pix, pix });
		buff.anim.PushBack({ pix * 5, pix * 5, pix, pix });
		buff.anim.loop = false;
		buff.anim.speed = speed;

		// anti_heal
		anti_heal.anim.PushBack({ pix * 0, pix * 6, pix, pix });
		anti_heal.anim.PushBack({ pix * 1, pix * 6, pix, pix });
		anti_heal.anim.PushBack({ pix * 2, pix * 6, pix, pix });
		anti_heal.anim.PushBack({ pix * 3, pix * 6, pix, pix });
		anti_heal.anim.PushBack({ pix * 4, pix * 6, pix, pix });
		anti_heal.anim.PushBack({ pix * 5, pix * 6, pix, pix });
		anti_heal.anim.loop = false;
		anti_heal.anim.speed = speed;
	}

	return true;
}

bool Particles::Update(float dt)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return true;
}

bool Particles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			app->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return true;
}

bool Particles::CleanUp()
{
	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void Particles::AddParticle(const Particle& particle, int x, int y, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			particles[i] = p;
			break;
		}
	}
}

void Particles::PlayParticle(ATT_EFFECT att_effect, SUPP_EFFECT supp_effect, int x, int y)
{
	if (att_effect != ATT_EFFECT::EMPTY)
	{
		switch (att_effect)
		{
		case ATT_EFFECT::PHYSIC:
			AddParticle(physic, x, y);
			break;
		case ATT_EFFECT::FIRE:
			AddParticle(fire, x, y);
			break;
		case ATT_EFFECT::LIGHTNING:
			AddParticle(lightning, x, y);
			break;
		case ATT_EFFECT::WATER:
			AddParticle(water, x, y);
			break;
		case ATT_EFFECT::ANTI_HEAL:
			AddParticle(anti_heal, x, y);
			break;
		}
	}
	else if (supp_effect != SUPP_EFFECT::EMPTY)
	{
		switch (supp_effect)
		{
		case SUPP_EFFECT::HEAL:
			AddParticle(heal, x, y);
			break;
		case SUPP_EFFECT::BUFF:
			AddParticle(buff, x, y);
			break;
		}
	}
	
}