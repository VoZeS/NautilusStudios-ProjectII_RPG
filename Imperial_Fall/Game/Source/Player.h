#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Entities.h"
#include "Physics.h"
#include "Animation.h"

class Player : public Entity
{
public:
	Player();

	virtual ~Player();

private:
	void InitCustomEntity();

	bool PreUpdate();

	void HandleInput(float dt);

	bool Update(float dt);

	bool Draw();

	// load-save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	fPoint GetPlayerPosition();
	void SetPlayerPosition(int new_x, int new_y);
	void ImpulsePlayer();

private:
	int w = 20, h = 32;
	float speed = 0.3f;

public:
	Animation* currentAnimation = NULL;

	// A set of animations
	Animation idleAnimU;
	Animation idleAnimD;
	Animation idleAnimL;
	Animation idleAnimR;
	Animation walkAnimU;
	Animation walkAnimD;
	Animation walkAnimL;
	Animation walkAnimR;

	uint walk_sound;
	int walk_cd = 320;

	int look_dir; // 0 --> up, 1 --> down, 2 --> left, 3 --> right
};

#endif
