#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

Fonts::Fonts() : Module()
{
	name.Create("fonts");
	
}

Fonts::~Fonts()
{}

int Fonts::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		//LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = app->tex->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		//LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].texture == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		//LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	Font& font = fonts[id];

	font.texture = tex;
	font.rows = rows;

	strcpy_s(fonts[id].table, MAX_FONT_CHARS, characters);
	font.totalLength = strlen(characters);
	font.columns = fonts[id].totalLength / rows;

	uint tex_w, tex_h;
	app->tex->GetSize(tex, tex_w, tex_h);
	font.char_w = tex_w / font.columns;
	font.char_h = tex_h / font.rows;

	//LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void Fonts::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].texture != nullptr)
	{
		app->tex->UnLoad(fonts[font_id].texture);
		fonts[font_id].texture = nullptr;
		//LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

void Fonts::BlitText(int x, int y, int font_id, const char* text, int zoom, int r, int g, int b, int max, int down) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].texture == nullptr)
	{
		//LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}
	int x0 = x;
	int y0 = y;

	const Font* font = &fonts[font_id];
	SDL_Rect spriteRect;

	uint len = strlen(text);

	spriteRect.w = 42;
	spriteRect.h = 42;

	for (uint i = 0; i < len; ++i)
	{
		uint charIndex = 0;

		for (uint j = 0; j < font->totalLength; ++j)
		{
			if (font->table[j] == text[i])
			{
				charIndex = j;
				break;
			}
		}

		spriteRect.x = spriteRect.w * (charIndex % font->columns);
		spriteRect.y = spriteRect.h * (charIndex / font->columns);
		if (text[i] == '|') {
			x = x0;
			y += spriteRect.h * zoom + zoom * down;
		}
		else if (text[i] == 'M' || text[i] == 'W' || text[i] == 'm' || text[i] == 'w') {
			app->render->DrawTexture(font->texture, x + 4, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w;
		}
		else {
			app->render->DrawTexture(font->texture, x, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 8;
		}



		/*
		else if (text[i] == 'I') {


			app->render->DrawTexture(font->texture, x - 2 * zoom + zoom, y + zoom, &spriteRect);
			x += spriteRect.w * zoom - zoom - 5 * zoom;
		}
		else if (text[i] == 'T') {
			app->render->DrawTexture(font->texture, x + zoom, y + zoom, &spriteRect, 0.0f, false, zoom, r, g, b);
			x += spriteRect.w * zoom - 2 * zoom;
		}
		else if (text[i] == '0' || text[i] == '1' || text[i] == '2' || text[i] == '3' || text[i] == '4' || text[i] == '5' || text[i] == '6' || text[i] == '7' || text[i] == '8' || text[i] == '9') {
			app->render->DrawTexture(font->texture, x + zoom, y + zoom, &spriteRect, 0.0f, false, zoom, r, g, b);
			x += spriteRect.w * zoom - 2 * zoom;
		}
		else {
			app->render->DrawTexture(font->texture, x + zoom, y + zoom, &spriteRect, 0.0f, false, zoom, r, g, b);
			x += spriteRect.w * zoom - zoom;
		}
		*/
		/*
		if (x > max) {
			x = x0;
			y += spriteRect.h * zoom + zoom * down;
		}
		*/
	}
}

