#include "App.h"
#include "AssetsManager.h"


ModuleAssetsManager::ModuleAssetsManager() : Module()
{
	name = ("assetsManager");
	
	//https://icculus.org/physfs/
	//https://icculus.org/physfs/docs/html/physfs_8h.html

	/*TODO 1: initialize physFS*/
	PHYSFS_init(nullptr);

	//After initializing physFS, you can uncomment this function (only required in Debug)
	//Create the default path
	PHYSFS_mount(".", nullptr, 1);
}


ModuleAssetsManager::~ModuleAssetsManager()
{
	/*TODO 1: close any file open for physFS*/
	PHYSFS_deinit();
}

bool ModuleAssetsManager::Awake(pugi::xml_node& config)
{
	/*TODO 2: add the search path*/
	PHYSFS_addToSearchPath("Assets.zip", 1);

	return true;
}


bool ModuleAssetsManager::CleanUp()
{
	return false;
}

SDL_RWops* ModuleAssetsManager::Load(const char* path) const
{
	char* buffer;
	uint bytes = LoadData(path, &buffer); //get the size of the data from the function Load Data

	//https://wiki.libsdl.org/SDL_RWops

	if (bytes > 0)
	{
		SDL_RWops* r = SDL_RWFromConstMem(buffer, bytes);

		return r;
	}
	else
		return nullptr;

}


uint ModuleAssetsManager::LoadData(const char* path, char** buffer) const
{
	uint ret = 0;
	
	/*TODO 3: Open and read the file*/
	PHYSFS_file* data_file = PHYSFS_openRead(path);

	if (data_file != nullptr)//look if the file is not null
	{
		int file_lenght = PHYSFS_fileLength(data_file); //read the file length to reserve the bytes we need.

		*buffer = new char[(uint)file_lenght]; //allocate memory in a buffer of the size of the file

		/*TODO 4: read the data formm physFS*/
		uint readed = PHYSFS_read(data_file, *buffer, 1, (uint)file_lenght); //read data from a physFS filehandle

		if (readed != file_lenght) //if file lenght is not the same that one was readed, thats an error
		{
			RELEASE(buffer); //clean the buffer
		}
		else
			ret = readed; //return the size of the data

		PHYSFS_close(data_file); //close the physFS used to read the data
	}

	return ret;
}


