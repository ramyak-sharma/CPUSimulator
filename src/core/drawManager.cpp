#include <vector>
#include <string>
#include "core/drawManager.h"
#include "core/inputManager.h" // For IM::mode
#include "raygui.h"

namespace DM {

    void drawGhostWire() {
        if (IM::mode == InteractionMode::WIRING && IM::wireStartNode != nullptr) {
            Vector2 start = IM::wireStartNode->position;
            Vector2 end = GetMousePosition();
            DrawLineBezier(start, end, 2, YELLOW);
        }
    }

    void drawDustbin(Texture2D texture, Rectangle src, Rectangle dst) {
        DrawTexturePro(texture, src, dst, {0, 0}, 0.0f, WHITE);
    }

    void drawWires(Circuit& circuit) {
        for (const auto& wire : circuit.getWires()) {
            Color wireColor = (wire.src->currentState == LogicState::HIGH) ? YELLOW : GRAY;
            DrawLineBezier(wire.src->position, wire.dst->position, 4, wireColor);
        }
    }

    void drawComponents(Circuit& circuit) {
        const auto& components = circuit.getAllComponents();
        float outlineThickness = 4.0f;
        Color outlineColor = BLACK;
        int fontSize = 20;

        for (const auto& component : components) {
            Rectangle mainBounds = component->getBounds();
            Rectangle outlineBounds = {
                mainBounds.x - outlineThickness,
                mainBounds.y - outlineThickness,
                mainBounds.width + (outlineThickness * 2),
                mainBounds.height + (outlineThickness * 2)
            };

            DrawRectangleRec(outlineBounds, outlineColor);
            DrawRectangleRec(mainBounds, component->m_color);

            const char* text = component->m_label.c_str();
            float textWidth = MeasureText(text, fontSize);
            float textX = mainBounds.x + (mainBounds.width - textWidth) / 2;
            float textY = mainBounds.y + (mainBounds.height - fontSize) / 2;
            DrawText(text, textX, textY, fontSize, WHITE);

            // The component now manages its own node positions. We just draw them.
            for (const auto& node : component->m_inputNodes) {
                DrawCircleV(node.position, node.radius, node.color);
            }
            for (const auto& node : component->m_outputNodes) {
                DrawCircleV(node.position, node.radius, node.color);
            }
        }
    }

    void drawGUI(float screenWidth, float screenHeight, Circuit& circuit) {
        Color semiTransparentWhite = {255, 255, 255, 127};
        if(IM::mode == InteractionMode::WIRING){
        	DrawText("W", 0, 0, 20, semiTransparentWhite);
        }else if(IM::mode == InteractionMode::NORMAL){
        	DrawText("E", 0, 0, 20, semiTransparentWhite);
        }
        
        float padding = 10.0f;
        Vector2 buttonSize = {100.0f, 50.0f};

        std::vector<Button> componentButtons{
            {"AND",      [&](){ circuit.addComponent(ComponentType::AND_GATE); }},
            {"NOT",      [&](){ circuit.addComponent(ComponentType::NOT_GATE); }},
            {"IN_LIGHT", [&](){ circuit.addComponent(ComponentType::INLIGHT); }},
            {"OUT_LIGHT",[&](){ circuit.addComponent(ComponentType::OUTLIGHT); }}
        };

        std::vector<Button> modeButtons{
            {"NORMAL", [](){ IM::mode = InteractionMode::NORMAL; }},
            {"WIRING", [](){ IM::mode = InteractionMode::WIRING; }}
        };

        std::vector<Button> clockButton{
            {"TICK", [&](){ circuit.onClockTick(); }}
        };

        drawButtonsHorizontally(componentButtons, {20, screenHeight - 70}, buttonSize, padding);
        drawButtonsVertically(modeButtons, {screenWidth - buttonSize.x - 20, 20}, buttonSize, padding);
        
        Rectangle clockBounds = {screenWidth / 2 - buttonSize.x / 2, 20, buttonSize.x, buttonSize.y};
        if (GuiButton(clockBounds, clockButton[0].label.c_str())) {
            clockButton[0].onClick();
        }

    }

    void drawButtonsVertically(const std::vector<Button>& buttons, Vector2 startPos, Vector2 buttonSize, float padding) {
        for (int i = 0; i < buttons.size(); i++) {
            float button_y = startPos.y + i * (buttonSize.y + padding);
            Rectangle buttonBounds = {startPos.x, button_y, buttonSize.x, buttonSize.y};
            if (GuiButton(buttonBounds, buttons[i].label.c_str())) {
                buttons[i].onClick();
            }
        }
    }

    void drawButtonsHorizontally(const std::vector<Button>& buttons, Vector2 startPos, Vector2 buttonSize, float padding) {
        for (int i = 0; i < buttons.size(); i++) {
            float button_x = startPos.x + i * (buttonSize.x + padding);
            Rectangle buttonBounds = {button_x, startPos.y, buttonSize.x, buttonSize.y};
            if (GuiButton(buttonBounds, buttons[i].label.c_str())) {
                buttons[i].onClick();
            }
        }
    }
};