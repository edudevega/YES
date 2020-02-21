#pragma once
#include "CS250Parser.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Matrix4.h"
#include "Vector4.h"
#include "Point4.h"
#include "Camera.h"
#include "Tank.h"
#include "Pipeline.h"

//Axis for the rotation
#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3

int Ceiling(float f);

void DrawMidpointLine(sf::Image &FrameBuffer, const sf::Vector2f & p1, const sf::Vector2f & p2, sf::Color color);

void DrawTriangleSolid(sf::Image &FrameBuffer, const sf::Vector2f & p0, const sf::Vector2f & p1, const sf::Vector2f & p2, sf::Color color);