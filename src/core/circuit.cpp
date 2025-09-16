#include "core/circuit.h"
#include <iostream>

unsigned int Circuit::m_idCounter = 0;

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

const Component* Circuit::getComponent(unsigned int id) const{
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

Component* Circuit::getComponent(unsigned int id){
	return const_cast<Component*>(
        static_cast<const Circuit*>(this)->getComponent(id)
    );
}

void Circuit::displayComponents() const{
	for(const auto& component : m_components){
		component->display();
	}
}

void Circuit::connectNodes(unsigned int id1, unsigned int id2){
	m_connections[id1].push_back(id2);
}


void Circuit::propogateUpdates(){
	
}

// helper functions
