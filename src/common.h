#pragma once

#include "base.h"
#include "raylib.h"
#include "raymath.h"

#define BG SKYBLUE
#define FG BLACK
#define cast(tp) static_cast<tp>

enum {
	RUF,
	RUB,
	RDF,
	RDB,
	LUF,
	LUB,
	LDF,
	LDB,
};

enum { UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BR, BL };

struct OrbitCamera {
	float radius;
	float yaw;
	float pitch;
};

struct Move {
	u8 cp[8];  // cubie positions
	u8 co[8];  // cubie orientations (0,1,2)
	u8 ep[12]; // edge positions
	u8 eo[12]; // edge orientations (0,1)
};

struct RCube {
	u8 cp[8];  // cubie positions
	u8 co[8];  // cubie orientations (0,1,2)
	u8 ep[12]; // edge positions
	u8 eo[12]; // edge orientations (0,1)

	RCube()
	{
		for (usize i = 0; i < 8; i++) {
			cp[i] = i;
			co[i] = 0;
		}
		for (usize i = 0; i < 12; i++) {
			ep[i] = i;
			eo[i] = 0;
		}
	}
};

struct Global {
	i32 width;
	i32 height;
	Model model;
	Camera3D camera;
	OrbitCamera ocam;
	RCube rcube;
};
extern Global g;

struct Point {
	int x;
	int y;
};

void render(void);
void init_graphics();
