#pragma once
#ifndef __SMALLCUBE_H__
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include<cstring>
#include <glm\fwd.hpp>

class SmallCube
{
public:

	SmallCube()
	{
		memset(color,0,sizeof(color));
	}
	void rotatez() //вверх
	{
		int tmp = color[0];
		color[0] = color[4];
		color[4] = color[5];
		color[5] = color[1];
		color[1] = tmp;
	}
	void mrotatez() //вниз
	{
		int tmp = color[0];
		color[0] = color[1];
		color[1] = color[5];
		color[5] = color[4];
		color[4] = tmp;
	}
	void rotatex() //вправо
	{
		int tmp = color[0];
		color[0] = color[3];
		color[3] = color[5];
		color[5] = color[2];
		color[2] = tmp;
	}
	void rotatey() //влево
	{
		int tmp = color[0];
		color[0] = color[2];
		color[2] = color[5];
		color[5] = color[3];
		color[3] = tmp;
	}
	void drawsmallcube(float x, float y, float z)
	{
		xc = x;
		yc = y;
		zc = z;
		float zs,xs, ys;
		zs = z + size;
		xs = x + size;
		ys = y + size;
		GLfloat vertices[] =
		{
		x,y,z, xs,y,z, xs,ys,z, x,ys,z, //перед
		x,y,z, x,ys,z,  x,ys,zs, x,y,zs, //лево
		x,y,zs, x,ys,zs, xs,ys,zs, xs,y,zs, //зад
		xs,y,zs, xs,ys,zs, xs,ys,z, xs,y,z, //право
		x,ys,z, x,ys,zs, xs,ys,zs, xs,ys,z, //верх
		x,y,z, xs,y,z, xs,y,zs, x,y,zs //низ
		};
		GLfloat colors[] =
		{
		0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1, //синяя вершина
		1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0, //красная вершина
		1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1, //белая вершина
		0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0, //зеленая вершина
		1, 1, 0,   1, 1, 0,   1, 1, 0,   1, 1, 0, //желтая вершина
		1, 0.5, 0, 1, 0.5, 0,   1, 0.5, 0,   1, 0.5, 0  //оранжевая вершина
		};
		static float alpha = 0;
		//attempt to rotate cube
		glRotatef(alpha, 0, 1, 0);

		/* We have a color array and a vertex array */
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(3, GL_FLOAT, 0, colors);

		/* Send data : 24 vertices */
		glDrawArrays(GL_QUADS, 0, 24);

		/* Cleanup states */
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		//alpha += 0.5;
	}
	float posx()
	{
		return xc;
	}
	float posy()
	{
		return yc;
	}
	float posz()
	{
		return zc;
	}
private:
	                                                 //2     5       1      6      4      3
	int color[6]; //6 граней у маленького кубика; // {верх, низ, спереди, сзади, слева, справа}
	double size{ 0.5 }; // размер ребра
	float xc, yc, zc;
};

#endif // !__SMALLCUBE_H__

