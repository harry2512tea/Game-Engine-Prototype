#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdexcept>
#include <list>
#include <iostream>
#include <fstream> 

//#include <wavefront/wavefront.h>

#include "RenderTexture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Object.h"
#include "Scene.h"
#include "Time.h"

//#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

int main()
{
	SceneTime* time = SceneTime::getInstance();

	int windowWidth = 1440;
	int windowHeight = 810;
	SDL_Window *window = SDL_CreateWindow("haha window go brrrr", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("glew not working :) ");
	}

	float PrevWindowWidth = windowHeight, PrevWindowHeight = windowWidth;
	int width = 0;
	int height = 0;
	unsigned int lastTime = 0;
	unsigned int currentTime = 0;
	float deltaTime = 0.0166666667f;

	time->SetDeltaTime(deltaTime);

	bool quit = false;

	RenderTexture rtx(windowWidth, windowHeight);

	Mesh sm(0);


	Shader ss("shaders/postprocess.vert", "shaders/null.frag");


	Scene mainScene = Scene(window, "SceneData/MainScene.txt");

	

	while (!quit)
	{
		SDL_GetWindowSize(window, &width, &height);

		//std::cout << width << std::endl;
		/*if (PrevWindowHeight != height || PrevWindowWidth != width)
		{
			PrevWindowHeight = height;
			PrevWindowWidth = width;
			rtx = RenderTexture(width, height);
		}*/

		rtx.bind();

		SDL_Event event = { 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		mainScene.DrawScene();


		glUseProgram(0);

		rtx.unbind();

		//render scene

		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ss.use();
		glBindVertexArray(sm.id());
		glBindTexture(GL_TEXTURE_2D, rtx.getTexture());
		glDrawArrays(GL_TRIANGLES, 0, sm.vert_count());
		

		glUseProgram(0);

		SDL_GL_SwapWindow(window);

		//currentTime = SDL_GetTicks();
		//deltaTime = (float)(currentTime - lastTime) / 1000.0f;
		//lastTime = currentTime;

		currentTime = SDL_GetPerformanceCounter();
		deltaTime = (float)((currentTime - lastTime) / (float)SDL_GetPerformanceFrequency());
		lastTime = currentTime;

		if (deltaTime > 0.1f)
		{
			deltaTime = 0.1f;
		}
		time->SetDeltaTime(deltaTime);
		mainScene.updateObjects(deltaTime);

	}

	return 0;
}