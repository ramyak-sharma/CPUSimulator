#include "inputManager.h"

namespace IM{

	InteractionMode mode = InteractionMode::NORMAL;

	void manageInput(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin){
		switch(mode){
		case InteractionMode::NORMAL:
			dragAndDrop(circuit, selectedComponent, dragOffset, dustbin);
			break;
		case InteractionMode::WIRING:

			break;
		}

	}

	void dragAndDrop(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin){

		Vector2 mouse = GetMousePosition();
		const auto& components = circuit.getAllComponents();
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			for(const auto& component : components){
				float x = component->m_position.x;
				float y = component->m_position.y;
				if(CheckCollisionPointRec(mouse, component->getInteractionBounds())){
					selectedComponent = component.get();
					dragOffset = Vector2Subtract({x, y}, mouse);
	                break; 
				}
			}
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectedComponent != nullptr) {
	        selectedComponent->m_position.x = Vector2Add(mouse, dragOffset).x;
	        selectedComponent->m_position.y = Vector2Add(mouse, dragOffset).y;
	    }

	    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
	        if (selectedComponent != nullptr) {
	            if (CheckCollisionRecs(selectedComponent->getInteractionBounds(), dustbin)) {
	                circuit.removeComponent(selectedComponent->getId());
	            }
        	}
        	selectedComponent = nullptr;
	    }
		
	}

};
