#include "Camera.h"

Camera::Camera(){}
Camera::Camera(Vector4 camPos_ ,Vector4 view_, Vector4 up_, Vector4 right_) :camPosV(camPos_),viewV(view_),upV(up_),rightV(right_){}
/******************************************************************************
	\fn		Matrix4 WorldToCam();

	\brief	Calculates the world to camera
******************************************************************************/
Matrix4 Camera::WorldToCam() {

	Matrix4 trans = Translate(camPosV);

		float cosA = -viewV.z / viewV.Length() ;

		float sinA = viewV.x / viewV.Length();

		Matrix4 rot1 = RotateEuler(cosA,sinA,Y_AXIS);

		Vector4 newView = rot1 * viewV;
		float cosB = (sqrt(newView.x * newView.x + newView.z * newView.z) /newView.Length());

		float sinB = -newView.y / newView.Length();
		Matrix4 rot2 = RotateEuler(cosB, sinB, X_AXIS);
		newView = rot2 * newView;

		Vector4  newUp = rot2 * rot1 * trans * upV;

		float cosY = newUp.y /newUp.Length() ;

		float sinY = newUp.x / newUp.Length();

		Matrix4 rot3 = RotateEuler(cosY,sinY, Z_AXIS);
		newUp = rot3 * newUp;

		trans = Translate(-camPosV);
		 rot1 = RotateEuler(cosA, sinA, Y_AXIS);
		 rot2 = RotateEuler(cosB, sinB, X_AXIS);
		 rot3 = RotateEuler(cosY, sinY, Z_AXIS);
		Matrix4 finalRot = rot3 * rot2 * rot1 * trans;
		Matrix4 mat;

		mat.m[0][0] = 1;
		mat.m[0][1] = 0;
		mat.m[0][2] = 0;
		mat.m[0][3] = 0;
		mat.m[1][0] = 0;
		mat.m[1][1] = 1;
		mat.m[1][2] = 0;
		mat.m[1][3] = 0;
		mat.m[2][0] = 0;
		mat.m[2][1] = 0;
		mat.m[2][2] = 1;
		mat.m[2][3] = 0;
		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;
		return finalRot;
		//return mat;
		
	

	return Rotate(-30, Y_AXIS) * Rotate(-45, Z_AXIS) * Rotate(90, X_AXIS) *Translate(-camPosV);
}

void Camera::Update(Vector4 tPos, Vector4 tOre, int  camMode) {

	if (camMode == 0) {
		camPosV = tPos;
		viewV = tOre;
		rightV = Vector4(0, 1, 0, 0);
		upV = Vector4(0, 1, 0, 0);
		return;
		
	}
	else if (camMode == 1) {
		camPosV = tPos - tOre * distance + Vector4(0, 1, 0, 0) * height;
		viewV = (tPos - camPosV) / (tPos - camPosV).Length();
		rightV = viewV.Cross(Vector4(0, 1, 0, 0));
		upV = rightV.Cross(viewV);
	}
	else  if (camMode == 2) {
		camPosV = Vector4(0, 0, 0, 0);
		viewV = Vector4(0, 0, -1, 0);
		rightV = Vector4(1, 0, 0, 0);
		upV = Vector4(0, 1, 0, 0);
	}
	
}
void  Camera::Movement() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {}
	//if E is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		distance++;
	
	}

	//if Q is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && distance != 5) {

		distance--;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {}
	//if E is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		height++;

	}

	//if Q is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && height != 1 ) {

		height--;
	}
}