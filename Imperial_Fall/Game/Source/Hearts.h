#ifndef __HEARTS_H__
#define __HEARTS_H__

#include "Module.h"
#include "Entities.h"
#include "Physics.h"
#include "Animation.h"
#include "DynArray.h"

class Hearts : public Entity
{
public:
	Hearts();

	virtual ~Hearts();

private:

	void InitCustomEntity();

	bool PreUpdate();

	bool Update(float dt);

	bool Draw();

	bool DeleteEntity();

	bool picked = false;

	bool plan_to_delete = false;

private:

	int w = 16, h = 16;

};

#endif