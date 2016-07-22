#include <iostream>
#include <SDL/SDL.h>
#include "gl_core_3_3.hpp"

using namespace GL;

int main(int, char**) {
	
	SDL_Window* window;
	SDL_GLContext context;
	
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL." << std::endl;
		return -1;
	}
	
	// Set OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	// Create window
	window = SDL_CreateWindow(
		"Gloic",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1136, 640,
		SDL_WINDOW_OPENGL
	);
	if (!window) {
		std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		return -1;
	}
	
	// Create OpenGL context
	context = SDL_GL_CreateContext(window);
	if (!context) {
		std::cout << "Failed to create context: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_GL_MakeCurrent(window, context);
	
	// Load OpenGL
	if (!glLoadFunctions(SDL_GL_GetProcAddress)) {
		std::cout << "OpenGL failed to load." << std::endl;
		return -1;
	}
	
	// Display OpenGL info
	std::cout << "OpenGL:   " << glGetString(GL_VERSION)                  << std::endl;
	std::cout << "Vendor:   " << glGetString(GL_VENDOR)                   << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER)                 << std::endl;
	std::cout << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	
	// Quit SDL
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}