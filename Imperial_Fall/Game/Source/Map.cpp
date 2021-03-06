#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"
#include "Physics.h"
#include "Enemies.h"
#include "Fonts.h"
#include "Scene.h"
#include "Outside_Castle.h"
#include "Frontground.h"
#include "Forest.h"
#include "Dungeon.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Map::Map(bool enabled) : Module(enabled), mapLoaded(false)
{
    name.Create("map");
	collision_loaded = false;
}

// Destructor
Map::~Map()
{}

// L06: TODO 7: Ask for the value of a custom property
int Properties::GetProperty(const char* value, int defaultValue) const
{
	ListItem<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value)
			return item->data->value;
		item = item->next;
	}

	return defaultValue;
}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

bool Map::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		collision_loaded = false;
		coins_index = 0;
		books0_index = 0;
		books1_index = 0;
		books2_index = 0;
		books3_index = 0;

		S1_Coll = NULL;
		S2_Coll = NULL;
		S3_Coll = NULL;
		S4_Coll = NULL;
		S5_Coll = NULL;
		S6_Coll = NULL;

		S1_Sens = NULL;
		S2_Sens = NULL;
		S3_Sens = NULL;
		S4_Sens = NULL;
		S5_Sens = NULL;
		S6_Sens = NULL;

		S1_Box = NULL;
		S2_Box = NULL;
		S3_Box = NULL;
		S4_Box = NULL;

		doorCastle = NULL;
	}

	return true;
}

// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;
	
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	while (mapLayerItem != NULL) {
		
		for (int x = 0; x < mapLayerItem->data->width; x++)
		{
			for (int y = 0; y < mapLayerItem->data->height; y++)
			{
				// L04: DONE 9: Complete the draw function
				int gid = mapLayerItem->data->Get(x, y);
				
				if (gid > 0) {
					TileSet* tileset = GetTilesetFromTileId(gid);
					
					SDL_Rect r = tileset->GetTileRect(gid);
					iPoint pos = MapToWorld(x, y);

					if (mapLayerItem->data->properties.GetProperty("Draw") == 1)
					{
						if (mapLayerItem->data->properties.GetProperty("Layer") == 0)
						{
							if ((-app->render->camera.x > pos.x - 1400 && -app->render->camera.x < pos.x + 200) &&
								(-app->render->camera.y < pos.y + 200 && -app->render->camera.y > pos.y - 800))
							{
								app->render->DrawTexture(tileset->texture, pos.x, pos.y, &r);
							}
						}
						else
						{
							if ((-app->render->camera.x > pos.x - 1400 && -app->render->camera.x < pos.x + 200) &&
								(-app->render->camera.y < pos.y + 200 && -app->render->camera.y > pos.y - 800))
							{
								app->render->AddrenderObject(tileset->texture, pos, r, mapLayerItem->data->properties.GetProperty("Layer"));
							}
						}
					}
					
					else if (mapLayerItem->data->properties.GetProperty("Draw") == 2 && app->frontground->adventure_phase < 1)
					{
						if ((-app->render->camera.x > pos.x - 1400 && -app->render->camera.x < pos.x + 200) &&
							(-app->render->camera.y < pos.y + 200 && -app->render->camera.y > pos.y - 800))
						{
							app->render->DrawTexture(tileset->texture, pos.x, pos.y, &r);
						}
					}
					else if (mapLayerItem->data->properties.GetProperty("Draw") == 3 && app->frontground->adventure_phase < 3)
					{
						if ((-app->render->camera.x > pos.x - 1400 && -app->render->camera.x < pos.x + 200) &&
							(-app->render->camera.y < pos.y + 200 && -app->render->camera.y > pos.y - 800))
						{
							app->render->DrawTexture(tileset->texture, pos.x, pos.y, &r);
						}
					}
					else if (mapLayerItem->data->properties.GetProperty("Draw") == 4 && app->frontground->adventure_phase < 5)
					{
						if ((-app->render->camera.x > pos.x - 1400 && -app->render->camera.x < pos.x + 200) &&
							(-app->render->camera.y < pos.y + 200 && -app->render->camera.y > pos.y - 800))
						{
							app->render->DrawTexture(tileset->texture, pos.x, pos.y, &r);
						}
					}
					else if (mapLayerItem->data->properties.GetProperty("Draw") == 5 && app->forest->allBoxesDone)
					{
						if ((-app->render->camera.x > pos.x - 1400 && -app->render->camera.x < pos.x + 200) &&
							(-app->render->camera.y < pos.y + 200 && -app->render->camera.y > pos.y - 800))
						{
							app->render->DrawTexture(tileset->texture, pos.x, pos.y, &r);
						}
					}
					
					if (!collision_loaded)
					{
						int width = mapLayerItem->data->properties.GetProperty("Width");
						int height = mapLayerItem->data->properties.GetProperty("Height");

						if (mapLayerItem->data->properties.GetProperty("Collision") == 30 && app->dungeon->Enabled())
						{
							// dungeon ice sensor
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 30);
						}
						if (mapLayerItem->data->properties.GetProperty("Collision") == 99 && app->dungeon->Enabled())
						{
							// dungeon spike sensor
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 99);
						}

						if (mapLayerItem->data->properties.GetProperty("Collision") == 1)
						{
							// collision ground
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 100);
						}
						
						// -------------------------------------------------------------------------- BOXES SOUKOBAN
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 301 && !app->forest->allBoxesDone)
						{
							S1_Box = app->physics->CreateDynamicBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 302 && !app->forest->allBoxesDone)
						{
							S2_Box = app->physics->CreateDynamicBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 303 && !app->forest->allBoxesDone)
						{
							S3_Box = app->physics->CreateDynamicBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 304 && !app->forest->allBoxesDone)
						{
							S4_Box = app->physics->CreateDynamicBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2);

						}
						// -------------------------------------------------------------------------- DOOR CASTLE
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 40 && (!app->outside->lever1Active || !app->outside->lever2Active))
						{
							// collision door castle
							doorCastle = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 40);
						}
						// -------------------------------------------------------------------- RIVER COLLISIONS SOUKOBAN PUZZLE
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 101 && !app->forest->allBoxesDone)
						{
							S1_Coll = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 101);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 102 && !app->forest->allBoxesDone)
						{
							S2_Coll = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 102);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 103 && !app->forest->allBoxesDone)
						{
							S3_Coll = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 103);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 104 && !app->forest->allBoxesDone)
						{
							S4_Coll = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 104);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 105 && !app->forest->allBoxesDone)
						{
							S5_Coll = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 105);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 106 && !app->forest->allBoxesDone)
						{
							S6_Coll = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 106);

						}
						// --------------------------------------------------------------------- SENSOR SOUKOBAN PUZZLE
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 201 && !app->forest->allBoxesDone)
						{
							S1_Sens = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 201);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 202 && !app->forest->allBoxesDone)
						{
							S2_Sens = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 202);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 203 && !app->forest->allBoxesDone)
						{
							S3_Sens = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 203);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 204 && !app->forest->allBoxesDone)
						{
							S4_Sens = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 204);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 205 && !app->forest->allBoxesDone)
						{
							S5_Sens = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 205);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 206 && !app->forest->allBoxesDone)
						{
							S6_Sens = app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 206);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 231)
						{
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 231);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 232)
						{
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 232);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 233)
						{
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 233);

						}

						
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 92 && app->frontground->adventure_phase < 1)
						{
							// collision ground
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 100);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 93 && app->frontground->adventure_phase < 3)
						{
							// collision ground
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 100);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 94 && app->frontground->adventure_phase < 5)
						{
							// collision ground
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 100);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 5)
						{
							// Renato
							app->entities->CreateEntity(ENTITY_TYPE::RENATO, pos.x, pos.y);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 6)
						{
							// Curandero
							app->entities->CreateEntity(ENTITY_TYPE::CURANDERO, pos.x, pos.y);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 7)
						{
							// Herrero
							app->entities->CreateEntity(ENTITY_TYPE::HERRERO, pos.x, pos.y);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 8)
						{
							// Sabio
							app->entities->CreateEntity(ENTITY_TYPE::SABIO, pos.x, pos.y);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 15)
						{
							// Aldeano
							app->entities->CreateEntity(ENTITY_TYPE::ALDEANO, pos.x, pos.y);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 900)
						{
							// SIGNAL SOUKOBAN
							app->entities->CreateEntity(ENTITY_TYPE::SIGNAL, pos.x, pos.y);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 901)
						{
							if (app->frontground->adventure_phase > 0)
							{
								// Granjero
								app->entities->CreateEntity(ENTITY_TYPE::GRANJERO, pos.x, pos.y);
							}
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 9)
						{
							// White templar
							int index = mapLayerItem->data->properties.GetProperty("Index");
							if (GetEnemyStateXml(index) && mapLayerItem->data->properties.GetProperty("Phase") == app->frontground->adventure_phase)
							{
								int en1 = mapLayerItem->data->properties.GetProperty("Enemy1");
								int en2 = mapLayerItem->data->properties.GetProperty("Enemy2");
								int en3 = mapLayerItem->data->properties.GetProperty("Enemy3");
								int en4 = mapLayerItem->data->properties.GetProperty("Enemy4");
								std::string s = IntToString(mapLayerItem->data->properties.GetProperty("Reward"));
								app->entities->CreateEntity(ENTITY_TYPE::W_TEMPLAR, pos.x, pos.y, index, en1, en2, en3, en4, s.c_str());
							}
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 10)
						{
							// Mushroom
							int index = mapLayerItem->data->properties.GetProperty("Index");
							if (GetEnemyStateXml(index) && mapLayerItem->data->properties.GetProperty("Phase") == app->frontground->adventure_phase)
							{
								int en1 = mapLayerItem->data->properties.GetProperty("Enemy1");
								int en2 = mapLayerItem->data->properties.GetProperty("Enemy2");
								int en3 = mapLayerItem->data->properties.GetProperty("Enemy3");
								int en4 = mapLayerItem->data->properties.GetProperty("Enemy4");
								std::string s = IntToString(mapLayerItem->data->properties.GetProperty("Reward"));
								app->entities->CreateEntity(ENTITY_TYPE::MUSHROOM, pos.x, pos.y, index, en1, en2, en3, en4, s.c_str());
							}
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 11)
						{
							// Goblin
							int index = mapLayerItem->data->properties.GetProperty("Index");
							if (GetEnemyStateXml(index) && mapLayerItem->data->properties.GetProperty("Phase") == app->frontground->adventure_phase)
							{
								int en1 = mapLayerItem->data->properties.GetProperty("Enemy1");
								int en2 = mapLayerItem->data->properties.GetProperty("Enemy2");
								int en3 = mapLayerItem->data->properties.GetProperty("Enemy3");
								int en4 = mapLayerItem->data->properties.GetProperty("Enemy4");
								std::string s = IntToString(mapLayerItem->data->properties.GetProperty("Reward"));
								app->entities->CreateEntity(ENTITY_TYPE::GOBLIN, pos.x, pos.y, index, en1, en2, en3, en4, s.c_str());
							}
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 13)
						{
							// Skeleton
							int index = mapLayerItem->data->properties.GetProperty("Index");
							if (GetEnemyStateXml(index) && mapLayerItem->data->properties.GetProperty("Phase") == app->frontground->adventure_phase)
							{
								int en1 = mapLayerItem->data->properties.GetProperty("Enemy1");
								int en2 = mapLayerItem->data->properties.GetProperty("Enemy2");
								int en3 = mapLayerItem->data->properties.GetProperty("Enemy3");
								int en4 = mapLayerItem->data->properties.GetProperty("Enemy4");
								std::string s = IntToString(mapLayerItem->data->properties.GetProperty("Reward"));
								app->entities->CreateEntity(ENTITY_TYPE::SKELETON, pos.x, pos.y, index, en1, en2, en3, en4, s.c_str());
							}
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 14)
						{
							// Red Templar
							int index = mapLayerItem->data->properties.GetProperty("Index");
							if (GetEnemyStateXml(index) && mapLayerItem->data->properties.GetProperty("Phase") == app->frontground->adventure_phase)
							{
								int en1 = mapLayerItem->data->properties.GetProperty("Enemy1");
								int en2 = mapLayerItem->data->properties.GetProperty("Enemy2");
								int en3 = mapLayerItem->data->properties.GetProperty("Enemy3");
								int en4 = mapLayerItem->data->properties.GetProperty("Enemy4");
								std::string s = IntToString(mapLayerItem->data->properties.GetProperty("Reward"));
								app->entities->CreateEntity(ENTITY_TYPE::R_TEMPLAR, pos.x, pos.y, index, en1, en2, en3, en4, s.c_str());
							}
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 17)
						{
							// Armored Templar
							int index = mapLayerItem->data->properties.GetProperty("Index");
							if (GetEnemyStateXml(index) && mapLayerItem->data->properties.GetProperty("Phase") == app->frontground->adventure_phase)
							{
								int en1 = mapLayerItem->data->properties.GetProperty("Enemy1");
								int en2 = mapLayerItem->data->properties.GetProperty("Enemy2");
								int en3 = mapLayerItem->data->properties.GetProperty("Enemy3");
								int en4 = mapLayerItem->data->properties.GetProperty("Enemy4");
								std::string s = IntToString(mapLayerItem->data->properties.GetProperty("Reward"));
								app->entities->CreateEntity(ENTITY_TYPE::A_TEMPLAR, pos.x, pos.y, index, en1, en2, en3, en4, s.c_str());
							}
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 18)
						{
							// Theseion
							int index = mapLayerItem->data->properties.GetProperty("Index");
							if (GetEnemyStateXml(index) && mapLayerItem->data->properties.GetProperty("Phase") == app->frontground->adventure_phase)
							{
								int en1 = mapLayerItem->data->properties.GetProperty("Enemy1");
								int en2 = mapLayerItem->data->properties.GetProperty("Enemy2");
								int en3 = mapLayerItem->data->properties.GetProperty("Enemy3");
								int en4 = mapLayerItem->data->properties.GetProperty("Enemy4");
								std::string s = IntToString(mapLayerItem->data->properties.GetProperty("Reward"));
								app->entities->CreateEntity(ENTITY_TYPE::THESEION, pos.x, pos.y, index, en1, en2, en3, en4, s.c_str());
							}
						}
						// ------------------------ miscelanea
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 20)
						{
							// coins
							pugi::xml_document saveGame;
							pugi::xml_parse_result result = saveGame.load_file(MISCELANEA_FILENAME);

							std::string p1 = "coins_in_room";
							std::string s1;
							switch (app->frontground->current_level)
							{
							case 1: s1 = std::to_string(0); break;
							case 2: s1 = std::to_string(1); break;
							case 3: s1 = std::to_string(2); break;
							case 4: s1 = std::to_string(3); break;
							case 5: s1 = std::to_string(4); break;
							case 6: s1 = std::to_string(5); break;
							case 7: s1 = std::to_string(6); break;
							default: break;
							}
							std::string t1 = p1 + s1;
							const char* c1 = t1.c_str();

							std::string p2 = "picked";
							std::string s2 = std::to_string(coins_index);
							std::string t2 = p2 + s2;
							const char* c2 = t2.c_str();

							if (!saveGame.child("miscelanea").child("coins").child(c1).attribute(c2).as_bool())
							{
								app->physics->CreateMiscelanea(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 20, 0);
							}
							coins_index++;
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 22)
						{
							// assassin book
							pugi::xml_document saveGame;
							pugi::xml_parse_result result = saveGame.load_file(MISCELANEA_FILENAME);

							std::string p1 = "books_in_room";
							std::string s1;
							switch (app->frontground->current_level)
							{
							case 1: s1 = std::to_string(0); break;
							case 2: s1 = std::to_string(1); break;
							case 3: s1 = std::to_string(2); break;
							case 4: s1 = std::to_string(3); break;
							case 5: s1 = std::to_string(4); break;
							case 6: s1 = std::to_string(5); break;
							case 7: s1 = std::to_string(6); break;
							default: break;
							}
							std::string t1 = p1 + s1;
							const char* c1 = t1.c_str();

							std::string p2 = "picked";
							std::string s2 = std::to_string(mapLayerItem->data->properties.GetProperty("Index"));
							std::string t2 = p2 + s2;
							const char* c2 = t2.c_str();

							if (!saveGame.child("miscelanea").child("books0").child(c1).attribute(c2).as_bool())
							{
								app->physics->CreateMiscelanea(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 22, mapLayerItem->data->properties.GetProperty("Index"));
							}
							books0_index++;
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 26)
						{
							// healer book
							pugi::xml_document saveGame;
							pugi::xml_parse_result result = saveGame.load_file(MISCELANEA_FILENAME);

							std::string p1 = "books_in_room";
							std::string s1;
							switch (app->frontground->current_level)
							{
							case 1: s1 = std::to_string(0); break;
							case 2: s1 = std::to_string(1); break;
							case 3: s1 = std::to_string(2); break;
							case 4: s1 = std::to_string(3); break;
							case 5: s1 = std::to_string(4); break;
							case 6: s1 = std::to_string(5); break;
							case 7: s1 = std::to_string(6); break;
							default: break;
							}
							std::string t1 = p1 + s1;
							const char* c1 = t1.c_str();

							std::string p2 = "picked";
							std::string s2 = std::to_string(mapLayerItem->data->properties.GetProperty("Index"));
							std::string t2 = p2 + s2;
							const char* c2 = t2.c_str();

							if (!saveGame.child("miscelanea").child("books1").child(c1).attribute(c2).as_bool())
							{
								app->physics->CreateMiscelanea(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 26, mapLayerItem->data->properties.GetProperty("Index"));
							}
							books1_index++;
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 27)
						{
							// tank book
							pugi::xml_document saveGame;
							pugi::xml_parse_result result = saveGame.load_file(MISCELANEA_FILENAME);

							std::string p1 = "books_in_room";
							std::string s1;
							switch (app->frontground->current_level)
							{
							case 1: s1 = std::to_string(0); break;
							case 2: s1 = std::to_string(1); break;
							case 3: s1 = std::to_string(2); break;
							case 4: s1 = std::to_string(3); break;
							case 5: s1 = std::to_string(4); break;
							case 6: s1 = std::to_string(5); break;
							case 7: s1 = std::to_string(6); break;
							default: break;
							}
							std::string t1 = p1 + s1;
							const char* c1 = t1.c_str();

							std::string p2 = "picked";
							std::string s2 = std::to_string(mapLayerItem->data->properties.GetProperty("Index"));
							std::string t2 = p2 + s2;
							const char* c2 = t2.c_str();

							if (!saveGame.child("miscelanea").child("books2").child(c1).attribute(c2).as_bool())
							{
								app->physics->CreateMiscelanea(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 27, mapLayerItem->data->properties.GetProperty("Index"));
							}
							books2_index++;
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 28)
						{
							// wizard book
							pugi::xml_document saveGame;
							pugi::xml_parse_result result = saveGame.load_file(MISCELANEA_FILENAME);

							std::string p1 = "books_in_room";
							std::string s1;
							switch (app->frontground->current_level)
							{
							case 1: s1 = std::to_string(0); break;
							case 2: s1 = std::to_string(1); break;
							case 3: s1 = std::to_string(2); break;
							case 4: s1 = std::to_string(3); break;
							case 5: s1 = std::to_string(4); break;
							case 6: s1 = std::to_string(5); break;
							case 7: s1 = std::to_string(6); break;
							default: break;
							}
							std::string t1 = p1 + s1;
							const char* c1 = t1.c_str();

							std::string p2 = "picked";
							std::string s2 = std::to_string(mapLayerItem->data->properties.GetProperty("Index"));
							std::string t2 = p2 + s2;
							const char* c2 = t2.c_str();

							if (!saveGame.child("miscelanea").child("books3").child(c1).attribute(c2).as_bool())
							{
								app->physics->CreateMiscelanea(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 28, mapLayerItem->data->properties.GetProperty("Index"));
							}
							books3_index++;
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 60)
						{
							app->physics->CreateMiscelanea(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 60, 0);

						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 70)
						{
							app->physics->CreateMiscelanea(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 70, 0);

						}
						// --------------------------------------------------------------------------- PASS LEVELS
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 12)
						{
							// town_1 --> town_2
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 12);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 21)
						{
							// town_2 --> town_1
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 21);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 23)
						{
							// town_2 --> forest
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 23);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 32)
						{
							// forest --> town_2
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 32);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 24)
						{
							// town_2 --> battlefield
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 24);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 42)
						{
							// battlefield --> town_2
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 42);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 25)
						{
							// town_2 --> dungeon
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 25);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 52)
						{
							// dungeon --> town_2
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 52);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 16)
						{
							// town_1 --> outside_castle
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 16);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 61)
						{
							// outside_castle-> town_1
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 61);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 67)
						{
							// outside_castle-> inside_castle
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 67);
						}
						else if (mapLayerItem->data->properties.GetProperty("Collision") == 76)
						{
							// inside_castle-> outside_castle
							app->physics->CreateMapBox(pos.x + ((r.w * width) / 2), pos.y + ((r.h * height) / 2), (r.w * width) / 2, (r.h * height) / 2, 76);
						}
					}
				}
			}
		}

		mapLayerItem = mapLayerItem->next;
	}

	collision_loaded = true;
}

// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * mapData.tileWidth;
		ret.y = y * mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{
	// L05: TODO 1: Add isometric map to world coordinates
		ret.x = (x - y) * (mapData.tileWidth * 0.5f);
		ret.y = (x + y) * (mapData.tileHeight * 0.5f);
	}
	
	return ret;
}


iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// L05: TODO 2: Add orthographic world to map coordinates
	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / mapData.tileWidth;
		ret.y = y / mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{
		// L05: TODO 3: Add the case for isometric maps to WorldToMap
		ret.x = (x - y) / (mapData.tileWidth * 0.5f);
		ret.y = (x + y) / (mapData.tileHeight * 0.5f);
	}

	return ret;
}

TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = mapData.tilesets.start;
	TileSet* set = item->data;
	
	for (set; set; item = item->next,  set = item->data)
	{
		if (id >= set->firstgid && id < set->firstgid + set->tilecount)
		{
			return set;
		}
	}

	return set;
}

std::string Map::IntToString(int n)
{
	std::string s;
	std::string r;

	if (n < 10)
	{
		s = std::to_string(n);
		r = "00" + s;
	}
	else if (n < 100)
	{
		s = std::to_string(n);
		r = "0" + s;
	}
	else
	{
		r = std::to_string(n);
	}

	return r;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// L04: DONE 7: Get relative Tile rectangle
	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % columns));
	rect.y = margin + ((rect.h + spacing) * (relativeId / columns));
	
	return rect;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");
	
    // L03: DONE 2: Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.Clear();

	// L04: DONE 2: clean up all layer data
	// Remove all layers
	ListItem<MapLayer*>* item2;
	item2 = mapData.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	mapData.layers.Clear();

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_document mapFile; 
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

	// Load general info
    if(ret == true)
    {
        // L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap(mapFile);
	}

    // L03: DONE 4: Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
	if (ret == true)
	{
		ret = LoadTileSets(mapFile.child("map"));
	}

	// L04: DONE 4: Iterate all layers and load each of them
	// Load layer info
	if (ret == true)
	{
		ret = LoadAllLayers(mapFile.child("map"));
	}
    
    if(ret == true)
    {
        // L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
		 
		/*LOG("Successfully parsed map XML file: %s", filename);
		LOG("width: %d", mapData.width);
		LOG("height: %d", mapData.height);
		LOG("tile width: %d", mapData.tileWidth);
		LOG("tile height: %d", mapData.tileHeight);
		if (mapData.type == MAPTYPE_ORTHOGONAL)
		{
			LOG("orientation: orthogonal");
		}
		else if (mapData.type == MAPTYPE_ISOMETRIC)
		{
			LOG("orientation: isometric");
		}*/

		ListItem<TileSet*>* tileset;
		tileset = mapData.tilesets.start;
		int tilesetCtr = 0;
		while (tileset != NULL)
		{
			/*LOG("Tileset %d", tilesetCtr + 1);
			LOG("name: %s", tileset->data->name.GetString());
			LOG("first gid: %d", tileset->data->firstgid);
			LOG("margin: %d", tileset->data->margin);
			LOG("spacing: %d", tileset->data->spacing);
			LOG("tile width: %d", tileset->data->tileWidth);
			LOG("tile height: %d", tileset->data->tileHeight);
			LOG("width: %d", tileset->data->texWidth);
			LOG("height: %d", tileset->data->texHeight);*/

			tileset = tileset->next;
			tilesetCtr++;
		}

		// L04: TODO 4: LOG the info for each loaded layer
		ListItem<MapLayer*>* layer;
		layer = mapData.layers.start;
		int layerCtr = 0;

		while (layer != NULL)
		{
			/*LOG("Layer %d", layerCtr + 1);
			LOG("name: %s", layer->data->name.GetString());
			LOG("width: %d", layer->data->width);
			LOG("height: %d", layer->data->height);*/
			
			layerCtr++;
			layer = layer->next;
		}
    }

    mapLoaded = ret;

    return ret;
}

