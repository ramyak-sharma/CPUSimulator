#pragma once
#include "core/circuit.h"
#include "raylib.h"

namespace DM{
	void drawComponents(Circuit& circuit);
	void drawNodes(Circuit& circuit);
	void drawDustbin(Texture2D texture, Rectangle src, Rectangle dst);
	void drawGUI(float w, float h, Circuit& circuit);
	void drawWires();
	void drawButtonsVertically(const std::vector<Button>& buttons, Vector2 startPos, Vector2 buttonSize, float padding);
	void drawButtonsHorizontally(const std::vector<Button>& buttons, Vector2 startPos, Vector2 buttonSize, float padding);
	std::vector<Vector2> getNodePositions(Rectangle mainBounds, int numNodes, bool right);
};