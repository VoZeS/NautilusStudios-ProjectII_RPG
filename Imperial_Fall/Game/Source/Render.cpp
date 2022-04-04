#include "App.h"
#include "Window.h"
#include "Render.h"
#include "Scene.h"
#include "Entities.h"

#include "Defs.h"
#include "Log.h"

#define VSYNC true

Render::Render() : Module()
{
	name.Create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
Render::~Render()
{}

// Called before render is available
bool Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;

	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if(config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(app->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = app->win->screenSurface->w;
		camera.h = app->win->screenSurface->h;
		camera.x = 0;
		camera.y = 0;
	}

	return ret;
}

// Called before the first frame
bool Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);
	return true;
}

// Called each loop iteration
bool Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool Render::Update(float dt)
{
	if (app->entities->entities.start)
	{
		Entity* entity = app->entities->GetPlayer();
		camera.x = -METERS_TO_PIXELS(entity->GetPlayerPosition().x) + (1280 / 2);
		camera.y = -METERS_TO_PIXELS(entity->GetPlayerPosition().y) + (720 / 2);
	}

	if (app->scene->current_level == 1)
	{
		if (camera.x > 0)
		{
			camera.x = 0;
		}
		else if (camera.x < -1900)
		{
			camera.x = -1900;
		}

		if (camera.y > 0)
		{
			camera.y = 0;
		}
		else if (camera.y < -500)
		{
			camera.y = -500;
		}
	}
	else if (app->scene->current_level == 2)
	{
		if (camera.x > 0)
		{
			camera.x = 0;
		}
		else if (camera.x < -1450)
		{
			camera.x = -1450;
		}

		if (camera.y > 0)
		{
			camera.y = 0;
		}
		else if (camera.y < -2400)
		{
			camera.y = -2400;
		}

	}
	else if (app->scene->current_level == 3)
	{
		if (camera.x > 0)
		{
			camera.x = 0;
		}
		else if (camera.x < -1600)
		{
			camera.x = -1600;
		}

		if (camera.y > 0)
		{
			camera.y = 0;
		}
		else if (camera.y < -2000)
		{
			camera.y = -2000;
		}
	}
	else if (app->scene->current_level == 4)
	{
		if (camera.x > -120)
		{
			camera.x = -120;
		}
		else if (camera.x < -1700)
		{
			camera.x = -1700;
		}

		if (camera.y > 0)
		{
			camera.y = 0;
		}
		else if (camera.y < -2400)
		{
			camera.y = -2400;
		}
	}
	else if (app->scene->current_level == 5)
	{
		if (camera.x > -0)
		{
			camera.x = -0;
		}
		else if (camera.x < -2300)
		{
			camera.x = -2300;
		}

		if (camera.y > 0)
		{
			camera.y = 0;
		}
		else if (camera.y < -1320)
		{
			camera.y = -1320;
		}
	}
	else if (app->scene->current_level == 6)
	{
	if (camera.x > -0)
	{
		camera.x = -0;
	}
	else if (camera.x < -700)
	{
		camera.x = -700;
	}

	if (camera.y > 0)
	{
		camera.y = 0;
	}
	else if (camera.y < -970)
	{
		camera.y = -970;
	}
	}
	else if (app->scene->current_level == 7)
	{
	if (camera.x > -0)
	{
		camera.x = -0;
	}
	else if (camera.x < -200)
	{
		camera.x = -200;
	}

	if (camera.y > 0)
	{
		camera.y = 0;
	}
	else if (camera.y < -600)
	{
		camera.y = -600;
	}
	}

	SDL_RenderSetLogicalSize(renderer, 1280, 720);

	return true;
}

bool Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

// Load Game State
bool Render::LoadState(pugi::xml_node& data)
{
	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();

	return true;
}

// Save Game State
bool Render::SaveState(pugi::xml_node& data)
{
	data.child("camera").attribute("x").set_value(camera.x);
	data.child("camera").attribute("y").set_value(camera.y);

	return true;
}

void Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

iPoint Render::ScreenToWorld(int x, int y) const
{
	iPoint ret;
	int scale = app->win->GetScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}

// Blit to screen
bool Render::DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivotX, int pivotY) const
{
	bool ret = true;
	float scale = app->win->GetScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * scale;
	rect.y = (int)(camera.y * speed) + y * scale;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if(pivotX != INT_MAX && pivotY != INT_MAX)
	{
		pivot.x = pivotX;
		pivot.y = pivotY;
		p = &pivot;
	}

	if(SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		//LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;
	float scale = app->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if(use_camera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w *= scale;
		rec.h *= scale;
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	float scale = app->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if(use_camera)
		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else
		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	float scale = app->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for(uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void Render::MoveCamera(int movement)
{
	camera.x -= movement;
}