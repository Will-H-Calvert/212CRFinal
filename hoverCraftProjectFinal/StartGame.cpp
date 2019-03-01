

#include "GameEngine/GameEngine.h"
#include "GameEngine/Grass.h"
#include "GameEngine/Hovercraft.h"
#include "GameEngine/Obstacle.h"
#include "math.h"
void semiDraw(float radius, bool positive, glm::vec3 left) { // Radius in arbitrary coordinate units, bool for positive or negative z, left is the point on the xircle with the smallest x value
	///draws a semi circle of given radius to the right of given point left.
	float nz = nz = sqrt(sqrt(pow((radius*radius - (left.x+0.5) * (left.x + 0.5)), 2)));;
	float nx = 0;
	float centreXCo = left.x + radius;

	float deltaX;
	float steps = radius * 2;
	float colStep = (0.4 / steps);
	Colour wallColour = {0.3,0.1,0.7};
	for (int i = left.x+1; i < (left.x + radius * 2);i++) {
		deltaX = i - centreXCo;
		if (positive) {
			nz = sqrt(sqrt(pow((radius*radius - deltaX * deltaX), 2)));
		}
		else
		{
			nz = sqrt(sqrt(pow((radius*radius - deltaX * deltaX), 2)))*-1;
		}
		wallColour.r += colStep;
		wallColour.b -= colStep;
		std::cout << i;
		std::cout << ", ";
		std::cout << nz << std::endl;
		GameEngine::addGameObject(new Obstacle(glm::vec3(i, 0.0, nz+left.z), { wallColour.r, 0.1f, wallColour.b }));
	}
	
	
}
void tunnelDraw(glm::vec3 topLeft, int tunnelLength, int tunnelWidth) {//top left is the point with smallest x value and largest Z value 
	float baseZ = topLeft.z;
	float baseX = topLeft.x;
	for (float i = baseZ; i< baseZ+tunnelLength; i++) {
		GameEngine::addGameObject(new Obstacle(glm::vec3(baseX, 0 ,i), { 0.5f, 0.1f, 0.5f}));
		GameEngine::addGameObject(new Obstacle(glm::vec3(baseX+tunnelWidth, 0, i), { 0.5f, 0.1f, 0.5f }));
	}
}
int main(int argc, char **argv) {

	//Initialise the engine.
	GameEngine::initEngine(argc, argv, "Hovercraft tutorial",true);

	//Adding grass field.
	GameEngine::addGameObject(new Grass(glm::vec3(0, 0, 0), glm::vec3(50, 0, 50)) );

	
	//Adding an Obstacle.
	semiDraw(12,true, glm::vec3(0,0,-2));
	semiDraw(22, true, glm::vec3(-10, 0, -2));
	semiDraw(12, false, glm::vec3(0, 0, -20));
	semiDraw(22, false, glm::vec3(-10, 0, -20));
	tunnelDraw(glm::vec3(-9,0,-23),25,10);
	tunnelDraw(glm::vec3(23,0,-23),25,10);
	//Add a movable hovercraft.
	GameEngine::addGameObject(new Hovercraft(glm::vec3(-2, 0, 2)), true);


	//Start the game engine.
	GameEngine::startEngine();

	return 0;
}