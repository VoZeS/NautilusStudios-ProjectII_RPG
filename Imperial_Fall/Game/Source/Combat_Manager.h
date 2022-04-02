#ifndef __COMBAT_MANAGER_H__
#define __COMBAT_MANAGER_H__

#include "Module.h"
#include "Menu.h"
#include "Animation.h"
#include "Point.h"
#include "Combat_Entities.h"

#define NUM_BUTTONS 7  //Bottones generales
#define NUM_ITEMS_BUTTONS 5
#define NUM_ENEMIES_BUTTONS 5
#define NUM_ALLIES_BUTTONS 5

class Combat_Entities;

class Combat_Manager : public Module
{
public:
	Combat_Manager();

	virtual ~Combat_Manager();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:
	bool in_combat = false;
	bool in_action = false;
	bool combat_init = false;

	Combat_Entities* turn_order[8];
	
	Combat_Entities* allies[4];
	Combat_Entities* enemies[4];
};

#endif