#include "Camera.h"


Camera::Camera(Vector4 camPos_ ,Vector4 view_, Vector4 up_, Vector4 right_) :camPosV(camPos_),viewV(view_),upV(up_),rightV(right_){}
/******************************************************************************
	\fn		Matrix4 WorldToCam();

	\brief	Calculates the world to camera
******************************************************************************/
Matrix4 Camera::WorldToCam() {
	/*Matrix4 mat;
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
	
	return mat;*/

	return Translate(-camPosV);
}

void Camera::Update(Vector4 vec) {
	camPosV = vec;
}