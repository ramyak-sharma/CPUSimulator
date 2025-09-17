#pragma once
#include "core/circuit.h"
#include "raylib.h"

namespace DM{
	void drawComponents(Circuit& circuit);
	void drawNodes(Circuit& circuit);
	void drawDustbin(Texture2D texture, Rectangle src, Rectangle dst);
	void drawGUI(float screenWidth, float screenHeight, Circuit& circuit);
	void drawWires(Circuit& circuit);
	void drawGhostWire();
	void drawButtonsVertically(const std::vector<Button>& buttons, Vector2 startPos, Vector2 buttonSize, float padding);
	void drawButtonsHorizontally(const std::vector<Button>& buttons, Vector2 startPos, Vector2 buttonSize, float padding);
	std::vector<Vector2> getNodePositions(Rectangle mainBounds, int numNodes, bool right);
};