bool Map::CleanMaps()
{
	mapData.tilesets.Clear();
	mapData.layers.Clear();

	return true;
}

// L03: TODO: Load map general properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// L03: DONE 3: Load map general properties
		mapData.height = map.attribute("height").as_int();
		mapData.width = map.attribute("width").as_int();
		mapData.tileHeight = map.attribute("tileheight").as_int();
		mapData.tileWidth = map.attribute("tilewidth").as_int();

		// L05: DONE 1: Add formula to go from isometric map to world coordinates
		mapData.type = MAPTYPE_UNKNOWN;
		if (strcmp(map.attribute("orientation").as_string(), "isometric") == 0)
		{
			mapData.type = MAPTYPE_ISOMETRIC;
		}
		if (strcmp(map.attribute("orientation").as_string(), "orthogonal") == 0)
		{
			mapData.type = MAPTYPE_ORTHOGONAL;
		}
	}

	return ret;
}

// L03: DONE 4: Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSets(pugi::xml_node mapFile) {

	bool ret = true;

	pugi::xml_node tileset;
	for (tileset = mapFile.child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();
		if (ret == true) ret = LoadTilesetDetails(tileset, set);
		if (ret == true) ret = LoadTilesetImage(tileset, set);
		mapData.tilesets.Add(set);
	}

	return ret;
}

