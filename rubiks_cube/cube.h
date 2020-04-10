#pragma once
#ifndef _CUBE_H_
#define _CUBE_H_
#include "smallcube.h"
#include <vector>
#include <string>

class Cube
{
public:
	void Draw()
	{
		cubiks[0][2][0].drawsmallcube(-1, -1, -1);
		cubiks[0][2][1].drawsmallcube(-0.49, -1, -1);
		cubiks[0][2][2].drawsmallcube(0.02, -1, -1);

		cubiks[0][1][0].drawsmallcube(-1, -0.47, -1);
		cubiks[0][1][1].drawsmallcube(-0.49, -0.47, -1);
		cubiks[0][1][2].drawsmallcube(0.02, -0.47, -1);

		cubiks[0][0][0].drawsmallcube(-1, 0.07, -1);
		cubiks[0][0][1].drawsmallcube(-0.49, 0.07, -1);
		cubiks[0][0][2].drawsmallcube(0.02, 0.07, -1);

		cubiks[1][0][0].drawsmallcube(-1,-1,-0.45);
		cubiks[1][1][0].drawsmallcube(-0.49, -1, -0.45);
		cubiks[1][2][0].drawsmallcube(0.02, -1, -0.45);

		cubiks[1][0][1].drawsmallcube(-1, -0.47, -0.45);
		cubiks[1][1][1].drawsmallcube(-0.49, -0.47, -0.45);
		cubiks[1][2][1].drawsmallcube(0.02, -0.47, -0.45);

		cubiks[1][0][2].drawsmallcube(-1, 0.07, -0.45);
		cubiks[1][1][2].drawsmallcube(-0.49, 0.07, -0.45);
		cubiks[1][2][2].drawsmallcube(0.02, 0.07, -0.45);

		cubiks[2][0][0].drawsmallcube(-1, -1, 0.02);
		cubiks[2][1][0].drawsmallcube(-0.49, -1, 0.02);
		cubiks[2][2][0].drawsmallcube(0.02, -1, 0.02);

		cubiks[2][0][1].drawsmallcube(-1, -0.47, 0.02);
		cubiks[2][1][1].drawsmallcube(-0.49, -0.47, 0.02);
		cubiks[2][2][1].drawsmallcube(0.02, -0.47, 0.02);

		cubiks[2][0][2].drawsmallcube(-1, 0.07, 0.02);
		cubiks[2][1][2].drawsmallcube(-0.49, 0.07, 0.02);
		cubiks[2][2][2].drawsmallcube(0.02, 0.07, 0.02);
	}
	SmallCube cubiks[3][3][3];
};

#endif // !_CUBE_H_

