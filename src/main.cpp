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

	Circuit circuit;

    Texture2D texture = LoadTexture("../assets/dustbin.jpeg");

    // Source rectangle uses the full texture
    Rectangle sourceRec = { 0, 0, (float)texture.width, (float)texture.height };

    // Destination rectangle is smaller and positioned at bottom-right
    float desiredWidth = 50.0f;
    float desiredHeight = 50.0f;
    Rectangle destRec = {
        screenWidth - desiredWidth,
        screenHeight - desiredHeight,
        desiredWidth,
        desiredHeight
    };

    SetTargetFPS(60);

	Component* selectedComponent = nullptr;
	Vector2 dragOffset = { 0.0f, 0.0f };

    while (!WindowShouldClose()) {
		IM::manageInput(circuit, selectedComponent, dragOffset, destRec);
		
        BeginDrawing();
		  
            ClearBackground(DARKGRAY);

            DM::drawDustbin(texture, sourceRec, destRec);
		
            DM::drawComponents(circuit);
        
            DM::drawGUI(screenWidth, screenHeight, circuit);
		
        EndDrawing();
	}

    CloseWindow();
    return 0;
}