// L03: DONE 4: Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// L03: DONE 4: Load Tileset attributes
	set->name.Create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->tilecount = tileset_node.attribute("tilecount").as_int();
	set->columns = tileset_node.attribute("columns").as_int();

	return ret;
}

// L03: DONE 4: Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// Load Tileset image
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
	}

	return ret;
}

// L04: DONE 3: Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	//Load the attributes
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();

	// Call Load Properties
	LoadProperties(node, layer->properties);

	//Reserve the memory for the tile array
	layer->data = new uint[layer->width * layer->height];
	memset(layer->data, 0, layer->width * layer->height);

	//Iterate over all the tiles and assign the values
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
	{
		layer->data[i] = tile.attribute("gid").as_int();
		i++;
	}

	return ret;
}

// L04: DONE 4: Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) {
	bool ret = true;
	for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		//Load the layer
		MapLayer* mapLayer = new MapLayer();
		ret = LoadLayer(layerNode, mapLayer);

		//add the layer to the map
		mapData.layers.Add(mapLayer);
	}

	return ret;
}

// L06: TODO 6: Load a group of properties from a layer and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	for (pugi::xml_node propertieNode = node.child("properties").child("property"); propertieNode; propertieNode = propertieNode.next_sibling("property"))
	{
		Properties::Property* p = new Properties::Property();
		p->name = propertieNode.attribute("name").as_string();
		p->value = propertieNode.attribute("value").as_int();

		properties.list.Add(p);
	}
	
	return ret;
}

