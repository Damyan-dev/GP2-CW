#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <SDL/SDL_mixer.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "BGAudio.h"

// Assings the two states the game will switch between during initialisation and upon quitting it.
enum class GameState{PLAY, EXIT};

// Holds all main methods that are initialised upon game start.
class MainGame
{
public:
	MainGame();
	~MainGame();

	void run(); // Starts the game.

private:
	void initialStartup(); // Loads all main components on start.
	void eventTracker(); // Tracks the current state of the game.
	void mainLoop(); // Contains the main game loop where it calls all required functions during runtime.
	void renderGame(); // Renders the meshes within the game window.
	void playBGAudio(unsigned int Source, glm::vec3 pos); // Play background audio during runtime.

	bool collisionDetect(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad); // Checks if objects collide with each other.
	
	// This section stores the variables for the required game components.
	Display _gameDisplay;
	GameState _gameState;
	Mesh model1, model2, model3;
	Camera myCamera;
	Shader shader;
	BGAudio bgAudio;

	float oppositeDir;
};

