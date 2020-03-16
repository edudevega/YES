/*!
*	\file		main.cpp
*	\brief		main for the tank project
*	\author		Eduardo de Vega - eduardo.devega@digipen.edu
*	\date		11/02/2020
*
*/
#pragma once
#include "Rasterizer.h"
#include <iostream>

int main()
{
	
	//Create the Window to show the tank
	sf::RenderWindow window(sf::VideoMode(800, 600), "CS250");
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	texture.create(800, 600);
	image.create(800, 600, sf::Color::White);

	//To load the data from the File
	CS250Parser data;
	data.LoadDataFromFile();
	
	//Select the darwing mode
	bool mode = 0;
	int camMode = 0;
	int count = 0;
	Cube cubes[25];
	for (int i = 0,r  = -100; i < 5 ;i++ ,r+=50) {
		for (int j = 0, w = -100; j < 5; j++, w += 50) {
			cubes[count] = Cube(Vector4(10, 10, 10, 0), Vector4(-r, 0, -w, 0), Vector4(0, 0, 1, 0), 0, Y_AXIS);
			count++;
		}
	}
	
	
	//Create all the parts of the tank
	Body body(Vector4(15, 12.5, 40, 0), Vector4(0, 0, -50, 0), Vector4(0, 0, 1, 0), 0, Y_AXIS);
	Turret tail(Vector4(5, 7.5, 10, 0), Vector4(0, 10, -15, 0), Vector4(0, 0, 1, 0), 0, Y_AXIS, body.GetMatrix());
	Turret leftwing(Vector4(20, 5, 10, 0), Vector4(-17.5, 0, -0, 0), Vector4(0, 0, 1, 0), 0, Y_AXIS, body.GetMatrix());
	Turret rightwing(Vector4(20, 5, 10, 0), Vector4(17.5, 0, -0, 0), Vector4(0, 0, 1, 0), 0, Y_AXIS, body.GetMatrix());
	
	//Create the Camera 
	Camera first;
	first.Update(Vector4(body.mPos.x, body.mPos.y + body.mScale.y/2+ body.mScale.y / 2, body.mPos.z) , Rotate(body.mAngle + body.mAngle, Y_AXIS) * Vector4(0, 0, 1, 0), camMode);
	Camera third;
	third.Update(body.mPos, body.mOrientation, camMode);
	Camera fixed;
	fixed.Update(Vector4 (0,0,0), Vector4(0,0,-1), camMode);

	body.Update(first.WorldToCam());
	tail.Update(first.WorldToCam(), body.GetMatrix());
	rightwing.Update(first.WorldToCam(), body.GetMatrix());
	leftwing.Update(first.WorldToCam(), body.GetMatrix());
	
	//Draw the the firts time
	body.Draw(image, mode);
	tail.Draw(image, mode);
	rightwing.Draw(image, mode);
	leftwing.Draw(image,mode);

	for (int i = 0; i < 25; i++) {
		cubes[i].Movement();
		cubes[i].Update(first.WorldToCam());


	}
	//Loop
	while (window.isOpen())
	{
		
		//To change the drawing method
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			mode = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			mode = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			camMode = 0;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			camMode = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			camMode = 2;

		//For closing the window
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}
		//If escape exit
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

		//Refresh the frame
		image.create(800, 600, sf::Color::White);
		
		//Get the input for the user for all the parts
		third.Movement();
		first.Movement();
		fixed.Movement();
		body.Movement();
		tail.Movement();
		rightwing.Movement();
		leftwing.Movement();
		
		
	
		//Update all the parts with the new transformations
		fixed.Update(Vector4(0, 0, 0), Vector4(0, 0, -1), camMode);
		third.Update(body.mPos, body.mOrientation,camMode);
		first.Update((body.mPos + body.mPos), Rotate(body.mAngle + body.mAngle, Y_AXIS) * Vector4(0, 0, 1, 0), camMode);
		if (camMode == 0) {
			body.Update(first.WorldToCam());
			tail.Update(first.WorldToCam(), body.GetMatrix());
			rightwing.Update(first.WorldToCam(), body.GetMatrix());
			leftwing.Update(first.WorldToCam(), body.GetMatrix());
		
			for (int i = 0 ; i < 25; i++) {
				cubes[i].Movement();
				cubes[i].Update(first.WorldToCam());
					

			}
			
		}
		else if (camMode == 1) {
			body.Update(third.WorldToCam());
			tail.Update(third.WorldToCam(), body.GetMatrix());
			rightwing.Update(third.WorldToCam(), body.GetMatrix());
			leftwing.Update(third.WorldToCam(), body.GetMatrix());

		
			for (int i = 0; i < 25; i++) {
				cubes[i].Movement();
				cubes[i].Update(third.WorldToCam());

			}
		
		}
		else if (camMode == 2) {
			body.Update(fixed.WorldToCam());
			tail.Update(fixed.WorldToCam(), body.GetMatrix());
			rightwing.Update(fixed.WorldToCam(), body.GetMatrix());
			leftwing.Update(fixed.WorldToCam(), body.GetMatrix());
		
		
			for (int i = 0; i < 25; i++) {
				cubes[i].Movement();
				cubes[i].Update(fixed.WorldToCam());
			}
		}

		for (int i = 0; i < 25; i++) {
			cubes[i].Draw(image, mode);
		}

		//Draw the the firts time
		body.Draw(image, mode);
		tail.Draw(image, mode);
		rightwing.Draw(image, mode);
		leftwing.Draw(image, mode);
		
		//SFML Stuff
		window.clear();
		texture.update(image);
		sprite.setTexture(texture);
		window.draw(sprite);
		window.display();
		
		
	}

	return 0;
}