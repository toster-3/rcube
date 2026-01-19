#include <utility>
#include <vector>

#include "base.h"
#include "common.h"
#include "raylib.h"
#include "raymath.h"

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

float vertices[] = {
    0.25f,  0.25f,  0.25f,  0.25f,  -0.25f, 0.25f,
    -0.25f, -0.25f, 0.25f,  -0.25f, 0.25f,  0.25f,

    0.25f,  0.25f,  -0.25f, 0.25f,  -0.25f, -0.25f,
    -0.25f, -0.25f, -0.25f, -0.25f, 0.25f,  -0.25f,
};

unsigned short indices[] = {
    0, 1, 2, 2, 3, 0, // front
    4, 7, 6, 6, 5, 4, // back
    0, 4, 5, 5, 1, 0, // right
    3, 2, 6, 6, 7, 3, // left
    3, 7, 4, 4, 0, 3, // top
    1, 5, 6, 6, 2, 1  // bottom
};

Vector3 corner_pos[8] = {
    {+1, +1, -1}, // FUR
    {+1, +1, +1}, // FUL
    {+1, -1, -1}, // FDR
    {+1, -1, +1}, // FDL
    {-1, +1, -1}, // BUR
    {-1, +1, +1}, // BUL
    {-1, -1, -1}, // BDR
    {-1, -1, +1}, // BDL
};

Vector3 edge_pos[12] = {
    {1, 1, 0},   // UR
    {0, 1, -1},  // UF
    {-1, 1, 0},  // UL
    {0, 1, 1},   // UB
    {1, -1, 0},  // DR
    {0, -1, -1}, // DF
    {-1, -1, 0}, // DL
    {0, -1, 1},  // DB
    {1, 0, -1},  // FR
    {-1, 0, -1}, // FL
    {1, 0, 1},   // BR
    {-1, 0, 1},  // BL
};

Vector3 center_pos[6] = {
    {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1},
};

Camera3D make_camera(OrbitCamera o)
{
	Camera3D cam = {};
	cam.fovy = 45.0;
	cam.target = {0, 0, 0};
	cam.up = {0, 1, 0};
	cam.projection = CAMERA_PERSPECTIVE;
	// Start with camera at (radius, 0, 0) relative to target
	Vector3 position = {o.radius, 0.0f, 0.0f};

	// Rotate by pitch around Z axis
	position = Vector3RotateByAxisAngle(position, {0.0f, 0.0f, 1.0f}, o.pitch);

	// Rotate by yaw around Y axis
	position = Vector3RotateByAxisAngle(position, {0.0f, 1.0f, 0.0f}, o.yaw);

	// Add target position to get world position
	cam.position = position;

	return cam;
}

#define U_COLOR YELLOW
#define D_COLOR WHITE
#define F_COLOR ORANGE
#define B_COLOR RED
#define R_COLOR BLUE
#define L_COLOR GREEN

const float size = 1.f;
float angle = 0;

