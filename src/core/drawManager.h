#pragma once
#include "core/circuit.h"
#include "raylib.h"

namespace DM{
	void drawComponents(Circuit& circuit);
	void drawNodes(Circuit& circuit);
	void drawGUI(float w, float h, Circuit& circuit);
};