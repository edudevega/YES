/*!
*	\file		Tank.h
*	\brief		members functions for the tank
*	\author		Eduardo de Vega - eduardo.devega@digipen.edu
*	\date		11/02/2020
*
*/
#pragma once
#include "Rasterizer.h"

struct Camera {

	Camera(Vector4 camPos_ ,Vector4 view_,Vector4 up_, Vector4 right_);
	Vector4 camPosV;
	Vector4 viewV;
	Vector4 upV;
	Vector4 rightV;


	/******************************************************************************
	\fn		WorldToCam
	\brief	Calculates world to camera transformation
	******************************************************************************/
	Matrix4 WorldToCam();

	void Update(Vector4 vec);
};
