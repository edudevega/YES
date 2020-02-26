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
	Body tank2(Vector4(30, 25, 80, 0), Vector4(0, 0, -20, 0), Vector4(0, 0, 1, 0), 0, Y_AXIS);
	Turret turret(Vector4(25, 15, 25, 0), Vector4(0, 20, 0, 0), Vector4(0, 0, 0, 0), 0, Y_AXIS, tank2.GetMatrix());
	Gun gun(Vector4(5,5, 40, 0), Vector4(0, 0, 12.5+20, 0), Vector4(0, 0, 1, 0), 0, X_AXIS, tank2.GetMatrix(),turret.GetMatrix());
	Wheel wheel1(Vector4(5,20, 20, 0), Vector4(17.5, -12.5, -25, 0), Vector4(0, 0, 0, 0), 0, X_AXIS, tank2.GetMatrix());
	Wheel wheel2(Vector4(5, 20, 20, 0), Vector4(-17.5, -12.5, -25, 0), Vector4(0, 0, 0, 0), 0, X_AXIS, tank2.GetMatrix());
	Wheel wheel3(Vector4(5, 20, 20, 0), Vector4(17.5, -12.5, 25, 0), Vector4(0, 0, 0, 0), 0, X_AXIS, tank2.GetMatrix());
	Wheel wheel4(Vector4(5, 20, 20, 0), Vector4(-17.5, -12.5, 25, 0), Vector4(0, 0, 0, 0), 0, X_AXIS, tank2.GetMatrix());

	
	//Create the Camera 
	Camera first;
	first.Update((tank2.GetMatrix()*turret.mPos), turret.mOrientation, camMode);
	Camera third;
	third.Update(tank2.mPos, tank2.mOrientation, camMode);
	Camera fixed;
	fixed.Update(Vector4 (0,0,0), Vector4(0,0,-1), camMode);

	tank2.Update(first.WorldToCam());
	turret.Update(first.WorldToCam(), tank2.GetMatrix());
	gun.Update(first.WorldToCam(), tank2.GetMatrix(), turret.GetMatrix());
	wheel1.Update(first.WorldToCam(), tank2.GetMatrix());
	wheel2.Update(first.WorldToCam(), tank2.GetMatrix());
	wheel3.Update(first.WorldToCam(), tank2.GetMatrix());
	wheel4.Update(first.WorldToCam(), tank2.GetMatrix());
	
	//Draw the the firts time
	tank2.Draw(image, mode);
	turret.Draw(image, mode);
	gun.Draw(image, mode);
	wheel1.Draw(image,mode);
	wheel2.Draw(image,mode);
	wheel3.Draw(image,mode);
	wheel4.Draw(image,mode);
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
		tank2.Movement();
		turret.Movement();
		gun.Movement();
		wheel1.Movement();
		wheel2.Movement();
		wheel3.Movement();
		wheel4.Movement();
		first.Movement();
		fixed.Movement();
		
	
		//Update all the parts with the new transformations
		third.Update(tank2.mPos, tank2.mOrientation,camMode);
		first.Update((tank2.GetMatrix()*turret.mPos), tank2.mOrientation, camMode);
		if (camMode == 0) {
			tank2.Update(first.WorldToCam());
			turret.Update(first.WorldToCam(), tank2.GetMatrix());
			gun.Update(first.WorldToCam(), tank2.GetMatrix(), turret.GetMatrix());
			wheel1.Update(first.WorldToCam(), tank2.GetMatrix());
			wheel2.Update(first.WorldToCam(), tank2.GetMatrix());
			wheel3.Update(first.WorldToCam(), tank2.GetMatrix());
			wheel4.Update(first.WorldToCam(), tank2.GetMatrix());
		
			for (int i = 0 ; i < 25; i++) {
				cubes[i].Movement();
				cubes[i].Update(first.WorldToCam());
					

			}
			
		}
		else if (camMode == 1) {
			tank2.Update(third.WorldToCam());
			turret.Update(third.WorldToCam(), tank2.GetMatrix());
			gun.Update(third.WorldToCam(), tank2.GetMatrix(), turret.GetMatrix());
			wheel1.Update(third.WorldToCam(), tank2.GetMatrix());
			wheel2.Update(third.WorldToCam(), tank2.GetMatrix());
			wheel3.Update(third.WorldToCam(), tank2.GetMatrix());
			wheel4.Update(third.WorldToCam(), tank2.GetMatrix());	
		
			for (int i = 0; i < 25; i++) {
				cubes[i].Movement();
				cubes[i].Update(third.WorldToCam());

			}
		
		}
		else if (camMode == 2) {
			tank2.Update(fixed.WorldToCam());
			turret.Update(fixed.WorldToCam(), tank2.GetMatrix());
			gun.Update(fixed.WorldToCam(), tank2.GetMatrix(), turret.GetMatrix());
			wheel1.Update(fixed.WorldToCam(), tank2.GetMatrix());
			wheel2.Update(fixed.WorldToCam(), tank2.GetMatrix());
			wheel3.Update(fixed.WorldToCam(), tank2.GetMatrix());
			wheel4.Update(fixed.WorldToCam(), tank2.GetMatrix());
		
		
			for (int i = 0; i < 25; i++) {
				cubes[i].Movement();
				cubes[i].Update(fixed.WorldToCam());
			}
		}

		for (int i = 0; i < 25; i++) {
			cubes[i].Draw(image, mode);
		}

		tank2.Draw(image, mode);
		turret.Draw(image, mode);
		gun.Draw(image, mode);
		wheel1.Draw(image, mode);
		wheel2.Draw(image, mode);
		wheel3.Draw(image, mode);
		wheel4.Draw(image, mode);
		
		//SFML Stuff
		window.clear();
		texture.update(image);
		sprite.setTexture(texture);
		window.draw(sprite);
		window.display();
		
		
	}

	return 0;
}