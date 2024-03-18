#include <iostream>
#include <string>
#include <vector>

#if defined(_WIN32)
	#include <SDL.h>
	#include <SDL_thread.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>
#endif // defined(_WIN32)

#if defined(__linux__)
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_thread.h>
#endif // defined(__linux__)

using namespace std;