#pragma once
#include "core/circuit.h"
#include "components/common.h"
#include "raylib.h"
#include "raymath.h"

namespace IM{

	extern InteractionMode mode;
	extern Node* wireStartNode;

	Rectangle getBounds(Component* c);

	Rectangle getInteractionBounds(Component* c);

	void mouseEvents(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin);
	void mouseHovering(Circuit& circuit);
	void manageInput(Circuit& circuit, Component*& selectedComponent, Vector2& dragOffset, Rectangle dustbin);
	Node* getClickedNode(Circuit& circuit, Vector2 mousePosition);
	std::weak_ptr<Node> getSharedPtrFromNode(Circuit& circuit, Node* rawNodePtr);
    std::shared_ptr<Node> getSharedPtrFromNodeStrong(Circuit& circuit, Node* rawNodePtr);
    void addWire(Circuit& circuit);



};

