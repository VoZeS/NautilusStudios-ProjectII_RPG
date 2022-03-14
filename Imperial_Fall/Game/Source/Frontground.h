#ifndef __FRONTGROUND_H__
#define __FRONTGROUND_H__

#include "Module.h"

class Frontground : public Module
{
public:
	Frontground();

	virtual ~Frontground();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void SetA_Black()
	{
		a = 255;
	}

	void SetA_Null()
	{
		a = 0;
	}

	bool FadeToBlack(int dest_level); // if -1 --> no level change

	bool FadeFromBlack(int dest_level); // if -1 --> no level change

	void SetPressE_Hide(bool hide)
	{
		press_e_hide = hide;
	}

private:
	SDL_Rect r;
	Uint8 a;

	bool go_black = false;
	bool return_black = false;
	int fade_speed = 2;

	int destination_level = -1;

	SDL_Texture* press_e;
	bool press_e_hide = true;
};

#endif
