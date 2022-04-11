#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "Module.h"
#include "Animation.h"

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
	bool inDialogRenato = false;
	bool inDialogAlly = false;
	bool inDialogEnemy = false;

	void SetPressE_Hide(bool hide)
	{
		press_e_hide = hide;
	}

private:
	
	pugi::xml_document dialogFile;
	pugi::xml_node dialog;
	pugi::xml_node renato;
	pugi::xml_node text1;

	std::string linea1String_Renato;
	std::string linea2String_Renato;
	const char* linea1Char_Renato;
	const char* linea2Char_Renato;

	std::string linea1String_Herrero;
	std::string linea2String_Herrero;
	const char* linea1Char_Herrero;
	const char* linea2Char_Herrero;

	std::string linea1String_Granjero;
	std::string linea2String_Granjero;
	const char* linea1Char_Granjero;
	const char* linea2Char_Granjero;

	std::string linea1String_Medico;
	std::string linea2String_Medico;
	const char* linea1Char_Medico;
	const char* linea2Char_Medico;

	std::string linea1String_Templario;
	std::string linea2String_Templario;
	const char* linea1Char_Templario;
	const char* linea2Char_Templario;

	std::string linea1String_Seta;
	std::string linea2String_Seta;
	const char* linea1Char_Seta;
	const char* linea2Char_Seta;

	bool LoadDialog();

	SDL_Texture* whitemark_300x80 = NULL;
	SDL_Texture* whitemark_1200x140 = NULL;

	SDL_Texture* press_e;
	bool press_e_hide = true;
	Animation* anim = NULL;
	Animation idle_e;

};

#endif
