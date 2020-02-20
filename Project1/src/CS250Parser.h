#pragma once
#include <stdio.h>
#include <vector>
#include "Point4.h"

class CS250Parser
{
	public:
		static void LoadDataFromFile();

		struct Face
		{
			int indices[3];
		};

		static float left;
		static float right;
		static float top;
		static float bottom;
		static float focal;
		static float nearPlane;
		static float farPlane;

		static std::vector<Point4> vertices;
		static std::vector<Face> faces;
		static std::vector<Point4> colors;
		static std::vector<Point4> textureCoords;

};