// {0, 1, 0} {0, 1, 0}
void draw_cubie(Vector3 movement, Vector3 coloring)
{
	Color possible[3] = {BLACK, BLACK, BLACK};
	// color resolution  U     F      R       D      B      L
	Color colors[6] = {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};
	if (coloring.x == 1) {
		possible[0] = F_COLOR;
	} else if (coloring.x == -1) {
		possible[0] = B_COLOR;
	}
	if (coloring.y == 1) {
		possible[1] = U_COLOR;
	} else if (coloring.y == -1) {
		possible[1] = D_COLOR;
	}
	if (coloring.z == -1) {
		possible[2] = R_COLOR;
	} else if (coloring.z == 1) {
		possible[2] = L_COLOR;
	}

	if (movement.x == 1) {
		colors[1] = possible[0];
	} else if (movement.x == -1) {
		colors[4] = possible[0];
	}
	if (movement.y == 1) {
		colors[0] = possible[1];
	} else if (movement.y == -1) {
		colors[3] = possible[1];
	}
	if (movement.z == -1) {
		colors[2] = possible[2];
	} else if (movement.z == 1) {
		colors[5] = possible[2];
	}

	// actual drawing
	Vector3 startpos = {0.5, 0.5, 0.5};
	Vector3 pos = Vector3Add(startpos, movement);
	DrawTriangle3D(pos, Vector3Add(pos, {0, 0, -1}),
	               Vector3Add(pos, {-1, 0, 0}), colors[0]);
	DrawTriangle3D(Vector3Add(pos, {-1, 0, -1}), Vector3Add(pos, {-1, 0, 0}),
	               Vector3Add(pos, {0, 0, -1}), colors[0]);
	DrawTriangle3D(pos, Vector3Add(pos, {0, -1, 0}),
	               Vector3Add(pos, {0, 0, -1}), colors[1]);
	DrawTriangle3D(Vector3Add(pos, {0, -1, -1}), Vector3Add(pos, {0, 0, -1}),
	               Vector3Add(pos, {0, -1, 0}), colors[1]);
	DrawTriangle3D(Vector3Add(pos, {0, 0, -1}), Vector3Add(pos, {0, -1, -1}),
	               Vector3Add(pos, {-1, 0, -1}), colors[2]);
	DrawTriangle3D(Vector3Add(pos, {-1, -1, -1}), Vector3Add(pos, {-1, 0, -1}),
	               Vector3Add(pos, {0, -1, -1}), colors[2]);

	DrawTriangle3D(Vector3Add(pos, {0, -1, 0}), Vector3Add(pos, {-1, -1, 0}),
	               Vector3Add(pos, {0, -1, -1}), colors[3]);
	DrawTriangle3D(Vector3Add(pos, {-1, -1, -1}), Vector3Add(pos, {0, -1, -1}),
	               Vector3Add(pos, {-1, -1, 0}), colors[3]);
	DrawTriangle3D(Vector3Add(pos, {-1, 0, 0}), Vector3Add(pos, {-1, 0, -1}),
	               Vector3Add(pos, {-1, -1, 0}), colors[4]);
	DrawTriangle3D(Vector3Add(pos, {-1, -1, -1}), Vector3Add(pos, {-1, -1, 0}),
	               Vector3Add(pos, {-1, 0, -1}), colors[4]);
	DrawTriangle3D(Vector3Add(pos, {0, 0, 0}), Vector3Add(pos, {-1, 0, 0}),
	               Vector3Add(pos, {0, -1, 0}), colors[5]);
	DrawTriangle3D(Vector3Add(pos, {-1, -1, 0}), Vector3Add(pos, {0, -1, 0}),
	               Vector3Add(pos, {-1, 0, 0}), colors[5]);
}

void draw_rcube()
{
	for (usize i = 0; i < 8; i++) {
		draw_cubie(corner_pos[g.rcube.cp[i]], corner_pos[i]);
	}
	for (usize i = 0; i < 12; i++) {
		draw_cubie(edge_pos[g.rcube.ep[i]], edge_pos[i]);
	}
	for (usize i = 0; i < 6; i++) {
		draw_cubie(center_pos[i], center_pos[i]);
	}
}

void render()
{
	Camera3D cam = make_camera(g.ocam);
	DrawText(TextFormat("0: (%f, %f, %f)", corner_pos[0].x, corner_pos[0].y,
	                    corner_pos[0].z),
	         10, 35, 20, FG);
	DrawText(TextFormat("1: (%f, %f, %f)", corner_pos[1].x, corner_pos[1].y,
	                    corner_pos[1].z),
	         10, 50, 20, FG);
	BeginMode3D(cam);

	draw_rcube();
	DrawModelWires(g.model, {0, 0, 0}, 1, BLACK);
	DrawGrid(10, 0.1);

	EndMode3D();
}

void init_graphics()
{
	g.ocam.radius = 10;
	g.ocam.pitch = 0;
	g.ocam.yaw = 0;

	Mesh mesh = GenMeshCube(3, 3, 3);
	g.model = LoadModelFromMesh(mesh);

	for (auto i : base_vs) {
		vs.push_back(i);
	}
}
