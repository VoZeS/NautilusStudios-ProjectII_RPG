#ifndef __INTROCUTSCENE_H__
#define __INTROCUTSCENE_H__

#include "Module.h"
#include "Physics.h"
#include "Animation.h"


struct _Mix_Music;
struct SDL_Texture;
enum class ENEMIES;

class Intro_Cutscene : public Module
{
public:

	Intro_Cutscene(bool enabled);

	// Destructor
	virtual ~Intro_Cutscene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool cutscene_finished = false;

private:
	SDL_Rect Wizard;
	SDL_Rect Tank;
	SDL_Rect Healer;
	SDL_Rect Assassin;

	SDL_Texture* assassin_texture = NULL;
	SDL_Texture* tank_texture = NULL;
	SDL_Texture* healer_texture = NULL;
	SDL_Texture* wizard_texture = NULL;

	Animation* W_currentAnimation = NULL;
	Animation* T_currentAnimation = NULL;
	Animation* H_currentAnimation = NULL;
	Animation* A_currentAnimation = NULL;

	// WIZARD main Animations
	Animation W_idleAnimU;
	Animation W_idleAnimD;
	Animation W_idleAnimL;
	Animation W_idleAnimR;
	Animation W_walkAnimU;
	Animation W_walkAnimD;
	Animation W_walkAnimL;
	Animation W_walkAnimR;

	// TANK main Animations
	Animation T_idleAnimU;
	Animation T_idleAnimD;
	Animation T_idleAnimL;
	Animation T_idleAnimR;
	Animation T_walkAnimU;
	Animation T_walkAnimD;
	Animation T_walkAnimL;
	Animation T_walkAnimR;

	// HEALER main Animations
	Animation H_idleAnimU;
	Animation H_idleAnimD;
	Animation H_idleAnimL;
	Animation H_idleAnimR;
	Animation H_walkAnimU;
	Animation H_walkAnimD;
	Animation H_walkAnimL;
	Animation H_walkAnimR;

	// ASSASSIN main Animations
	Animation A_idleAnimU;
	Animation A_idleAnimD;
	Animation A_idleAnimL;
	Animation A_idleAnimR;
	Animation A_walkAnimU;
	Animation A_walkAnimD;
	Animation A_walkAnimL;
	Animation A_walkAnimR;
};

#endif // __INTROCUTSCENE_H__