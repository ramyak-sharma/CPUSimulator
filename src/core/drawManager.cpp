#include <vector>
#include <string>
#include "core/drawManager.h"
#include "raygui.h"

namespace DM{
	void drawComponents(Circuit& circuit){
		const auto& components = circuit.getAllComponents();
		
		for(const auto& component : components){
			float x = component->m_x;
			float y = component->m_y;
			ComponentType type = component->m_type;
			if(type == ComponentType::AND_GATE){
				DrawRectangle(x, y, 50, 50, BLUE);
			}
			else if(type == ComponentType::NOT_GATE){
				DrawRectangle(x, y, 50, 25, RED);
			}
		}
	}


	void drawGUI(float w, float h, Circuit& circuit){
		std::vector<std::string> buttons = {"AND", "NOT"};
		
		float initial_x = 20.0f;
	    float initial_y = h - 70.0f; 
	    float button_width = 100.0f;
	    float button_height = 50.0f;
	    float padding = 10.0f;

	    //add components GUI
		for (int i = 0; i < buttons.size(); i++) {
        float button_x = initial_x + i * (button_width + padding);

        if (GuiButton({button_x, initial_y, button_width, button_height}, buttons[i].c_str())) {
            if (buttons[i] == "AND") {
                circuit.addComponent(ComponentType::AND_GATE);
            }else if (buttons[i] == "NOT"){
            	circuit.addComponent(ComponentType::NOT_GATE);
            }
        }
    }
	}
};