#include <vector>
#include <string>
#include "core/drawManager.h"
#include "core/inputManager.h"
#include "raygui.h"

namespace DM{

	void drawDustbin(Texture2D texture, Rectangle src, Rectangle dst){
		DrawTexturePro(texture, src, dst, (Vector2){0, 0}, 0.0f, WHITE);
	}

	void drawWires(Circuit& circuit){
		for(const auto& wire : circuit.getWires()){
			if (auto src = wire.src.lock()) {
				if (auto dst = wire.dst.lock()) {
					Vector2 start = src->position;
					Vector2 end = dst->position;
					DrawLineBezier(start, end, 4, RED);
				}
			}
		}
	}

	void addWire(Circuit& circuit, Vector2 mouse, bool& isNodeSelected, std::weak_ptr<Node>& selectedNode){
		if(!isNodeSelected){
			// First node selection
			Node* clickedNode = IM::getClickedNode(circuit, mouse);
			if(!clickedNode) return;
			
			isNodeSelected = true;
			// Get the shared_ptr from the component that owns this node
			auto clickedNodeShared = circuit.getSharedPtrForNode(clickedNode);
			if (clickedNodeShared) {
				selectedNode = clickedNodeShared; // Store as weak_ptr
				clickedNode->color = YELLOW; // Visual feedback
			} else {
				isNodeSelected = false; // Reset if we couldn't get shared_ptr
			}
		} else {
			// Draw temporary wire from selected node to mouse
			if (auto srcShared = selectedNode.lock()) {
				DrawLineBezier(srcShared->position, mouse, 4, BLACK);
				
				// Second node selection
				Node* clickedNode = IM::getClickedNode(circuit, mouse);
				if(!clickedNode) return;
				
				// Get shared_ptr for destination node
				auto dstShared = circuit.getSharedPtrForNode(clickedNode);
				if (!dstShared) return;
				
				// Create connection using weak_ptr references
				if (circuit.connectNodes(selectedNode, std::weak_ptr<Node>(dstShared))) {
					std::cout << "Wire connected successfully!\n";
				}
				
				// Reset selection
				isNodeSelected = false;
				srcShared->color = GRAY; // Reset color using the locked shared_ptr
				selectedNode.reset();
			}
		}
	}

	void drawComponents(Circuit& circuit){
		const auto& components = circuit.getAllComponents();

		float outlineThickness = 4.0f;
		Color outlineColor = BLACK;
		int fontSize = 20;

		for(const auto& component : components){


			Rectangle mainBounds = {
				component->m_position.x,
				component->m_position.y,
				component->m_size.x,
				component->m_size.y
			};

			Rectangle outlineBounds = {
				mainBounds.x - outlineThickness,
				mainBounds.y - outlineThickness,
				mainBounds.width + (outlineThickness * 2),
				mainBounds.height + (outlineThickness * 2)
			};

			DrawRectangleRec(outlineBounds, outlineColor);

			DrawRectangleRec(mainBounds, component->m_color);

			// add text
			const char* text = component->m_label.c_str();
			float textWidth = MeasureText(text, fontSize);

			float textX = mainBounds.x + (mainBounds.width - textWidth) / 2;
			float textY = mainBounds.y + (mainBounds.height - fontSize) / 2;
			
			DrawText(text, textX, textY, fontSize, WHITE);

			int numInNodes = component->m_inputNodes.size();
			int numOutNodes = component->m_outputNodes.size();

			std::vector<Vector2> inPos = getNodePositions(mainBounds, numInNodes, false);
			std::vector<Vector2> outPos = getNodePositions(mainBounds, numOutNodes, true);

			for(int i = 0; i < numInNodes; i++){
				component->m_inputNodes[i]->position = inPos[i];
				DrawCircleV(inPos[i], component->m_inputNodes[i]->radius, component->m_inputNodes[i]->color);
			}

			for(int i = 0; i < numOutNodes; i++){
				component->m_outputNodes[i]->position = outPos[i];
				DrawCircleV(outPos[i], component->m_outputNodes[i]->radius, component->m_outputNodes[i]->color);
			}
			

		}
	}

	void drawGUI(float screenWidth, float screenHeight, Circuit& circuit){
		
		float padding = 10.0f;
		Vector2 buttonSize = {100.0f, 50.0f};

		std::vector<Button> componentButtons{
			{"AND", [&](){circuit.addComponent(ComponentType::AND_GATE);}},
			{"NOT", [&](){circuit.addComponent(ComponentType::NOT_GATE);}}
		};

		std::vector<Button> modeButtons{
			{"NORMAL", [&](){IM::mode = InteractionMode::NORMAL;}},
			{"WIRING", [&](){IM::mode = InteractionMode::WIRING;}}
		};

		drawButtonsHorizontally(componentButtons, {20, screenHeight - 70}, buttonSize, padding);
		drawButtonsVertically(modeButtons, {screenWidth - buttonSize.x - 20, 20}, buttonSize, padding);
	}

	std::vector<Vector2> getNodePositions(Rectangle mainBounds, int numNodes, bool right) {
		std::vector<Vector2> positions;

		if (numNodes <= 0) return {};

		// Calculate spacing between nodes along the edge
		float spacing = mainBounds.height / (numNodes + 1);

		for (int i = 0; i < numNodes; ++i) {
			// Calculate y position
			float x = mainBounds.x - 3;
			if(right) x = mainBounds.x + mainBounds.width + 3;
			float y = mainBounds.y + spacing * (i + 1);
			positions.push_back({x,y});

		}
		return positions;
	}

	void drawButtonsVertically(const std::vector<Button>& buttons, Vector2 startPos, Vector2 buttonSize, float padding){
		for (int i = 0; i < buttons.size(); i++) {
			float button_y = startPos.y + i * (buttonSize.y + padding);
			Rectangle buttonBounds = {startPos.x, button_y, buttonSize.x, buttonSize.y};
			if (GuiButton(buttonBounds, buttons[i].label.c_str())) {
				buttons[i].onClick();
			}
		}
	}

	void drawButtonsHorizontally(const std::vector<Button>& buttons, Vector2 startPos, Vector2 buttonSize, float padding){
		for (int i = 0; i < buttons.size(); i++) {
			float button_x = startPos.x + i * (buttonSize.x + padding);
			Rectangle buttonBounds = {button_x, startPos.y, buttonSize.x, buttonSize.y};
			if (GuiButton(buttonBounds, buttons[i].label.c_str())) {
				buttons[i].onClick();
			}
		}
	}
};