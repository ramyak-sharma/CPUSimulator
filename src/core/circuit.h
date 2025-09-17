#pragma once
#include <vector>
#include <unordered_map>
#include "components/common.h"
#include "components/component.h"
#include "components/gates/andGate.h"
#include "components/gates/notGate.h"

struct Wire
{
	std::weak_ptr<Node>src;
	std::weak_ptr<Node> dst;
};

class Circuit
{
private:
	std::vector<std::unique_ptr<Component>> m_components; //unnecessary but never got the chance to use smart ptrs
	std::vector<std::unique_ptr<Wire>> m_wires;

	static unsigned int m_idCounter;

public:
	Component* addComponent(ComponentType type);

	void removeComponent(unsigned int id);

	const Component* getComponentById(unsigned int id) const;

	const std::vector<std::unique_ptr<Component>>& getAllComponents() const;

	Component* getComponentById(unsigned int id);

	void connectNodes();

	void onClockTick();

	void propogateUpdates();
};
