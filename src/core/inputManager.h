#pragma once
#include "core/circuit.h"
#include "raylib.h"
#include "raymath.h"

namespace IM{

	Rectangle getBounds(Component* c);

	Rectangle getInteractionBounds(Component* c);

	void dragAndDrop(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset);


};

