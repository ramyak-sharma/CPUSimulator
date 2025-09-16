#include <iostream>
#include "core/circuit.h"
#include "raylib.h"
#include "raymath.h"
#include "core/inputManager.h"
#include "core/drawManager.h"
#include "core/circuit.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
	
	#ifdef __APPLE__
		SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	#endif

    InitWindow(screenWidth, screenHeight, "Coordinate System Test");
    SetTargetFPS(60);

	Circuit circuit;
	circuit.addComponent(ComponentType::AND_GATE);
	circuit.addComponent(ComponentType::NOT_GATE);
	circuit.displayComponents();

	Component* selectedComponent = nullptr;
	Vector2 dragOffset = { 0.0f, 0.0f };

    while (!WindowShouldClose()) {
		IM::dragAndDrop(circuit, selectedComponent, dragOffset);
		BeginDrawing();
		ClearBackground(DARKGRAY);
		DM::drawComponents(circuit);
        DM::drawGUI(screenWidth, screenHeight, circuit);
		EndDrawing();
	}

    CloseWindow();
    return 0;
}
