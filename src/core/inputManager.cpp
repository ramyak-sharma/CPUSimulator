#include "inputManager.h"

namespace IM{

	void dragAndDrop(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset){
		Vector2 mouse = GetMousePosition();
		const auto& components = circuit.getAllComponents();
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			for(const auto& component : components){
				float x = component->m_x;
				float y = component->m_y;
				if(CheckCollisionPointRec(mouse, component->getInteractionBounds())){
					selectedComponent = component.get();
					dragOffset = Vector2Subtract({x, y}, mouse);
	                break; 
				}
			}
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectedComponent != nullptr) {
	        selectedComponent->m_x = Vector2Add(mouse, dragOffset).x;
	        selectedComponent->m_y = Vector2Add(mouse, dragOffset).y;
	    }

	    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
	        selectedComponent = nullptr;
	    }
		
	}

};
