/*!
*	\file		Tank.h
*	\brief		members functions for the tank
*	\author		Eduardo de Vega - eduardo.devega@digipen.edu
*	\date		11/02/2020
*
*/
#pragma once
#include "Rasterizer.h"

struct Body {

	Vector4 mScale;

	Vector4 mPos;

	Vector4 mOrientation;
	float mAngle;
	int mAxis;
	CS250Parser data;
	Vector4 v[8];
	Vector4 v_world[8];
	Body(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis);
	void Movement();
	void Draw(sf::Image &image, bool mode);
	virtual void Update();
	virtual Matrix4 GetMatrix();
	
};
struct Turret  {

	Vector4 mScale;

	Vector4 mPos;

	Vector4 mOrientation;
	float mAngle;
	int mAxis;
	CS250Parser data;
	Vector4 v[8];
	Vector4 v_world[8];
	Turret(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat);
	void Draw(sf::Image &image, bool mode);
	void Update(Matrix4 mat);
	Matrix4 GetMatrix();
	void Movement();

};
struct Gun{

	Vector4 mScale;

	Vector4 mPos;

	Vector4 mOrientation;
	float mAngle;
	int mAxis;
	CS250Parser data;
	Vector4 v[8];
	Vector4 v_world[8];
	Gun(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat1, Matrix4 mat2);
	void Draw(sf::Image &image ,bool mode);
	void Update(Matrix4 mat1, Matrix4 mat2);
	Matrix4 GetMatrix();
	void Movement();

};
struct Wheel {

	Vector4 mScale;

	Vector4 mPos;

	Vector4 mOrientation;
	float mAngle;
	int mAxis;
	CS250Parser data;
	Vector4 v[8];
	Vector4 v_world[8];
	Wheel(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat);
	void Draw(sf::Image &image, bool mode);
	void Update(Matrix4 mat);
	Matrix4 GetMatrix();
	void Movement();

};