#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY; // Initialises the game.
	Display* _gameDisplay = new Display(); // Creates the game window.
}

MainGame::~MainGame()
{
}

// Starts the game.
void MainGame::run()
{
	initialStartup(); 
	mainLoop();
}

// Initialises the main components on start up.
void MainGame::initialStartup()
{
	// Creates a game window.
	_gameDisplay.createDisplay(); 

	// Audio that will be played on game start. The audio file can be changed by editting the name at the end.
	bgAudio.addAudioTrack("..\\res\\BGM.wav");

	// Various objects that will be loaded on game start. You can change the models by editting the name at the end.
	model3.loadModel("..\\res\\sakuya.obj");
	model2.loadModel("..\\res\\dagger.obj");
	model1.loadModel("..\\res\\pocketwatch.obj");
	
	// Loads the camera on game start.
	myCamera.createCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	// Creates a new shader.
	shader.init("..\\res\\shader"); 
	oppositeDir = 1.0f;
}

// Contains the methods that allows the game to function upon start.
void MainGame::mainLoop()
{
	while (_gameState != GameState::EXIT)
	{
		playBGAudio(0, model2.getSpherePos());
		eventTracker();
		renderGame();
		collisionDetect(model1.getSpherePos(), model1.getSphereRadius(), model2.getSpherePos(), model2.getSphereRadius());
	}
}

// Plays back audio.
void MainGame::playBGAudio(unsigned int source, glm::vec3 pos) 
{
	bgAudio.playAudioTrack();
}

// Tracks the current game state.
void MainGame::eventTracker()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) 
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}

// Creates checks for object collision and reports it in the console.
bool MainGame::collisionDetect(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = ((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));
	
	if (distance*distance < (m1Rad + m2Rad))
	{
		cout << distance << '\n';
		return true;
	}
	else
	{
		return false;
	}
}

// Draws the game on screen.
void MainGame::renderGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	// This section stores the texture data within the assigned variables.
	Texture texture("..\\res\\sakuyatex.jpg"); 
	Texture texture1("..\\res\\pocketwatchtex.jpg"); 
	Texture texture2("..\\res\\daggertex.jpg");

	// model1 properties
	transform.SetPos(glm::vec3(sinf(-oppositeDir), -0.5, 0.9)); // Sets the model position in the 3D space.
	transform.SetRot(glm::vec3(-0.7, oppositeDir * 2.0, 0)); // Sets the model rotation.
	transform.SetScale(glm::vec3(5.0, 5.0, 5)); // Sets the model scale.
	
	shader.Bind();
	shader.Update(transform, myCamera);
	texture1.Bind(0); // Binds the textures to the model.
	model1.draw(); // Renders the model.
	model1.updateSphereData(*transform.GetPos(), 0.6f);
	
	// model2 properties
	transform.SetPos(glm::vec3(sinf(oppositeDir), 0.5, 0.9)); // Sets the model position in the 3D space.
	transform.SetRot(glm::vec3(0.0, oppositeDir * 5.0, 0.0)); // Sets the model rotation.
	transform.SetScale(glm::vec3(0.09, 0.09, 0.09)); // Sets the model scale.

	shader.Bind();
	shader.Update(transform, myCamera);
	texture2.Bind(0); // Binds the textures to the model.
	model2.draw(); // Renders the model.
	model2.updateSphereData(*transform.GetPos(), 0.6f);
	oppositeDir = oppositeDir + 0.05f;

	// model3 properties;
	transform.SetPos(glm::vec3(0.0, -0.7, 0.0)); // Sets the model position in the 3D space.
	transform.SetRot(glm::vec3(0.0, oppositeDir, 0.0)); // Sets the model rotation.
	transform.SetScale(glm::vec3(2.5, 2.5, 2.5)); // Sets the model scale.
	

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0); // Binds the textures to the model.
	model3.draw(); // Renders the model.
	model3.updateSphereData(*transform.GetPos(), 0.6f);
	oppositeDir = oppositeDir + 0.05f;

				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 