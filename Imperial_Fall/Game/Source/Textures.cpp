#include "App.h"
#include "Render.h"
#include "Textures.h"

#include "Defs.h"
#include "Log.h"

#include "SDL_image/include/SDL_image.h"
//#pragma comment(lib, "../Game/Source/External/SDL_image/libx86/SDL2_image.lib")

Textures::Textures() : Module()
{
	name.Create("textures");
}

// Destructor
Textures::~Textures()
{}

// Called before render is available
bool Textures::Awake(pugi::xml_node& config)
{
	LOG("Init Image library");
	bool ret = true;

	// Load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool Textures::Start()
{
	LOG("start textures");
	bool ret = true;

	assassin_texture = Load("Assets/textures/Asesino.png");
	tank_texture = Load("Assets/textures/Tanque.png");
	healer_texture = Load("Assets/textures/Healer.png");
	wizard_texture = Load("Assets/textures/Mago.png");
	renato_bueno = Load("Assets/textures/renato_bueno.png");
	curandero = Load("Assets/textures/curandero.png");
	herrero = Load("Assets/textures/herrero.png");
	granjero = Load("Assets/textures/granjero.png");
	start_menu = Load("Assets/textures/Start_screen.png");
	target = Load("Assets/textures/target.png");
	skull = Load("Assets/textures/skull.png");
	goblin = Load("Assets/textures/goblin.png");
	skeleton = Load("Assets/textures/skeleton.png");
	mushroom = Load("Assets/textures/mushroom.png");
	white_templar = Load("Assets/textures/white_templar.png");
	red_templar = Load("Assets/textures/red_templar.png");
	heroes_icons = Load("Assets/textures/heroes_icons.png");
	enemies_icons = Load("Assets/textures/enemies_icons.png");
	turn_icon = Load("Assets/textures/turn_icon.png");
	dead_icon = Load("Assets/textures/dead_icon.png");
	whitemark_64x64 = Load("Assets/textures/64x64_whitemark.png");
	whitemark_400x50 = Load("Assets/textures/400x50_whitemark.png");
	whitemark_110x110 = Load("Assets/textures/110x110_whitemark.png");
	whitemark_128x128 = Load("Assets/textures/128x128_whitemark.png");
	particles_texture = Load("Assets/textures/particlesBig.png");


	hab_tex = Load("Assets/textures/HabilityMack.png");
	slime_textureR = Load("Assets/textures/SlimeR.png");
	slime_textureL = Load("Assets/textures/SlimeL.png");
	floper_texture = Load("Assets/textures/Floper.png");
	tileX = Load("Assets/textures/x.png");
	coin_texture = Load("Assets/textures/Coin.png");
	heart_texture = Load("Assets/textures/Heart.png");

	return ret;
}

// Called before quitting
bool Textures::CleanUp()
{
	LOG("Freeing textures and Image library");
	ListItem<SDL_Texture*>* item;

	for(item = textures.start; item != NULL; item = item->next)
	{
		SDL_DestroyTexture(item->data);
	}

	textures.Clear();
	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const Textures::Load(const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if(surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

// Unload texture
bool Textures::UnLoad(SDL_Texture* texture)
{
	ListItem<SDL_Texture*>* item;

	for(item = textures.start; item != NULL; item = item->next)
	{
		if(texture == item->data)
		{
			SDL_DestroyTexture(item->data);
			textures.Del(item);
			return true;
		}
	}

	return false;
}

// Translate a surface into a texture
SDL_Texture* const Textures::LoadSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(app->render->renderer, surface);

	if(texture == NULL)
	{
		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		textures.Add(texture);
	}

	return texture;
}

// Retrieve size of a texture
void Textures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*) &width, (int*) &height);
}
