#include "common.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

Global g;

void init_game(void)
{
	InitWindow(1080, 720, "rcube");
	SetTargetFPS(60);
	int display = GetCurrentMonitor();
	g.width = GetMonitorWidth(display);
	g.height = GetMonitorHeight(display);
	SetWindowSize(g.width, g.height);
}

Point point(Vector2 v)
{
	return {cast(int)(v.x), cast(int)(v.y)};
}

static Matrix rot = MatrixIdentity();
void input(void)
{
	DrawText(TextFormat("yaw: %f, pitch: %f", g.ocam.yaw, g.ocam.pitch), 10, 10,
	         20, FG);
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 d = GetMouseDelta();
		g.ocam.yaw -= d.x * 0.005f;
		g.ocam.pitch += d.y * 0.003f;

		g.ocam.pitch = Clamp(g.ocam.pitch, -1.553f, 1.553f);
	}

	if (IsKeyPressed(KEY_R)) {
		g.ocam.yaw = 0;
		g.ocam.pitch = 0;
	}

	/*
	    static Vector2 mouseorig;
	    Vector2 mousepos = GetMousePosition();
	    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
	        mouseorig = mousepos;
	    }

	    if (IsKeyPressed(KEY_R)) {
	        rot = MatrixIdentity();
	        g.model.transform = rot;
	    }

	    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
	        Vector2 delta = {mousepos.x - mouseorig.x, mousepos.y -
	   mouseorig.y}; DrawCircle(mouseorig.x, mouseorig.y, 10, FG);
	        DrawText(TextFormat("delta: (%f, %f)", delta.x, delta.y), 10, 10,
	   20, FG);

	        float sx = delta.x * 0.0001f;
	        float sy = delta.y * 0.0001f;

	        Vector3 cam_forward = Vector3Normalize(
	            Vector3Subtract(g.camera.target, g.camera.position));
	        Vector3 cam_right =
	            Vector3Normalize(Vector3CrossProduct(cam_forward, g.camera.up));
	        Vector3 cam_up = Vector3CrossProduct(cam_right, cam_forward);

	        Matrix rot_y = MatrixRotate(cam_up, sx);
	        Matrix rot_x = MatrixRotate(cam_right, sy);

	        // IMPORTANT: pre-multiply (view-space)
	        rot = MatrixMultiply(rot, rot_y);
	        rot = MatrixMultiply(rot, rot_x);

	        g.model.transform = rot;
	    } */
}

int main(int argc, char **argv)
{

	init_game();
	init_graphics();
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BG);
		input();
		render();
		EndDrawing();
	}

	return 0;
}
