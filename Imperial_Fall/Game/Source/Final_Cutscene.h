#ifndef __FINALCUTSCENE_H__
#define __FINALCUTSCENE_H__

#include "Module.h"
#include "Physics.h"
#include "Animation.h"


struct _Mix_Music;
struct SDL_Texture;
enum class ENEMIES;

class Final_Cutscene : public Module
{
public:

	Final_Cutscene(bool enabled);

	// Destructor
	virtual ~Final_Cutscene();

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

	int counter = 0;

private:
	// cutscene
	uint letlengh = 0;
	uint letlengh2 = 0;
	int letter_cd = 0;

	bool inDialog = false;

	SDL_Rect Wizard;
	SDL_Rect Tank;
	SDL_Rect Healer;
	SDL_Rect Assassin;
	SDL_Rect Theseion;
	SDL_Rect Renato;

	SDL_Texture* assassin_texture = NULL;
	SDL_Texture* tank_texture = NULL;
	SDL_Texture* healer_texture = NULL;
	SDL_Texture* wizard_texture = NULL;
	SDL_Texture* theseion_texture = NULL;
	SDL_Texture* renato_texture = NULL;

	SDL_Rect whiteMark_Name;

	SDL_Texture* whitemark_300x80 = NULL;
	SDL_Texture* whitemark_500x70 = NULL;
	SDL_Texture* whitemark_1200x140;
	SDL_Texture* whitemark_1240x680;

	Animation* W_currentAnimation = NULL;
	Animation* T_currentAnimation = NULL;
	Animation* H_currentAnimation = NULL;
	Animation* A_currentAnimation = NULL;
	Animation* TH_currentAnimation = NULL;
	Animation* R_currentAnimation = NULL;

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

	// THESEION main Animations
	Animation TH_idleAnimU;
	Animation TH_idleAnimD;
	Animation TH_idleAnimL;
	Animation TH_idleAnimR;
	Animation TH_walkAnimU;
	Animation TH_walkAnimD;
	Animation TH_walkAnimL;
	Animation TH_walkAnimR;

	// RENATO main Animations
	Animation R_idleAnimU;
	Animation R_idleAnimD;
	Animation R_idleAnimL;
	Animation R_idleAnimR;
	Animation R_walkAnimU;
	Animation R_walkAnimD;
	Animation R_walkAnimL;
	Animation R_walkAnimR;
};

#endif // __FINALCUTSCENE_H__