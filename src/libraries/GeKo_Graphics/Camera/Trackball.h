#pragma once

#include "GeKo_Graphics/Defs.h"
#include "Camera.h"
#include "GeKo_Graphics/Window.h"

class Trackball : public Camera
{
public:
	Trackball(int width, int height);
	~Trackball();

	void setPosition(glm::vec4 position);
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);

	// changes the positon in direction of the z axis
	void moveForward();
	void moveBackward();

	// changes the positon in a circle around the object
	void moveLeft();
	void moveRight();

	// changes the positon in a half-circle over the object
	void moveUp();
	void moveDown();


protected:

	double m_radius;
	// Remember the last x and y position
	double m_oldX, m_oldY;
	// Angle in x direction
	double m_phi;
	// Angle in y direction
	double m_theta;
	// Speed of movement
	float m_speed;
	float m_sensitivity;
};

