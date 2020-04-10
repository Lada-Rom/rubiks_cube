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
	void rotatez() //�����
	{
		int tmp = color[0];
		color[0] = color[4];
		color[4] = color[5];
		color[5] = color[1];
		color[1] = tmp;
	}
	void mrotatez() //����
	{
		int tmp = color[0];
		color[0] = color[1];
		color[1] = color[5];
		color[5] = color[4];
		color[4] = tmp;
	}
	void rotatex() //������
	{
		int tmp = color[0];
		color[0] = color[3];
		color[3] = color[5];
		color[5] = color[2];
		color[2] = tmp;
	}
	void rotatey() //�����
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
		x,y,z, xs,y,z, xs,ys,z, x,ys,z, //�����
		x,y,z, x,ys,z,  x,ys,zs, x,y,zs, //����
		x,y,zs, x,ys,zs, xs,ys,zs, xs,y,zs, //���
		xs,y,zs, xs,ys,zs, xs,ys,z, xs,y,z, //�����
		x,ys,z, x,ys,zs, xs,ys,zs, xs,ys,z, //����
		x,y,z, xs,y,z, xs,y,zs, x,y,zs //���
		};
		GLfloat colors[] =
		{
		0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1, //����� �������
		1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0, //������� �������
		1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1, //����� �������
		0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0, //������� �������
		1, 1, 0,   1, 1, 0,   1, 1, 0,   1, 1, 0, //������ �������
		1, 0.5, 0, 1, 0.5, 0,   1, 0.5, 0,   1, 0.5, 0  //��������� �������
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
	int color[6]; //6 ������ � ���������� ������; // {����, ���, �������, �����, �����, ������}
	double size{ 0.5 }; // ������ �����
	float xc, yc, zc;
};

#endif // !__SMALLCUBE_H__

