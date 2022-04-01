#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Entities.h"
#include "Physics.h"
#include "Animation.h"

struct Companion
{
	int comp_number;
	fPoint position;
	b2Body* body;
	int look_dir = 1; // 0 --> up, 1 --> down, 2 --> left, 3 --> right
	Animation* currentAnimation = NULL;
};

class Player : public Entity
{
public:
	Player();

	virtual ~Player();

private:
	void InitCustomEntity(int npc);

	bool PreUpdate();

	void HandleInput(float dt);

	bool Update(float dt);

	bool Draw();

	// load-save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	fPoint GetPlayerPosition();
	void SetPlayerPosition(int new_x, int new_y);
	void SetPlayerLookDir(int lookDir);

	fPoint GetCompanion0Position();
	fPoint GetCompanion1Position();
	fPoint GetCompanion2Position();

	void SetCompanion0Position(int new_x, int new_y);
	void SetCompanion1Position(int new_x, int new_y);
	void SetCompanion2Position(int new_x, int new_y);

	void SetCompanion0LookDir(int lookDir);
	void SetCompanion1LookDir(int lookDir);
	void SetCompanion2LookDir(int lookDir);


	void ImpulsePlayer();

	int char_control = 0; // 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard
	int GetCharControl();

	void FollowPlayer(Companion c, Companion pre_c, float dt);
	Companion c0;
	Companion c1;
	Companion c2;

private:
	int w = 20, h = 32;
	float speed = 0.3f;
	bool collision_active;
	b2Fixture* bodyFixture;

public:
	Animation* currentAnimation = NULL;

	// main Animations
	Animation idleAnimU;
	Animation idleAnimD;
	Animation idleAnimL;
	Animation idleAnimR;
	Animation walkAnimU;
	Animation walkAnimD;
	Animation walkAnimL;
	Animation walkAnimR;

	// c0 Animations
	Animation c0_idleAnimU;
	Animation c0_idleAnimD;
	Animation c0_idleAnimL;
	Animation c0_idleAnimR;
	Animation c0_walkAnimU;
	Animation c0_walkAnimD;
	Animation c0_walkAnimL;
	Animation c0_walkAnimR;

	// c1 Animations
	Animation c1_idleAnimU;
	Animation c1_idleAnimD;
	Animation c1_idleAnimL;
	Animation c1_idleAnimR;
	Animation c1_walkAnimU;
	Animation c1_walkAnimD;
	Animation c1_walkAnimL;
	Animation c1_walkAnimR;

	// c2 Animations
	Animation c2_idleAnimU;
	Animation c2_idleAnimD;
	Animation c2_idleAnimL;
	Animation c2_idleAnimR;
	Animation c2_walkAnimU;
	Animation c2_walkAnimD;
	Animation c2_walkAnimL;
	Animation c2_walkAnimR;

	uint walk_sound;
	int walk_cd = 320;

	int look_dir; // 0 --> up, 1 --> down, 2 --> left, 3 --> right
};

#endif
