#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Physics.h"
#include "Player.h"
#include "Hearts.h"
#include "Menu.h"

#include "Defs.h"
#include "Log.h"

Player::Player() : Entity()
{

}

// Destructor
Player::~Player()
{}

void Player::InitCustomEntity()
{
	currentAnimation = &idleAnimR;
	look_dir = 1;

	walk_sound = app->audio->LoadFx("Assets/audio/fx/step_sound.wav");

	// body
	b2BodyDef p_body;
	p_body.type = b2_dynamicBody;
	p_body.fixedRotation = true;
	p_body.position.Set(position.x, position.y);

	body = app->physics->world->CreateBody(&p_body);
	body->SetBullet(true);
	body->SetFixedRotation(true);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h));

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.friction = 0.0f;
	b2Fixture* bodyFixture = body->CreateFixture(&fixture);
	bodyFixture->SetSensor(false);
	bodyFixture->SetUserData((void*)1); // player collision
}

// Called each loop iteration
bool Player::PreUpdate()
{
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;

	return true;
}

void Player::HandleInput(float dt)
{
	float fixedSpeed = speed * dt;

	//if (!app->menu->GetGameState() && !app->scene->GetStartScreenState())
	{
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE || app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE)
		{
			// move up
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				body->SetLinearVelocity({ body->GetLinearVelocity().x, -fixedSpeed });
				look_dir = 0;

				if (currentAnimation != &walkAnimU)
				{
					walkAnimU.Reset();
					currentAnimation = &walkAnimU;
				}
			}
			else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
			{
				body->SetLinearVelocity({ body->GetLinearVelocity().x, 0 });

				if (currentAnimation != &idleAnimU)
				{
					idleAnimU.Reset();
					currentAnimation = &idleAnimU;
				}
			}

			// move down
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				body->SetLinearVelocity({ body->GetLinearVelocity().x, fixedSpeed });
				look_dir = 1;

				if (currentAnimation != &walkAnimD)
				{
					walkAnimD.Reset();
					currentAnimation = &walkAnimD;
				}
			}
			else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
			{
				body->SetLinearVelocity({ body->GetLinearVelocity().x, 0 });

				if (currentAnimation != &idleAnimD)
				{
					idleAnimD.Reset();
					currentAnimation = &idleAnimD;
				}
			}
		}
		else
		{
			body->SetLinearVelocity({ body->GetLinearVelocity().x, 0 });
		}
		
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE || app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		{
			// move left
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				body->SetLinearVelocity({ -fixedSpeed, body->GetLinearVelocity().y });
				look_dir = 2;

				if (currentAnimation != &walkAnimL)
				{
					walkAnimL.Reset();
					currentAnimation = &walkAnimL;
				}
			}
			else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{
				body->SetLinearVelocity({ 0, body->GetLinearVelocity().y });

				if (currentAnimation != &idleAnimL)
				{
					idleAnimL.Reset();
					currentAnimation = &idleAnimL;
				}
			}

			//Move Right
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				body->SetLinearVelocity({ fixedSpeed, body->GetLinearVelocity().y });
				look_dir = 3;

				if (currentAnimation != &walkAnimR)
				{
					walkAnimR.Reset();
					currentAnimation = &walkAnimR;
				}
			}
			else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				body->SetLinearVelocity({ 0, body->GetLinearVelocity().y });

				if (currentAnimation != &idleAnimR)
				{
					idleAnimR.Reset();
					currentAnimation = &idleAnimR;
				}
			}
		}
		else
		{
			body->SetLinearVelocity({ 0, body->GetLinearVelocity().y });
		}

		if (body->GetLinearVelocity().x != 0 && body->GetLinearVelocity().y != 0)
		{
			body->SetLinearVelocity({ 0, 0 });
		}
		

		if (body->GetLinearVelocity().x != 0 || body->GetLinearVelocity().y != 0)
		{
			walk_cd -= dt;
			if (walk_cd <= 0)
			{
				app->audio->PlayFx(walk_sound);
				walk_cd = 320;
			}
		}

		
		if (body->GetLinearVelocity().x == 0 && body->GetLinearVelocity().y == 0)
		{
			switch (look_dir)
			{
			case 0:
				if (currentAnimation != &idleAnimU)
				{
					idleAnimU.Reset();
					currentAnimation = &idleAnimU;
				}
				break;
			case 1:
				if (currentAnimation != &idleAnimD)
				{
					idleAnimD.Reset();
					currentAnimation = &idleAnimD;
				}
				break;
			case 2:
				if (currentAnimation != &idleAnimL)
				{
					idleAnimL.Reset();
					currentAnimation = &idleAnimL;
				}
				break;
			case 3:
				if (currentAnimation != &idleAnimR)
				{
					idleAnimR.Reset();
					currentAnimation = &idleAnimR;
				}
				break;
			}
		}

		currentAnimation->Update();
	}
}

// Called each loop iteration
bool Player::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool Player::Draw()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	app->render->DrawRectangle({ METERS_TO_PIXELS(position.x), METERS_TO_PIXELS(position.y), 16, 32 }, 255, 0, 0);
	 
	/*if (!app->scene->GetStartScreenState())
	{
		if (lookLeft)
		{
			app->render->DrawTexture(app->tex->player_textureL, METERS_TO_PIXELS(position.x - 55.5f), METERS_TO_PIXELS(position.y - 70.0f), &rect);
		}
		else
		{
			app->render->DrawTexture(app->tex->player_textureR, METERS_TO_PIXELS(position.x - 55.5f), METERS_TO_PIXELS(position.y - 70.0f), &rect);
		}
	}*/
	
	return true;
}

bool Player::Load(pugi::xml_node& data)
{
	position.x = data.child("player").child("position").attribute("x").as_int();
	position.y = data.child("player").child("position").attribute("y").as_int();

	body->SetTransform({ position.x + PIXELS_TO_METERS(w), position.y }, body->GetAngle());
	body->ApplyForceToCenter({ 0, 1 }, true);

	currentAnimation = &idleAnimR;
	if (app->menu->dead)
	{
		app->menu->dead = false;
	}

	return true;
}

bool Player::Save(pugi::xml_node& data)
{
	data.child("player").child("position").attribute("x").set_value(position.x);
	data.child("player").child("position").attribute("y").set_value(position.y);

	return true;
}

fPoint Player::GetPlayerPosition()
{
	return position;
}

void Player::SetPlayerPosition(int new_x, int new_y)
{
	position.x = new_x;
	position.y = new_y;

	body->SetTransform({ position.x, position.y }, body->GetAngle());
	body->ApplyForceToCenter({ 0, 1 }, true);
}

void Player::ImpulsePlayer()
{
	body->SetLinearVelocity({ body->GetLinearVelocity().x , 0 });
	body->ApplyForceToCenter({ 0, -25.0f * app->GetDT() }, true);
}