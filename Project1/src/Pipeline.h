/*!
*	\file		Pipeline.h
*	\brief		Pipeline for the tank
*	\author		Eduardo de Vega - eduardo.devega@digipen.edu
*	\date		11/02/2020
*
*/
#pragma once
#include "Rasterizer.h"
/******************************************************************************
	\fn		PerspectiveProjection
	\brief	Calculates the perspective projection matrix
******************************************************************************/
Matrix4 PerspectiveProjection();


/******************************************************************************
	\fn		WinToVP
	\brief	Calculates the window to view
******************************************************************************/
Matrix4 WinToVP(float Hw, float Ww, float Hv, float Wv);
/******************************************************************************
	\fn   Scale
	\brief Calculates the Scale transformation matrix
******************************************************************************/
Matrix4 Scale(Vector4 vec);
/******************************************************************************
	\fn		Translate
	\brief	Calculates the perspective projection matrix
******************************************************************************/
Matrix4 Translate(Vector4 vec);
/******************************************************************************
	\fn		Rotate
	\brief	Calculates the Rotation matrix
******************************************************************************/
Matrix4 Rotate(float angle, int axis);

Matrix4 RotateEuler(float cosA, float sinA, int axis);