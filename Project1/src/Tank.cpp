/*!
*	\file		Tank.cmPP
*	\brief		members functions for the tank
*	\author		Eduardo de Vega - eduardo.devega@digipen.edu
*	\date		11/02/2020
*
*/
#include "Tank.h"
/******************************************************************************
	\fn		Body Constructor
	\brief	Constructor for the body class
******************************************************************************/
Body::Body(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis) : mScale(Scale_), mPos(Pos), mAxis(Axis), mAngle(Angle), mOrientation(Ore) {

	//Load the data from the file
	data.LoadDataFromFile();

	//Set the array of vertex to the data vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Calculate the mTransformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	mTransform = trans * rot * sca;
	mPP = PerspectiveProjection();
	mWtV = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	
}

/******************************************************************************
	\fn		Update
	\brief	Updates the vertices of the Body
******************************************************************************/
void Body::Update(Matrix4 mat) {
	
	//Calculate the mTransformations
	Matrix4 rot = Rotate(mAngle, mAxis);;
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	mTransform = mat * trans * rot * sca;
	
}

/******************************************************************************
	\fn		Movement
	\brief	Checks the input and modifies the respective values
******************************************************************************/
void Body::Movement() {
	
	//Reset the vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Angle to store how much does it rotate
	float angle = 0.0f;

	//Move it forward if Space is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		//Normalize the orientation
		mOrientation /= mOrientation.Length();

		//Add it to the position
		mPos += mOrientation ;
	}

	//If both are pressed at the same time do nothing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {}

	//if A is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

		//increase the angle
		angle += 0.05f;
		mAngle += 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);

		//AmPPly it to the orientation
		mOrientation =  rot * mOrientation;
	}

	//if D is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		//Decrese the angle
		angle -= 0.05f;
		mAngle -= 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);
		
		//AmPPly it to the orentation
		mOrientation = rot * mOrientation;
	}
}

/******************************************************************************
	\fn		Draw
	\brief	Draws the Body in the method wanted
******************************************************************************/
void Body::Draw(sf::Image &image, bool mode) {
	
	
	//AmPPly the to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = mTransform * v[i];
		if (v[i].z > -data.nearPlane)
			mIsDrawable = 0;
		else 
			mIsDrawable = 1;
		v[i] = mPP * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = mWtV * v[i];
	}
	//For looping on the colors
	int i = 0; 
	if (mIsDrawable) {
		//To draw all the vertices
		for (auto it = data.faces.begin(); it != data.faces.end(); ++it, i++) {
			//if mode is solid
			if (mode == 0)
				DrawTriangleSolid(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y),
					sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y),
					sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y),
					sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));

			//if mode is lines
			else {
				DrawMidpointLine(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y), sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));
				DrawMidpointLine(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y), sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));
				DrawMidpointLine(image, sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y), sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));


			}

		}
	}
}

/******************************************************************************
	\fn		GetMatrix
	\brief	returns the matrix for child mTransformations
******************************************************************************/
Matrix4 Body::GetMatrix() {

	//Calculate the matrices
	Matrix4 rot = Rotate(mAngle, mAxis);;
	Matrix4 trans = Translate(mPos);

	return (trans * rot);
}

/******************************************************************          TURRET        ****************************************************************************************/
/******************************************************************************
	\fn		turret Constructor
	\brief	Constructor for the turret class
******************************************************************************/
Turret::Turret() {}
/******************************************************************************
	\fn		turret Constructor
	\brief	Constructor for the turret class
******************************************************************************/
Turret::Turret(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis,Matrix4 mat){


	Body::mScale = Scale_;
	Body::mPos = Pos;
	Body::mOrientation = Ore;
	Body::mAngle = Angle;
	Body::mAxis = Axis;
	//Load the data from the file
	Body::data.LoadDataFromFile();

	//Set the array of vertex to the data vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Calculate the mTransformation matrices
	Matrix4 rot = Rotate(mAngle,mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Body::mPP  = PerspectiveProjection();
	Body::mWtV = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);
	mTransform = mat * trans * rot * sca;
	//Multyply by the parent matrix
	

}

/******************************************************************************
	\fn		GetMatrix
	\brief	returns the matrix for child mTransformations
******************************************************************************/
Matrix4 Turret::GetMatrix() {
	//Calculate the matrices
	Matrix4 rot = Rotate(mAngle, mAxis);;
	Matrix4 trans = Translate(mPos);

	return (trans * rot);
}

