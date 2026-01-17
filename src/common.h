#pragma once

#include "base.h"
#include "raylib.h"
#include "raymath.h"

#define BG SKYBLUE
#define FG BLACK
#define cast(tp) static_cast<tp>

struct Global {
	i32 width;
	i32 height;
};
extern Global g;

struct Point {
	int x;
	int y;
};

void rotate_vs(Vector3 axis, float angle);
void render(void);
void init_vs();
