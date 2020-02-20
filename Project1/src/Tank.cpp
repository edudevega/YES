/*!
*	\file		Tank.cpp
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

	//Calculate the transformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Matrix4 transform = trans * rot * sca;
	Matrix4 pp = PerspectiveProjection();
	Matrix4 wtp = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Apply the to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = transform * v[i];
		v[i] = pp * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = wtp * v[i];
	}
}

/******************************************************************************
	\fn		Update
	\brief	Updates the vertices of the Body
******************************************************************************/
void Body::Update() {
	
	//Calculate the transformations
	Matrix4 rot = Rotate(mAngle, mAxis);;
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Matrix4 transform = trans * rot * sca; 
	Matrix4 pp = PerspectiveProjection();
	Matrix4 wtp = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Apply them to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = transform * v[i];
		v[i] = pp * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = wtp * v[i];
	}
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

		//Apply it to the orientation
		mOrientation =  rot * mOrientation;
	}

	//if D is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		//Decrese the angle
		angle -= 0.05f;
		mAngle -= 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);
		
		//Apply it to the orentation
		mOrientation = rot * mOrientation;
	}
}

/******************************************************************************
	\fn		Draw
	\brief	Draws the Body in the method wanted
******************************************************************************/
void Body::Draw(sf::Image &image, bool mode) {
	
	//For looping on the colors
	int i = 0; 

	//To draw all the vertices
	for (auto it = data.faces.begin(); it != data.faces.end(); ++it, i++) {
		
		//if mode is solid
		if(mode == 0)
		DrawTriangleSolid(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y),
			sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y),
			sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y),
			sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));

		//if mode is lines
		else{
			DrawMidpointLine(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y), sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));
			DrawMidpointLine(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y), sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));
			DrawMidpointLine(image, sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y), sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));

			
		}
			
	}
}

/******************************************************************************
	\fn		GetMatrix
	\brief	returns the matrix for child transformations
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
Turret::Turret(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis,Matrix4 mat) : mScale(Scale_), mPos(Pos), mAxis(Axis), mAngle(Angle), mOrientation(Ore) {
	
	//Load the data from the file
	data.LoadDataFromFile();

	//Set the array of vertex to the data vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Calculate the transformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Matrix4 pp = PerspectiveProjection();
	Matrix4 wtp = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Multyply by the parent matrix
	Matrix4 transform = mat * trans * rot * sca;

	//Apply the to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = transform * v[i];
		v[i] = pp * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = wtp * v[i];
	}
}

/******************************************************************************
	\fn		Draw
	\brief	Draws the turret in the method wanted
******************************************************************************/
void Turret::Draw(sf::Image &image , bool mode) {

	//For looping on the colors
	int i = 0;

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

/******************************************************************************
	\fn		GetMatrix
	\brief	returns the matrix for child transformations
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

		//Apply it to the orientation
		mOrientation = rot * mOrientation;
	}

	//if Q is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

		//Decrese the angle
		angle -= 0.05f;
		mAngle -= 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);

		//Apply it to the orentation
		mOrientation = rot * mOrientation;
	}
}

/******************************************************************************
	\fn		Update
	\brief	Updates the vertices of the turret
******************************************************************************/
void Turret::Update(Matrix4 mat) {
	
	//Calculate the transformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Matrix4 pp = PerspectiveProjection();
	Matrix4 wtp = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Multyply by the parents matrix
	Matrix4 transform = mat  * trans * rot * sca;

	//Apply the to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = transform * v[i];
		v[i] = pp * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = wtp * v[i];
	}
}

/******************************************************************          GUN        ********************************************************************************************/

/******************************************************************************
	\fn		Gun Constructor
	\brief	Constructor for the Gun class
******************************************************************************/
Gun::Gun(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat1, Matrix4 mat2) : mScale(Scale_), mPos(Pos), mAxis(Axis), mAngle(Angle), mOrientation(Ore) {
	
	//Load the data from the file
	data.LoadDataFromFile();

	//Set the array of vertex to the data vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Calculate the transformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Matrix4 pp = PerspectiveProjection();
	Matrix4 wtp = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Multyply by the parents matrix
	Matrix4 transform = mat1 * mat2 * trans * rot   * sca;

	//Apply the to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = transform * v[i];
		v[i] = pp * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = wtp * v[i];
	}
}

/******************************************************************************
	\fn		Draw
	\brief	Draws the Gun in the method wanted
******************************************************************************/
void Gun::Draw(sf::Image &image, bool mode) {

	//For looping on the colors
	int i = 0;

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

		//Apply it to the orientation
		mOrientation = rot * mOrientation;
	}

	//if D is pressed rotate the body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {

		//Decrese the angle
		angle -= 0.05f;
		mAngle -= 0.05f;

		//Calculate the rotation matrix by that angle
		Matrix4 rot = Rotate(angle, mAxis);

		//Apply it to the orentation
		mOrientation = rot * mOrientation;
	}
}

