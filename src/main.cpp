#include <vector>

#include "common.h"
#include "raylib.h"

using namespace std;

Global g;

float dt = 1.f / 60.f;

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

void input(void)
{
	static Vector2 mouseorig;
	Vector2 mousepos = GetMousePosition();
	float angle = PI * dt;
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		mouseorig = mousepos;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		Vector2 delta = {mousepos.x - mouseorig.x, mousepos.y - mouseorig.y};
		DrawCircle(mouseorig.x, mouseorig.y, 10, FG);
		DrawText(TextFormat("delta: (%f, %f)", delta.x, delta.y), 10, 10, 20,
		         FG);
		rotate_vs({0, -1, 0}, delta.x / 10000);
		rotate_vs({-1, 0, 0}, delta.y / 10000);
	}

	if (IsKeyDown(KEY_LEFT)) {
		rotate_vs({0, 1, 0}, angle);
	}
	if (IsKeyDown(KEY_RIGHT)) {
		rotate_vs({0, 1, 0}, -angle);
	}
	if (IsKeyDown(KEY_UP)) {
		rotate_vs({1, 0, 0}, angle);
	}
	if (IsKeyDown(KEY_DOWN)) {
		rotate_vs({1, 0, 0}, -angle);
	}
}

int main(int argc, char **argv)
{

	init_game();
	init_vs();
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BG);
		input();
		render();
		EndDrawing();
	}

	return 0;
}
