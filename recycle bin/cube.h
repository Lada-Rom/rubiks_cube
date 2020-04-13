#pragma once
#ifndef _CUBE_H_
#define _CUBE_H_
#include "smallcube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

class Cube {

public:
	Cube() {
		cubiks[0][2][0].setposition(-1, -1, -1);
		cubiks[0][2][1].setposition(-0.49f, -1.f, -1.f);
		cubiks[0][2][2].setposition(0.02, -1, -1);

		cubiks[0][1][0].setposition(-1, -0.47, -1);
		cubiks[0][1][1].setposition(-0.49, -0.47, -1);
		cubiks[0][1][2].setposition(0.02, -0.47, -1);

		cubiks[0][0][0].setposition(-1, 0.07, -1);
		cubiks[0][0][1].setposition(-0.49, 0.07, -1);
		cubiks[0][0][2].setposition(0.02, 0.07, -1);
		//---------------нижний---------------------


		//--------------середина--------------------
		cubiks[1][0][0].setposition(-1, -1, -0.45);
		cubiks[1][1][0].setposition(-0.49, -1, -0.45);
		cubiks[1][2][0].setposition(0.02, -1, -0.45);

		cubiks[1][0][1].setposition(-1, -0.47, -0.45);
		cubiks[1][1][1].setposition(-0.49, -0.47, -0.45);
		cubiks[1][2][1].setposition(0.02, -0.47, -0.45);

		cubiks[1][0][2].setposition(-1, 0.07, -0.45);
		cubiks[1][1][2].setposition(-0.49, 0.07, -0.45);
		cubiks[1][2][2].setposition(0.02, 0.07, -0.45);
		//----------------середина----------------------------


		//------------------верх-------------------------------
		cubiks[2][0][0].setposition(-1, -1, 0.08);
		cubiks[2][1][0].setposition(-0.49, -1, 0.08);
		cubiks[2][2][0].setposition(0.02, -1, 0.08);

		cubiks[2][0][1].setposition(-1, -0.47, 0.08);
		cubiks[2][1][1].setposition(-0.49, -0.47, 0.08);
		cubiks[2][2][1].setposition(0.02, -0.47, 0.08);

		cubiks[2][0][2].setposition(-1, 0.07, 0.08);
		cubiks[2][1][2].setposition(-0.49, 0.07, 0.08);
		cubiks[2][2][2].setposition(0.02, 0.07, 0.08);
	}

	void updatebelt() {
		if (!rotationstatus) {

			//смотрим по координатам к какой плоскости принадлежит маленький кубик
            //и на основе этого даем ему номер пояса
            //не будет работать во время ротации потому что координаты меняются
			for (int i(0); i < 3; i++) {
				for (int j(0); j < 3; j++) {
					for (int k(0); k < 3; k++) {

						if (( -1.1f < cubiks[i][j][k].posz()
                            && cubiks[i][j][k].posz() < -0.9f)
                            && (-1.1f < cubiks[i][j][k].posy()
                            && cubiks[i][j][k].posy() < 0.1f )
                            && cubiks[i][j][k].getvbelt() != 1) {
							cubiks[i][j][k].setverticalbelt(1);
						}

						if (( -0.46f < cubiks[i][j][k].posz()
                            && cubiks[i][j][k].posz() < -0.44f)
                            && (-1.1f < cubiks[i][j][k].posy()
                                && cubiks[i][j][k].posy() < 0.1f)
                            && cubiks[i][j][k].getvbelt() != 2) {
							cubiks[i][j][k].setverticalbelt(2);
						}

						if ((0.06  < cubiks[i][j][k].posz()
                            && cubiks[i][j][k].posz() < 0.1)
                            && (-1.1f <= cubiks[i][j][k].posy()
                                && cubiks[i][j][k].posy() < 0.1f)
                            && cubiks[i][j][k].getvbelt() != 3) {
							cubiks[i][j][k].setverticalbelt(3);
						}

						if ((-1.1 < cubiks[i][j][k].posy()
                            && cubiks[i][j][k].posy() < -0.9f)
                            && (-1.1f < cubiks[i][j][k].posz()
                                && cubiks[i][j][k].posz() < 0.1f)
                            && cubiks[i][j][k].gethbelt() != 4) {
							cubiks[i][j][k].sethorizontalbelt(4);
						}

						if (( -0.49f < cubiks[i][j][k].posy()
                            && cubiks[i][j][k].posy() < -0.45f)
                            && (-1.1f < cubiks[i][j][k].posz()
                            && cubiks[i][j][k].posz() < 0.1f)
                            && cubiks[i][j][k].gethbelt() != 5) {
							cubiks[i][j][k].sethorizontalbelt(5);
						}

						if ((0.05f < cubiks[i][j][k].posy()
                            && cubiks[i][j][k].posy() < 0.1f)
                            && (-1.1f < cubiks[i][j][k].posz()
                                && cubiks[i][j][k].posz() < 0.1f)
                            && cubiks[i][j][k].gethbelt() != 6) {
							cubiks[i][j][k].sethorizontalbelt(6);
						}
					}
				}
			}
		}
	}

