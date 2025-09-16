#pragma once
#include <vector>
#include <unordered_map>
#include "components/common.h"
#include "components/component.h"
#include "components/gates/andGate.h"
#include "components/gates/notGate.h"


class Circuit
{
private:
	std::vector<std::unique_ptr<Component>> m_components;

	static unsigned int m_idCounter;

public:
	Component* addComponent(ComponentType type);

	const Component* getComponent(unsigned int id) const;

	const std::vector<std::unique_ptr<Component>>& getAllComponents() const;

	Component* getComponent(unsigned int id);

	void connectNodes(unsigned int id1, unsigned int id2);

	void displayComponents() const;

	void propogateUpdates();
};
