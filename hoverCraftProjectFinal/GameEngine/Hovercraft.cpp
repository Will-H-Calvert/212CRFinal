#include "Hovercraft.h"
#include "CubeCollider.h"

Hovercraft::Hovercraft(glm::vec3 pos) :GameObject(pos) {
	Hovercraft::collider = new CubeCollider(&this->position,1.5,1.5,1.5);
}

Hovercraft::~Hovercraft(){
	delete Hovercraft::collider;
	Hovercraft::collider = NULL;
}

unsigned int Hovercraft::setupDrawing(unsigned int listBase) {
	this->base = listBase;
	// Draw ship.
	glNewList(this->base, GL_COMPILE);
		glPushMatrix();
			glColor3f(-2, 0, 2);
			glutSolidCone(0.5, 0.75, 30, 30);
			//glRotatef(-90, 0, 1, 0);
			glRotatef(90, 0, 1, 0);
			glPushMatrix();
				glTranslatef(0.4, 0, 0);
				glColor3f(1, 1, 1);
				glutSolidCube(0.8);
			glPopMatrix();
		glPopMatrix();
	glEndList();

	return this->base + 1;
}

void Hovercraft::drawScene() {
	glPushMatrix();
		glTranslatef(this->position.x, this->position.y, this->position.z);
		//rotate openGL object
		glRotatef(pitchAngle, 0.0, 0.0, 1.0);
		glRotatef(rotationAngle, 0.0, 1.0, 0.0);
		glCallList(this->base); // Draw Hovercraft.
	glPopMatrix(); // End draw Hovercraft.

	//if we are in debug mode then:
	if (false) {
		//display heading vector
		glPushMatrix();
			glBegin(GL_LINES);
				glColor3f(0, 1, 0);
				glVertex3f(position.x, position.y, position.z);
				glVertex3f(position.x + heading.x, position.y + heading.y, position.z + heading.z);
			glEnd();
		glPopMatrix();
		//display the collider bounding box
		this->collider->Draw();
	}
}

void Hovercraft::start() {
}

void Hovercraft::update(int deltaTime) {
	float turningSpeed = TURNING_SPEED * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time

	if (specialKeys[GLUT_KEY_DOWN]) {//braking
		if (currentVelocity < 20) {
			currentVelocity -= 0.03;
		}
	}
	if (specialKeys[GLUT_KEY_PAGE_UP]) {
		this->pitchAngle += turningSpeed; //in degrees not radians
	}
	if (specialKeys[GLUT_KEY_PAGE_DOWN]) {
		this->pitchAngle -= turningSpeed; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_LEFT]) {
		this->rotationAngle += turningSpeed; //in degrees not radians
	}
	if (specialKeys[GLUT_KEY_UP]) {//speeds up the craft
		if (currentVelocity < 20) {//making sure craft stays underits own max speed
			currentVelocity += 0.3;
		}
	}
	if (specialKeys[GLUT_KEY_RIGHT]) {
		this->rotationAngle -= turningSpeed; //in degrees not radians
	}
	if (currentVelocity > 0) {//slows the craft down slowly over time.
		currentVelocity -= 0.01;
	}
	else//just in case it pushes it into reverse
	{
		currentVelocity = 0;
	}
	std::cout << currentVelocity << std::endl;
	float moveStep = currentVelocity * (deltaTime / 1000.0); //movement speed in units per second * deltaTime in sec = moveStep
	this->position += this->heading * moveStep;//constatnly moves the craft forward by its remaining momentum
											   //rotate the heading
											   //In the drawscene we will need to rotate by the full rotation since the start
											   //Therfore we start heard from the original startingheading, so that we can use the same variables for the rotations
	this->heading = glm::rotate(this->startingHeading, glm::radians(rotationAngle), glm::vec3(0.0, 1.0, 0.0));
	this->heading = glm::rotate(this->heading, glm::radians(pitchAngle), glm::vec3(0.0, 0.0, 1.0));
}

void Hovercraft::collides(Collider* other) {
	if (debugMode) {
		std::cout << "Hovercraft collides!" << std::endl;
	}
}