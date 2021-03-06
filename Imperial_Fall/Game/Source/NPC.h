#ifndef __NPC_H__
#define __NPC_H__

#include "Module.h"
#include "Entities.h"
#include "Physics.h"
#include "Animation.h"

class NPC : public Entity
{
public:
	NPC();

	virtual ~NPC();

private:
	void InitCustomEntity(int npc);

	bool PreUpdate();

	bool Update(float dt);

	bool Draw();

	// load-save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

private:
	int w = 20, h = 12;
	int npc_type = 0; // renato = 1, curandero = 2, herrero = 3, sabio = 4, aldeano = 5, granjero = 6, signal = 8

public:
	Animation* currentAnimation = NULL;

	// main Animations
	Animation idleAnim_renato;
	Animation idleAnim_vendedores;
};

#endif
