#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "Module.h"
#include "Animation.h"
#include "Menu.h"

#define NUM_SHOP_BUTTONS 4
#define NUM_SHOP_INTERACT_BUTTONS 2

struct Button;

enum class DIALOGS
{
	NO_ONE = -1,
	RENATO,
	HERRERO,
	MEDICO,
	GRANJERO,
	ALDEANO,
	ENEMIGO
};

struct Shop_objects
{
	std::string item;
	int cost;
	bool selled = false;
};

class Dialog : public Module
{
public:
	Dialog(bool enabled);

	virtual ~Dialog();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	int limitLenght = 0;
	int limitLenght2 = 0;

	uint letlengh = 0;
	uint letlengh2 = 0;

	int letter_cd = 0;

	bool inDialog = false;

	DIALOGS actual_dialog = DIALOGS::NO_ONE;

	void QuitDialogs()
	{
		inDialog = false;
		actual_dialog = DIALOGS::NO_ONE;
	}

	void SetPressE_Hide(bool hide)
	{
		press_e_hide = hide;
	}

	bool InDialog()
	{
		return (in_shop != 0 || inDialog);
	}

	void UpdateShop();

private:
	
	pugi::xml_document dialogFile;
	pugi::xml_node dialog;
	pugi::xml_node renato;
	pugi::xml_node text1;

	std::string linea1String_Renato[5];
	std::string linea2String_Renato[5];
	const char* linea1Char_Renato[5];
	const char* linea2Char_Renato[5];
	int renato_text = -1;
	int renato_maxtext = 5;
	bool dialog_finish = false;

	std::string linea1String_Herrero;
	std::string linea2String_Herrero;
	const char* linea1Char_Herrero;
	const char* linea2Char_Herrero;
	int herrero_text = -1;
	int herrero_maxtext = 1;

	std::string linea1String_Medico;
	std::string linea2String_Medico;
	const char* linea1Char_Medico;
	const char* linea2Char_Medico;
	int medico_text = -1;
	int medico_maxtext = 1;

	std::string linea1String_Granjero;
	std::string linea2String_Granjero;
	const char* linea1Char_Granjero;
	const char* linea2Char_Granjero;
	int granjero_text = -1;
	int granjero_maxtext = 1;


	std::string linea1String_Aldeano;
	const char* linea1Char_Aldeano;
	int aldeano_text = -1;
	int aldeano_maxtext = 1;

	/*
	std::string linea1String_Templario;
	std::string linea2String_Templario;
	const char* linea1Char_Templario;
	const char* linea2Char_Templario;
	int templario_text = 0;
	int templario_maxtext = 1;

	
	std::string linea1String_Seta;
	std::string linea2String_Seta;
	const char* linea1Char_Seta;
	const char* linea2Char_Seta;
	*/
	bool LoadDialog();
	uint letter_fx; // normal
	uint letterA_fx; // agudo
	uint letterG_fx; // grave
	void PlayLetterSound();

	SDL_Texture* whitemark_300x80 = NULL;
	SDL_Texture* whitemark_1200x140 = NULL;

	SDL_Texture* press_e;
	bool press_e_hide = true;
	Animation* anim = NULL;
	Animation idle_e;

	bool ContinueDialog(int& actual_text, int max_text);

	// shop
	int chosed;
	int in_shop; // 0 --> all closed, 1 --> herrero, 2 --> medico, 3 --> granjero
	Button shop_buttons[NUM_SHOP_BUTTONS];
	Button shop_interact_buttons[NUM_SHOP_INTERACT_BUTTONS];
	Shop_objects shop1[4];
	Shop_objects shop2[4];
	Shop_objects shop3[4];
	SDL_Texture* whitemark_128x128;
	SDL_Texture* whitemark_800x150;
	SDL_Texture* whitemark_1240x680;
	Shop_objects* item_saved = new Shop_objects;
	std::string GetObjectForShop(const char* aei);

	// sound
	uint click_sound;
	uint hover_sound;
	bool hover_playing = false;
	bool InAnyButton();

};

#endif
