#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"

#include "Point.h"

#include "SDL/include/SDL.h"

#include <vector>

using namespace std;

struct renderObject
{
	SDL_Texture* texture;

	SDL_Rect section = { 0,0,0,0 };

	SDL_Rect renderRect = { 0,0 };

	SDL_RendererFlip flip;

	double angle = 0.0f;

	int layer = 0;

	float Ordeninlayer = 1.0f;

	float speed = 1.0f;

};

class Render : public Module
{
public:

	Render(bool enabled);

	// Destructor
	virtual ~Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y) const;

	// Drawing
	bool DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool useCamera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;

	void SortingRenderObjectsWithPosition(vector<renderObject>& vectorofobjectstosort);

	bool IsinCamera(const renderObject* renderObj);

	void AddrenderObject(SDL_Texture* texture, iPoint pos, SDL_Rect section, int layer, float ordeninlayer = 1.0f, double angle = 0.0f, bool isFlipH = false, float scale = 1.0f, float speed = 1.0f);

	void Draw();

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	void MoveCamera(int movement);

public:

	SDL_Renderer* renderer;
	SDL_Rect camera;
	SDL_Rect viewport;
	SDL_Color background;

private:
	vector< vector<renderObject>> layers;

	int cont = 0;

};

#endif // __RENDER_H__