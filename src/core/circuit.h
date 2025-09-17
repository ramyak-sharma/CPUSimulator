#pragma once
#include <vector>
#include <unordered_map>
#include "components/common.h"
#include "components/component.h"
#include "components/gates/andGate.h"
#include "components/gates/notGate.h"
#include "components/gates/inLight.h"
#include "components/gates/outLight.h"
#include <functional>

// Specialize std::hash for std::pair<unsigned int, unsigned int>
namespace std {
    template <>
    struct hash<std::pair<unsigned int, unsigned int>> {
        size_t operator()(const std::pair<unsigned int, unsigned int>& p) const {
            // Combine the hash of both elements
            auto h1 = std::hash<unsigned int>{}(p.first);
            auto h2 = std::hash<unsigned int>{}(p.second);
            return h1 ^ (h2 << 1);  // Simple but effective combination
        }
    };
}

class Wire
{
public:
	Node* src = nullptr;
	Node* dst = nullptr;

	void evaluate() const;

	void commit() const;
};

class Circuit
{
private:
	std::vector<std::unique_ptr<Component>> m_components; //unnecessary but never got the chance to use smart ptrs
	std::vector<Wire> m_wires;
	static unsigned int m_idCounter;
	std::unordered_map<std::pair<unsigned int, unsigned int>, Node*> m_nodes; //{component_id, node_id} -> node*

public:
	std::vector<Wire> getWires(){return m_wires;}

	Component* addComponent(ComponentType type);

	void removeComponent(unsigned int id);

	void removeWireWithNode(Node* node);

	const Component* getComponentById(unsigned int id) const;

	const std::vector<std::unique_ptr<Component>>& getAllComponents() const;

	Component* getComponentById(unsigned int id);

	bool connectNodes(Node* src, Node* dst);

	void onClockTick();

};
