#include "core/circuit.h"
#include <iostream>

unsigned int Circuit::m_idCounter = 0;

void Wire::evaluate() const{
	if (auto srcLocked = src.lock()) {
        if (auto dstLocked = dst.lock()) {
            dstLocked->nextState = srcLocked->currentState;
        }
    }
}

void Wire::commit() const{
	if (auto dstLocked = dst.lock()) {
        dstLocked->currentState = dstLocked->nextState;
    }
}

Component* Circuit::addComponent(ComponentType type){
	unsigned int newId = ++m_idCounter;
	std::unique_ptr<Component> newComponent = nullptr;

	switch(type){
	case ComponentType::AND_GATE:
		newComponent = std::make_unique<AndGate>(newId);
		break;
	case ComponentType::NOT_GATE:
		newComponent = std::make_unique<NotGate>(newId);
		break;
	default:
		std::cout << "Invalid component type!\n";
		return nullptr;
	}

    Component* rawPtr = newComponent.get();
    m_components.push_back(std::move(newComponent));
    return rawPtr; 
    
}

const Component* Circuit::getComponentById(unsigned int id) const{
	for(const auto& component : m_components){
		if(component->getId() == id){
			return component.get();
		}
	}
	return nullptr;
}

const std::vector<std::unique_ptr<Component>>& Circuit::getAllComponents() const {
	return m_components;
}

Component* Circuit::getComponentById(unsigned int id){
	return const_cast<Component*>(
        static_cast<const Circuit*>(this)->getComponentById(id)
    );
}

void Circuit::onClockTick() {
    for (const auto& component : m_components) {
        component->evaluate();
    }

    for (const auto& wire : m_wires) {
        wire.evaluate();
    }

    for (const auto& component : m_components) {
        component->commit();
    }

    for (const auto& wire : m_wires) {
        wire.commit();
    }
}

void Circuit::removeComponent(unsigned int id){
	auto it = std::remove_if(m_components.begin(), m_components.end(), 
		[id](const std::unique_ptr<Component>& component){return component->getId() == id;});
	m_components.erase(it, m_components.end());
}

bool Circuit::connectNodes(std::weak_ptr<Node>& src, std::weak_ptr<Node>& dst) {
    // Lock the weak pointers to get shared pointers
    auto srcLocked = src.lock();
    auto dstLocked = dst.lock();
    
    // Check if nodes still exist
    if(!srcLocked || !dstLocked) return false;

    // Check node types and swap if needed
    if(srcLocked->type == NodeType::INPUT && dstLocked->type == NodeType::OUTPUT) {
        std::swap(src, dst);
        // Re-lock after swap
        srcLocked = src.lock();
        dstLocked = dst.lock();
    }
    
    // Check valid connection
    if(srcLocked->type == NodeType::OUTPUT && dstLocked->type == NodeType::INPUT){
        Wire newWire;
        newWire.src = src;  // Already weak_ptr, no need to convert
        newWire.dst = dst;  // Already weak_ptr, no need to convert
        m_wires.push_back(newWire);
        return true;
    }
    
    return false;
}

// helper functions
