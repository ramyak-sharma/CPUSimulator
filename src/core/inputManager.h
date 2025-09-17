#pragma once
#include "core/circuit.h"
#include "components/common.h"
#include "raylib.h"
#include "raymath.h"

namespace IM{

	extern InteractionMode mode;

	Rectangle getBounds(Component* c);

	Rectangle getInteractionBounds(Component* c);

	void dragAndDrop(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin);

	void manageInput(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin);


};

