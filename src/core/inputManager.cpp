#include "inputManager.h"
#include "components/component.h" 

namespace IM {
    InteractionMode mode = InteractionMode::NORMAL;
    Node* wireStartNode = nullptr;

    void manageInput(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin) {
        if (IsKeyPressed(KEY_SPACE)){
        	if(mode == InteractionMode::WIRING){
        		mode = InteractionMode::NORMAL;
        	}
        	else{
        		mode = InteractionMode::WIRING;
        	}
        }
        switch (mode) {
            case InteractionMode::NORMAL:
                mouseEvents(circuit, selectedComponent, dragOffset, dustbin);
                break;
            case InteractionMode::WIRING:
                mouseHovering(circuit);
                addWire(circuit);
                break;
        }
    }

    void addWire(Circuit& circuit) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if (!wireStartNode) {
                wireStartNode = getClickedNode(circuit, mouse);
            } else {
                Node* secondNode = getClickedNode(circuit, mouse);
                if (secondNode && secondNode != wireStartNode) {
                    circuit.connectNodes(wireStartNode, secondNode);
                }
                wireStartNode = nullptr;
            }
        }
    }

    Node* getClickedNode(Circuit& circuit, Vector2 mousePosition) {
        for (const auto& component : circuit.getAllComponents()) {
            for (auto& node : component->m_inputNodes) {
                if (CheckCollisionPointCircle(mousePosition, node.position, node.radius + 1)) {
                    return &node;
                }
            }
            for (auto& node : component->m_outputNodes) {
                if (CheckCollisionPointCircle(mousePosition, node.position, node.radius + 1)) {
                    return &node;
                }
            }
        }
        return nullptr;
    }

    void mouseHovering(Circuit& circuit) {
        Vector2 mouse = GetMousePosition();
        for (const auto& component : circuit.getAllComponents()) {
            for (auto& node : component->m_inputNodes) {
                node.color = CheckCollisionPointCircle(mouse, node.position, node.radius + 1) ? GREEN : GRAY;
            }
            for (auto& node : component->m_outputNodes) {
                node.color = CheckCollisionPointCircle(mouse, node.position, node.radius + 1) ? GREEN : GRAY;
            }
        }
    }

    void mouseEvents(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin) {
        Vector2 mouse = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            selectedComponent = nullptr;
            for (const auto& component : circuit.getAllComponents()) {
                if (CheckCollisionPointRec(mouse, component->getInteractionBounds())) {
                    selectedComponent = component.get();
                    dragOffset = Vector2Subtract(selectedComponent->m_position, mouse);
                    break;
                }
            }
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectedComponent != nullptr) {
            // Use the setter to ensure node positions are also updated
            selectedComponent->setPosition(Vector2Add(mouse, dragOffset));

        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (selectedComponent != nullptr) {
                bool deselect = true;
                if (CheckCollisionRecs(selectedComponent->getInteractionBounds(), dustbin)) {
                    circuit.removeComponent(selectedComponent->getId());
                } else if (selectedComponent->isToggleable()) { // Use the virtual capability function
                    selectedComponent->toggle();
                    circuit.onClockTick();
                    deselect = false;
                }
                
                if (deselect) {
                    selectedComponent = nullptr;
                }
            }
        }
    }
};