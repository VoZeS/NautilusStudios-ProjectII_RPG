#ifndef __COINS_H__
#define __COINS_H__

#include "Module.h"
#include "Entities.h"
#include "Physics.h"
#include "Animation.h"
#include "DynArray.h"

class Coins : public Entity
{
public:
	Coins();

	virtual ~Coins();

private:

	void InitCustomEntity();

	bool PreUpdate();

	bool Update(float dt);

	bool Draw();

	bool DeleteEntity();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	void ReloadCoin();

	bool picked = false;

	bool plan_to_delete = false;

private:
	Animation* currentAnimation = NULL;

	Animation idleAnim;

	int w = 16, h = 16;

};

#endif