bool Map::CreateWalkabilityMap(int& width, int& height, uchar** buffer) const
{
	bool ret = false;
	ListItem<MapLayer*>* item;
	item = mapData.layers.start;

	for (item = mapData.layers.start; item != NULL; item = item->next)
	{
		MapLayer* layer = item->data;

		if (layer->properties.GetProperty("Navigation", 0) == 0)
			continue;

		uchar* map = new uchar[layer->width * layer->height];
		memset(map, 1, layer->width * layer->height);

		for (int y = 0; y < mapData.height; ++y)
		{
			for (int x = 0; x < mapData.width; ++x)
			{
				int i = (y * layer->width) + x;

				int tileId = layer->Get(x, y);
				TileSet* tileset = (tileId > 0) ? GetTilesetFromTileId(tileId) : NULL;

				if (tileset != NULL)
				{
					map[i] = (tileId - tileset->firstgid) > 0 ? 0 : 1;
				}
			}
		}

		*buffer = map;
		width = mapData.width;
		height = mapData.height;
		ret = true;

		break;
	}

	return ret;
}

bool Map::GetEnemyStateXml(int index)
{
	pugi::xml_document saveGame;
	saveGame.load_file(SAVE_STATE_FILENAME);

	std::string p = "enemy";
	std::string s = std::to_string(index);
	std::string t = p + s;
	const char* c = t.c_str();

	bool ret = saveGame.child("game_state").child("entities").child("enemies").child(c).attribute("state").as_bool();

	return ret;
}