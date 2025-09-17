#include <iostream>
#include "core/circuit.h"
#include "raylib.h"
#include "raymath.h"
#include "core/inputManager.h"
#include "core/drawManager.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    int screenWidth = 1280;
    int screenHeight = 800;

    #ifdef __APPLE__
        unsigned int flags = FLAG_WINDOW_HIGHDPI;
    #endif

    SetConfigFlags(flags);

    InitWindow(screenWidth, screenHeight, "CPU Simulator");
    SetTargetFPS(60);

    Circuit circuit;

    Texture2D texture = LoadTexture("../assets/dustbin.jpeg");
    Rectangle sourceRec = { 0, 0, (float)texture.width, (float)texture.height };

    Component* selectedComponent = nullptr;
    Vector2 dragOffset = { 0.0f, 0.0f };

    bool autoTickEnabled = false;
    float tickSpeed = 1.0f;
    double lastTickTime = GetTime();

    while (!WindowShouldClose()) {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        float desiredWidth = 50.0f;
        float desiredHeight = 50.0f;
        Rectangle destRec = {
            screenWidth - desiredWidth - 10,
            screenHeight - desiredHeight - 10,
            desiredWidth,
            desiredHeight
        };

        IM::manageInput(circuit, selectedComponent, dragOffset, destRec);
        
        BeginDrawing();
            ClearBackground(DARKGRAY);
            
            DM::drawComponents(circuit);
            DM::drawWires(circuit);
            DM::drawGhostWire();
            DM::drawDustbin(texture, sourceRec, destRec);
            DM::drawGUI(screenWidth, screenHeight, circuit);
            
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}