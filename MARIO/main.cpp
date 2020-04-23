#include "Main.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "GameManager.h"

void CloseSDL();
void InitGameManager();
bool InitSDL();
void Render();
void Update();

Uint32 gOldTime;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer;

bool quit = false;

int main(int argc, char* agrs[])
{
	//Initialise SDL elements
	if (InitSDL())
	{
		InitGameManager();
		GameManager::Instance()->soundManager->PlayMusic("AUDIO/Mario.mp3");
		gOldTime = SDL_GetTicks();
		//Game Loop
		while (!quit)
		{
			Render();
			Update();
		}
	}
	
	CloseSDL();
	return 0;
}

void CloseSDL()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	IMG_Quit();
	SDL_Quit();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
}

void InitGameManager()
{
	GameManager::Instance()->collision = new Collisions();
	GameManager::Instance()->soundManager = new SoundManager();
	GameManager::Instance()->gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);
	GameManager::Instance()->camera = new Camera(Rect2D(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	GameManager::Instance()->scoreManager = new ScoreManager();
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL Did Not Initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("GAEM",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Window Was Not Created. Error: " << SDL_GetError();
			return false;
		}
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer !=NULL)
	{
		int imageFlags = IMG_INIT_PNG;
		if (!IMG_Init(imageFlags)&&imageFlags)
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
	}
	else
	{
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Mixer Could Not Initialise. Error: " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

void Render()
{
	//SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);

	GameManager::Instance()->gameScreenManager->Render();

	SDL_RenderPresent(gRenderer);
}

void Update()
{
	Uint32 newTime = SDL_GetTicks();
	//Event Handler
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT:
		quit = true;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			quit = true;
			return;
		case SDLK_SPACE:
			GameManager::Instance()->gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
		}
	}
	GameManager::Instance()->gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return;
}


