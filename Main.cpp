// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "SDL_mixer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char** argv)
{
	Mix_Music* music=NULL;
	

	Game game;
	bool success = game.Initialize();
	
	if (success)
	{
	
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		music = Mix_LoadMUS("Assets/music.ogg");
		Mix_PlayMusic(music, -1);
		
		//SDL_Delay(3000);
		
		/*
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_CloseFont(font);
		*/
		game.RunLoop();
		
	}
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
	game.Shutdown();
	return 0;
}
