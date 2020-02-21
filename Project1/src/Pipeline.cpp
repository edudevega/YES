/*!
*	\file		Pipeline.cpp
*	\brief		Pipeline for the tank
*	\author		Eduardo de Vega - eduardo.devega@digipen.edu
*	\date		11/02/2020
*
*/

#include "Pipeline.h"
/******************************************************************************
	\fn		PerspectiveProjection
	\brief	Calculates the perspective projection matrix
******************************************************************************/
Matrix4 PerspectiveProjection(void) {
	Matrix4 mat;
	//Set all rows and cols to 0
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {
			mat.m[i][j] = 0;
			if (i == j)
				//Set on the identity the focal length
				mat.m[i][j] = CS250Parser::focal;
		}
	}

	mat.m[3][3] = 0;
 	mat.m[3][2] = -1;

	return mat;
}

/******************************************************************************
	\fn		WinToVP
	\brief	Calculates the window to view
******************************************************************************/
Matrix4 WinToVP(float Hw, float Ww, float Hv, float Wv ) {

	Matrix4 mat;

	//Set everything to zero
	for (int i = 0; i < 16; i++)
		mat.v[i] = 0;

	//Set all the matrix values
	mat.m[0][0] = Wv/Ww;
	mat.m[1][1] = -Hv/Hw;
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	mat.m[0][3] = Wv/2;
	mat.m[1][3] = Hv/2;

	return mat;
}
/******************************************************************************
	\fn   Scale
	\brief Calculates the Scale transformation matrix
******************************************************************************/
Matrix4 Scale(Vector4 vec) {

	Matrix4 mat;

	//set the matrix to zeroes
	for (int i = 0; i < 16; i++)
			mat.v[i] = 0;

	//Set the data
	mat.m[0][0] = vec.x;
	mat.m[1][1] = vec.y;
	mat.m[2][2] = vec.z;

	mat.m[3][3] = 1;
	return mat;
}
/******************************************************************************
	\fn		Translate
	\brief	Calculates the perspective projection matrix
******************************************************************************/
Matrix4 Translate(Vector4 vec){

		Matrix4 mat;

		for (int i = 0; i < 16; i++)
			mat.v[i] = 0;
			
		//Set all the values
		mat.m[0][0] = 1;
		mat.m[1][1] = 1;
		mat.m[2][2] = 1;
		mat.m[0][3] = vec.x;
		mat.m[1][3] = vec.y;
		mat.m[2][3] = vec.z;
		mat.m[3][3] = 1;

			return mat;
}
/******************************************************************************
	\fn		Rotate
	\brief	Calculates the Rotation matrix
******************************************************************************/
Matrix4 Rotate(float angle,int axis) {

			Matrix4 mat;

			//If the axis is the x or 1
			if (axis == X_AXIS) {

				//Set everything to zero
				for (int i = 0; i < 16; i++)
					mat.v[i] = 0;

				//Set the values of the matrix
				mat.m[0][0] = 1;
				mat.m[1][1] = cos(angle);
				mat.m[1][2] = -sin(angle);
				mat.m[2][1] = sin(angle);
				mat.m[2][2] = cos(angle);
				mat.m[3][3] = 1;

				return mat;
			}
			//If the axis is the y or 2
			if (axis == Y_AXIS) {

				//Set everything to zero
				for (int i = 0; i < 16; i++)
					mat.v[i] = 0;

				//Set the values of the matrix
				mat.m[0][0] = cos(angle);
				mat.m[1][1] = 1;
				mat.m[0][2] = sin(angle);
				mat.m[2][2] = cos(angle);
				mat.m[2][0] = -sin(angle);
				mat.m[3][3] = 1;

				return mat;
			}
			//If the axis is the z or 3
			if (axis == Z_AXIS) {

				//Set everything to zero
				for (int i = 0; i < 16; i++)
					mat.v[i] = 0;

				//Set the values of the matrix
				mat.m[0][0] = cos(angle);
				mat.m[2][2] = 1;
				mat.m[1][0] = sin(angle);
				mat.m[1][1] = cos(angle);
				mat.m[0][1] = -sin(angle);
				mat.m[3][3] = 1;

				return mat;
			}
			return mat;
}
/******************************************************************************
	\fn		Rotate
	\brief	Calculates the Rotation matrix
******************************************************************************/
Matrix4 RotateEuler(float cosA, float sinA, int axis) {

	Matrix4 mat;

	//If the axis is the x or 1
	if (axis == X_AXIS) {

		//Set everything to zero
		for (int i = 0; i < 16; i++)
			mat.v[i] = 0;

		//Set the values of the matrix
		mat.m[0][0] = 1;
		mat.m[1][1] = cosA;
		mat.m[1][2] = -sinA;
		mat.m[2][1] = sinA;
		mat.m[2][2] = cosA;
		mat.m[3][3] = 1;

		return mat;
	}
	//If the axis is the y or 2
	if (axis == Y_AXIS) {

		//Set everything to zero
		for (int i = 0; i < 16; i++)
			mat.v[i] = 0;

		//Set the values of the matrix
		mat.m[0][0] = cosA;
		mat.m[1][1] = 1;
		mat.m[0][2] = sinA;
		mat.m[2][2] = cosA;
		mat.m[2][0] = -sinA;
		mat.m[3][3] = 1;

		return mat;
	}
	//If the axis is the z or 3
	if (axis == Z_AXIS) {

		//Set everything to zero
		for (int i = 0; i < 16; i++)
			mat.v[i] = 0;

		//Set the values of the matrix
		mat.m[0][0] = cosA;
		mat.m[2][2] = 1;
		mat.m[1][0] = sinA;
		mat.m[1][1] = cosA;
		mat.m[0][1] = -sinA;
		mat.m[3][3] = 1;

		return mat;
	}
	return mat;
}