/******************************************************************************
	\fn		Movement
	\brief	Checks the input and modifies the respective values
******************************************************************************/
void Turret::Movement() {

	//Reset the vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Angle to store how much does it rotate
	float angle = 0.0f;

	//If both are pressed at the same time do nothing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {}

	//if E is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {

		//increase the angle
		angle += 0.05f;
		mAngle += 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);

		//AmPPly it to the orientation
		mOrientation = rot * mOrientation;
	}

	//if Q is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

		//Decrese the angle
		angle -= 0.05f;
		mAngle -= 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);

		//AmPPly it to the orentation
		mOrientation = rot * mOrientation;
	}
}

/******************************************************************************
	\fn		Update
	\brief	Updates the vertices of the turret
******************************************************************************/
void Turret::Update(Matrix4 mat1,Matrix4 mat2) {
	
	//Calculate the mTransformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Body::mPP = PerspectiveProjection();
	Body::mWtV = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Multyply by the parents matrix
	mTransform = mat1 * mat2  * trans * rot * sca;
}

/******************************************************************          GUN        ********************************************************************************************/

/******************************************************************************
	\fn		Gun Constructor
	\brief	Constructor for the Gun class
******************************************************************************/
Gun::Gun(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat1, Matrix4 mat2) {
	Body::mScale = Scale_;
	Body::mPos = Pos;
	Body::mOrientation = Ore;
	Body::mAngle = Angle;
	Body::mAxis = Axis;
	//Load the data from the file
	Body::data.LoadDataFromFile();

	//Set the array of vertex to the data vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Calculate the mTransformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Body::mPP = PerspectiveProjection();
	Body::mWtV = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Multyplyby the parents matrix
	mTransform = mat1 * mat2 * trans * rot   * sca;
}



/******************************************************************************
	\fn		Movement
	\brief	Checks the input and modifies the respective values
******************************************************************************/
void Gun::Movement() {

	//Reset the vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Angle to store how much does it rotate
	float angle = 0.0f;

	//If both are pressed at the same time do nothing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {}

	//if A is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {

		//increase the angle
		angle += 0.05f;
		mAngle += 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);

		//AmPPly it to the orientation
		mOrientation = rot * mOrientation;
	}

	//if D is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {

		//Decrese the angle
		angle -= 0.05f;
		mAngle -= 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);

		//AmPPly it to the orentation
		mOrientation = rot * mOrientation;
	}
}

/******************************************************************************
	\fn		Update
	\brief	Updates the vertices of the Gun
******************************************************************************/
void Gun::Update(Matrix4 mat1 , Matrix4 mat2, Matrix4 mat3) {
	
	//Calculate the mTransformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans1 = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Matrix4 trans2 = Translate(Vector4(0,0,20,0));
	Matrix4 trans3 = Translate(Vector4(0, 0, -20, 0));
	//Multyply by the parent matrix
	mTransform = mat1 * mat2 * mat3 * trans1* trans3 * rot  * trans2 * sca;


}

/******************************************************************          WHEEL        ****************************************************************************************/

/******************************************************************************
	\fn		Wheel Constructor
	\brief	Constructor for the Wheel class
******************************************************************************/
Wheel::Wheel(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat){

	Body::mScale = Scale_;
	Body::mPos = Pos;
	Body::mOrientation = Ore;
	Body::mAngle = Angle;
	Body::mAxis = Axis;

	//Load the data from the file
	Body::data.LoadDataFromFile();

	//Set the array of vertex to the data vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Calculate the mTransformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Body::mPP = PerspectiveProjection();
	Body::mWtV = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Multyply by the parent matrix
	Body::mTransform = mat * trans * rot * sca;

	//AmPPly the to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = mTransform * v[i];
		v[i] = mPP * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = mWtV * v[i];
	}
}

/******************************************************************************
	\fn		Movement
	\brief	Checks the input and modifies the respective values
******************************************************************************/
void Wheel::Movement() {

	//Reset the vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Angle to store how much does it rotate
	float angle = 0.0f;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		//increase the angle
		angle += 0.05f;
		mAngle += 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);
		
		//AmPPly it to the orentation
		mOrientation = rot * mOrientation;
	}
}
Cube::Cube(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis) {
	mScale = Scale_;
	mPos = Pos;
	mOrientation = Ore;
	mAngle = Angle;
	mAxis = mAxis;
}