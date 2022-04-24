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
#include "Dialog.h"
#include "Frontground.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

Fonts::Fonts(bool enabled) : Module(enabled)
{
	name.Create("fonts");
	
}

Fonts::~Fonts()
{}

bool Fonts::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		char lookupTableChars[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ çüéâäàaçêëèïîìäaéÆæôöòûù" };
		textFont1 = app->fonts->Load("Assets/textures/Tipografia_Titulos.png", lookupTableChars, 8);
		textFont2 = app->fonts->Load("Assets/textures/my_font.png", lookupTableChars, 8);
		textFont3 = app->fonts->Load("Assets/textures/my_font_red.png", lookupTableChars, 8);
		textFont4 = app->fonts->Load("Assets/textures/my_font_green.png", lookupTableChars, 8);
	}

	return true;
}

bool Fonts::CleanUp()
{
	UnLoad(textFont1);
	UnLoad(textFont2);
	UnLoad(textFont3);
	UnLoad(textFont4);

	return true;
}

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
		else if (text[i] == ' ') {
			app->render->DrawTexture(font->texture, x, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 25;
		}
		else if (text[i] == 'M' || text[i] == 'W' || text[i] == 'm' || text[i] == 'w') {
			app->render->DrawTexture(font->texture, x + 4, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 10;
		}
		else {
			app->render->DrawTexture(font->texture, x, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 8 - 15;
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

void Fonts::BlitCombatText(int x, int y, int font_id, const char* text, int zoom, int r, int g, int b, int max, int down) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].texture == nullptr)
	{
		return;
	}
	int x0 = x;
	int y0 = y;

	x += 5;
	y -= 5;

	const Font* font = &fonts[font_id];
	SDL_Rect spriteRect;

	uint len = strlen(text);

	spriteRect.w = 32;
	spriteRect.h = 40;

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
		if (text[i] == '!' || text[i] == '¡' || text[i] == ',' || text[i] == '.' || text[i] == ':' || text[i] == ';' || text[i] == '|')
		{
			app->render->DrawTexture(font->texture, x - 10, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 24;
		}
		else if (text[i] == '"' || text[i] == '*' || text[i] == '1' || text[i] == 'j' || text[i] == '(' || text[i] == ')' || text[i] == 'I'
			|| text[i] == '{' || text[i] == '}' || text[i] == ' ')
		{
			app->render->DrawTexture(font->texture, x - 6, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 16;
		}
		else if (text[i] == '#' || text[i] == '@')
		{
			app->render->DrawTexture(font->texture, x + 4, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w + 4;
		}
		else if (text[i] == '%')
		{
			app->render->DrawTexture(font->texture, x + 1, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 2;
		}
		else if (text[i] == '¿' || text[i] == '-' || text[i] == '/' || text[i] == '0' || text[i] == '2' || text[i] == '3' || text[i] == '5'
			|| text[i] == '6' || text[i] == '7' || text[i] == '8' || text[i] == '9' || text[i] == '<' || text[i] == '=' || text[i] == '>'
			|| text[i] == '?' || text[i] == 'A' || text[i] == 'B' || text[i] == 'C' || text[i] == 'D' || text[i] == 'E' || text[i] == 'F'
			|| text[i] == 'G' || text[i] == 'H' || text[i] == 'J' || text[i] == 'K' || text[i] == 'L' || text[i] == 'N' || text[i] == 'O'
			|| text[i] == 'P' || text[i] == 'R' || text[i] == 'S' || text[i] == 'U' || text[i] == 'V' || text[i] == 'X' || text[i] == 'Y'
			|| text[i] == 'Z' || text[i] == '-' || text[i] == 'c' || text[i] == 'f' || text[i] == 'r' || text[i] == 's' || text[i] == 'z')
		{
			app->render->DrawTexture(font->texture, x - 4, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 12;
		}
		else if (text[i] == '+' || text[i] == '4' || text[i] == 'M' || text[i] == 'Q' || text[i] == 'T' || text[i] == 'W' || text[i] == '^'
			|| text[i] == 't' || text[i] == 'u' || text[i] == 'v' || text[i] == 'x' || text[i] == 'y')
		{
			app->render->DrawTexture(font->texture, x - 2, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 6;
		}
		else if (text[i] == '[' || text[i] == ']' || text[i] == 'i' || text[i] == 'l')
		{
			app->render->DrawTexture(font->texture, x - 8, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 20;
		}
		else if (text[i] == 'w')
		{
			app->render->DrawTexture(font->texture, x + 2, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w;
		}
		else
		{
			app->render->DrawTexture(font->texture, x, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 4;
		}
		
	}
}

void Fonts::BlitTextLetter(int x, int y, int font_id, const char* text, int zoom, int r, int g, int b, int max, int down, uint len, int linea)
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


	if (linea == 1)
	{
		app->dialog->limitLenght = strlen(text);
	}
	else if (linea == 2)
	{
		app->dialog->limitLenght2 = strlen(text);
	}

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
			x += spriteRect.w - 10;
		}
		else {
			app->render->DrawTexture(font->texture, x, y, &spriteRect, 1.0f, 0, INT_MAX, INT_MAX);
			x += spriteRect.w - 8 - 15;
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