/******************************************************************************
	\fn		Update
	\brief	Updates the vertices of the Gun
******************************************************************************/
void Gun::Update(Matrix4 mat1 , Matrix4 mat2) {
	
	//Calculate the transformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans1 = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Matrix4 pp = PerspectiveProjection();
	Matrix4 wtp = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);
	Matrix4 trans2 = Translate(Vector4(0,0,20,0));
	Matrix4 trans3 = Translate(Vector4(0, 0, -20, 0));
	//Multyply by the parent matrix
	Matrix4 transform = mat1 * mat2 * trans1* trans3 * rot  * trans2 * sca;

	//Apply the to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = transform * v[i];
		v[i] = pp * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = wtp * v[i];
	}

}

/******************************************************************          WHEEL        ****************************************************************************************/

/******************************************************************************
	\fn		Wheel Constructor
	\brief	Constructor for the Wheel class
******************************************************************************/
Wheel::Wheel(Vector4 Scale_, Vector4 Pos, Vector4 Ore, float Angle, int Axis, Matrix4 mat) : mScale(Scale_), mPos(Pos), mAxis(Axis), mAngle(Angle), mOrientation(Ore) {
	
	//Load the data from the file
	data.LoadDataFromFile();

	//Set the array of vertex to the data vertices
	for (int i = 0; i < 8; i++) {
		v[i].x = data.vertices[i].x;
		v[i].y = data.vertices[i].y;
		v[i].z = data.vertices[i].z;
		v[i].w = data.vertices[i].w;
	}

	//Calculate the transformation matrices
	Matrix4 rot = Rotate(mAngle, mAxis);
	Matrix4 trans = Translate(mPos);
	Matrix4 sca = Scale(mScale);
	Matrix4 pp = PerspectiveProjection();
	Matrix4 wtp = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);

	//Multyply by the parent matrix
	Matrix4 transform = mat * trans * rot * sca;

	//Apply the to the vertices
	for (int i = 0; i < 8; i++) {
		v[i] = transform * v[i];
		v[i] = pp * v[i];
		v[i] = v[i] / v[i].w;
		v[i] = wtp * v[i];
	}
}
//
///******************************************************************************
//	\fn		Draw
//	\brief	Draws the whee; in the method wanted
//******************************************************************************/
//void Wheel::Draw(sf::Image &image, bool mode) {
//
//	//For looping on the colors
//	int i = 0;
//
//	//To draw all the vertices
//	for (auto it = data.faces.begin(); it != data.faces.end(); ++it, i++) {
//
//		//if mode is solid
//		if (mode == 0)
//			DrawTriangleSolid(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y),
//				sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y),
//				sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y),
//				sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));
//
//		//if mode is lines
//		else {
//			DrawMidpointLine(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y), sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));
//			DrawMidpointLine(image, sf::Vector2f(v[it->indices[0]].x, v[it->indices[0]].y), sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));
//			DrawMidpointLine(image, sf::Vector2f(v[it->indices[1]].x, v[it->indices[1]].y), sf::Vector2f(v[it->indices[2]].x, v[it->indices[2]].y), sf::Color((int)data.colors[i].x, (int)data.colors[i].y, (int)data.colors[i].z, 255));
//		}
//
//	}
//}

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
		
		//Apply it to the orentation
		mOrientation = rot * mOrientation;
	}

	
}
//
///******************************************************************************
//	\fn		Update
//	\brief	Updates the vertices of the Wheel
//******************************************************************************/
//void Wheel::Update(Matrix4 mat) {
//
//	//Calculate the transformation matrices
//	Matrix4 rot = Rotate(mAngle, mAxis);
//	Matrix4 trans = Translate(mPos);
//	Matrix4 sca = Scale(mScale);
//	Matrix4 pp = PerspectiveProjection();
//	Matrix4 wtp = WinToVP(-CS250Parser::bottom + CS250Parser::top, -CS250Parser::left + CS250Parser::right, 600, 800);
//
//	//Multyply by the parent matrix
//	Matrix4 transform = mat * trans * rot * sca;
//
//	//Apply the to the vertices
//	for (int i = 0; i < 8; i++) {
//		v[i] = transform * v[i];
//		v[i] = pp * v[i];
//		v[i] = v[i] / v[i].w;
//		v[i] = wtp * v[i];
//	}
//
//}