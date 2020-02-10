#ifndef GAME_H
#define GAME_H

#include <Debug.h>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Vector3f.h>
#include <Matrix3f.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void cubeRotation();

	sf::Clock clock;
	sf::Time elapsed;

	float rotationAngle = 0.0f;
};

#endif