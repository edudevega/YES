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
	bool mIsDrawable = 1;
	Vector4 mPos;

	Vector4 mOrientation;
	float mAngle;
	int mAxis;
	CS250Parser data;
	Matrix4 mTransform;
	Matrix4 mPP;
	Matrix4 mWtV;
	Vector4 v[8];
	Vector4 v_world[8];
	Body() : mScale(Vector4(0,0,0,0)), mPos(Vector4(0, 0, 0, 0)), mAxis(0), mAngle(0), mOrientation(Vector4(0, 0, 0, 0)) {}
	Body(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis);
	void Movement();
	void Draw(sf::Image &image, bool mode);
	virtual void Update(Matrix4 mat);
	virtual Matrix4 GetMatrix();
	
};
struct Turret :public Body {

	Turret();
	Turret(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat);
	void Update(Matrix4 mat1, Matrix4 mat2);
	Matrix4 GetMatrix();
	void Movement();

};
struct Gun : public Body{

	
	Gun(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat1, Matrix4 mat2);
	void Update(Matrix4 mat1, Matrix4 mat2, Matrix4 mat3);
	void Movement();

};
struct Wheel : Turret{

	Wheel(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat);
	void Movement();

};

struct Cube : Body {

	Cube() {}
	Cube(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis);
	void Movement() {}
};