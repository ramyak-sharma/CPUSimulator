#include "inputManager.h"

namespace IM{

	InteractionMode mode = InteractionMode::NORMAL;

	void manageInput(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin){
		switch(mode){
		case InteractionMode::NORMAL:
			mouseEvents(circuit, selectedComponent, dragOffset, dustbin);
			break;
		case InteractionMode::WIRING:
			mouseHovering(circuit);
			break;
		}

	}

	Node* getClickedNode(Circuit& circuit, Vector2 mousePosition) {
	    for (const auto& component : circuit.getAllComponents()) {
	        // Check input nodes
	        for (const auto& node : component->m_inputNodes) {
	            if (CheckCollisionPointCircle(mousePosition, node->position, node->radius)) {
	                return node.get(); 
	            }
	        }
	        
	        // Check output nodes
	        for (const auto& node : component->m_outputNodes) {
	            if (CheckCollisionPointCircle(mousePosition, node->position, node->radius)) {
	                return node.get();
	            }
	        }
	    }
	    return nullptr;
	}

	void mouseHovering(Circuit& circuit){
	    Vector2 mouse = GetMousePosition();
	    bool isHoveringAnyNode = false;
	    Color c = GRAY;
	    for(const auto& component : circuit.getAllComponents()){
	        for(const auto& node : component->m_inputNodes){
	            node->color = c; 
	            if(CheckCollisionPointCircle(mouse, node->position, node->radius + 1)){
	                node->color = GREEN;
	                isHoveringAnyNode = true;
	            }
	        }
	      
	        for(const auto& node : component->m_outputNodes){
	            node->color = c;
	            
	            if(CheckCollisionPointCircle(mouse, node->position, node->radius + 1)){
	                node->color = GREEN;
	                isHoveringAnyNode = true;
	            }
	        }
	    }
	}

	void mouseEvents(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin){

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