	void Rotatebelt(int n, int angle) {
		rotx = glm::rotate(rotx, 90.f, glm::vec3(1.0, 0.0, 0.0));
		roty = glm::rotate(rotx, angle * 90.f, glm::vec3(0.0, 1.0, 0.0));
		rotz = glm::rotate(rotx, angle * (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0, 1.0, 1.0));
		rotationstatus = true;

		if (n == 1) {
			for (int i(0); i < 3; i++) {
				for (int j(0); j < 3; j++) {
					for (int k(0); k < 3; k++) {
						if (cubiks[i][j][k].getvbelt() == 1) {
							roty = glm::rotate(roty, glm::radians(angle*90.f), glm::vec3(0.0, 1.0, 0.0));
							glm::vec4 t(cubiks[i][j][k].posx(), cubiks[i][j][k].posy(), cubiks[i][j][k].posz(),1);
							t = roty * t;
							cubiks[i][j][k].setposition(t.x,t.y,t.z);
						}
					}
				}
			}
		}
		rotationstatus = false;
	}

	void Draw() {
		//-----------------фасад
		cubiks[0][2][0].drawsmallcube(cubiks[0][2][0].posx(), cubiks[0][2][0].posy(), cubiks[0][2][0].posz());
		cubiks[0][2][1].drawsmallcube(cubiks[0][2][1].posx(), cubiks[0][2][1].posy(), cubiks[0][2][1].posz());
		cubiks[0][2][2].drawsmallcube(cubiks[0][2][2].posx(), cubiks[0][2][2].posy(), cubiks[0][2][2].posz());

		cubiks[0][1][0].drawsmallcube(cubiks[0][1][0].posx(), cubiks[0][1][0].posy(), cubiks[0][1][0].posz());
		cubiks[0][1][1].drawsmallcube(cubiks[0][1][1].posx(), cubiks[0][1][1].posy(), cubiks[0][1][1].posz());
		cubiks[0][1][2].drawsmallcube(cubiks[0][1][2].posx(), cubiks[0][1][2].posy(), cubiks[0][1][2].posz());

		cubiks[0][0][0].drawsmallcube(cubiks[0][0][0].posx(), cubiks[0][0][0].posy(), cubiks[0][0][0].posz());
		cubiks[0][0][1].drawsmallcube(cubiks[0][0][1].posx(), cubiks[0][0][1].posy(), cubiks[0][0][1].posz());
		cubiks[0][0][2].drawsmallcube(cubiks[0][0][2].posx(), cubiks[0][0][2].posy(), cubiks[0][0][2].posz());
		//фасад

		//--------------середина--------------------
		cubiks[1][0][0].drawsmallcube(cubiks[1][0][0].posx(), cubiks[1][0][0].posy(), cubiks[1][0][0].posz());
		cubiks[1][1][0].drawsmallcube(cubiks[1][1][0].posx(), cubiks[1][1][0].posy(), cubiks[1][1][0].posz());
		cubiks[1][2][0].drawsmallcube(cubiks[1][2][0].posx(), cubiks[1][2][0].posy(), cubiks[1][2][0].posz());

		cubiks[1][0][1].drawsmallcube(cubiks[1][0][1].posx(), cubiks[1][0][1].posy(), cubiks[1][0][1].posz());
		cubiks[1][1][1].drawsmallcube(cubiks[1][1][1].posx(), cubiks[1][1][1].posy(), cubiks[1][1][1].posz());
		cubiks[1][2][1].drawsmallcube(cubiks[1][2][1].posx(), cubiks[1][2][1].posy(), cubiks[1][2][1].posz());

		cubiks[1][0][2].drawsmallcube(cubiks[1][0][2].posx(), cubiks[1][0][2].posy(), cubiks[1][0][2].posz());
		cubiks[1][1][2].drawsmallcube(cubiks[1][1][2].posx(), cubiks[1][1][2].posy(), cubiks[1][1][2].posz());
		cubiks[1][2][2].drawsmallcube(cubiks[1][2][2].posx(), cubiks[1][2][2].posy(), cubiks[1][2][2].posz());
		//----------------середина----------------------------

		//--------------------зад------------------------
		cubiks[2][0][0].drawsmallcube(cubiks[2][0][0].posx(), cubiks[2][0][0].posy(), cubiks[2][0][0].posz());
		cubiks[2][1][0].drawsmallcube(cubiks[2][1][0].posx(), cubiks[2][1][0].posy(), cubiks[2][1][0].posz());
		cubiks[2][2][0].drawsmallcube(cubiks[2][2][0].posx(), cubiks[2][2][0].posy(), cubiks[2][2][0].posz());

		cubiks[2][0][1].drawsmallcube(cubiks[2][0][1].posx(), cubiks[2][0][1].posy(), cubiks[2][0][1].posz());
		cubiks[2][1][1].drawsmallcube(cubiks[2][1][1].posx(), cubiks[2][1][1].posy(), cubiks[2][1][1].posz());
		cubiks[2][2][1].drawsmallcube(cubiks[2][2][1].posx(), cubiks[2][2][1].posy(), cubiks[2][2][1].posz());

		cubiks[2][0][2].drawsmallcube(cubiks[2][0][2].posx(), cubiks[2][0][2].posy(), cubiks[2][0][2].posz());
		cubiks[2][1][2].drawsmallcube(cubiks[2][1][2].posx(), cubiks[2][1][2].posy(), cubiks[2][1][2].posz());
		cubiks[2][2][2].drawsmallcube(cubiks[2][2][2].posx(), cubiks[2][2][2].posy(), cubiks[2][2][2].posz());
		//------------------зад--------------------------------
	}

private:
	SmallCube cubiks[3][3][3];
	glm::mat4 rotx = glm::mat4(1.0);
	glm::mat4 rotz = glm::mat4(1.0);
	glm::mat4 roty = glm::mat4(1.0);
	bool rotationstatus;
};

#endif // !_CUBE_H_
