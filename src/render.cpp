#include <vector>

#include "common.h"

using namespace std;

vector<Vector3> base_vs = {
    {0.25, 0.25, 0.25},   {0.25, -0.25, 0.25},
    {-0.25, 0.25, 0.25},  {-0.25, -0.25, 0.25},

    {0.25, 0.25, -0.25},  {0.25, -0.25, -0.25},
    {-0.25, 0.25, -0.25}, {-0.25, -0.25, -0.25},
};
vector<Vector3> vs;

vector<Point> fs = {{0, 1}, {1, 3}, {2, 3}, {0, 2}, {4, 5}, {5, 7},
                    {6, 7}, {4, 6}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};

Point screen(Vector2 v)
{
	// -1..1 -> 0..2 -> 0..1 -> 0..w
	return {cast(i32)((v.x + 1) / 2 * g.height) + (g.width - g.height) / 2,
	        cast(i32)((1 - v.y) / 2 * g.height)};
}

Vector2 project(Vector3 v)
{
	return {v.x / v.z, v.y / v.z};
}

Vector3 translate_z(Vector3 v, float dz)
{
	return {v.x, v.y, v.z + dz};
}

Vector3 rotate_xz(Vector3 v, float angle)
{
	return Vector3RotateByAxisAngle(v, {0, 1, 0}, angle);
}

void draw_point(Point p)
{
	DrawRectangle(p.x - 10, p.y - 10, 20, 20, FG);
}

void rotate_vs(Vector3 axis, float angle)
{
	for (usize i = 0; i < vs.size(); i++) {
		vs[i] = Vector3RotateByAxisAngle(vs[i], axis, angle);
	}
}

void rotate_vs_by_base(Vector3 axis, float angle)
{
	for (usize i = 0; i < vs.size(); i++) {
		vs[i] = Vector3RotateByAxisAngle(base_vs[i], axis, angle);
	}
}
void render()
{
	// for (auto i : vs) {
	//	draw_point(screen(project(translate_z(rotate_xz(i, angle), 1))));
	// }
	for (auto i : fs) {
		Vector3 a = vs[i.x];
		Vector3 b = vs[i.y];
		Point start = screen(project(translate_z(a, 1)));
		Point end = screen(project(translate_z(b, 1)));
		DrawLine(start.x, start.y, end.x, end.y, FG);
	}
}

void init_vs()
{
	for (auto i : base_vs) {
		vs.push_back(i);
	}
}
