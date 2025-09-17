#include "core/circuit.h"
#include <iostream>
#include <algorithm>

unsigned int Circuit::m_idCounter = 0;

void Wire::evaluate() const {
    dst->nextState = src->currentState;
}

void Wire::commit() const {
    dst->currentState = dst->nextState;
}

void Circuit::removeWireWithNode(Node* node) {
    auto it = std::remove_if(m_wires.begin(), m_wires.end(), 
        [node](const Wire& wire) { return (wire.src == node || wire.dst == node); });
    m_wires.erase(it, m_wires.end());
}

Component* Circuit::addComponent(ComponentType type) {
    unsigned int newId = ++m_idCounter;
    std::unique_ptr<Component> newComponent = nullptr;
    
    switch(type) {
    case ComponentType::AND_GATE:
        newComponent = std::make_unique<AndGate>(newId);
        break;
    case ComponentType::NOT_GATE:
        newComponent = std::make_unique<NotGate>(newId);
        break;
    case ComponentType::INLIGHT:
        newComponent = std::make_unique<InLight>(newId);
        break;
    case ComponentType::OUTLIGHT:
        newComponent = std::make_unique<OutLight>(newId);
        break;
    default:
        std::cout << "Invalid component type!\n";
        return nullptr;
    }
    
    unsigned int compId = newComponent->getId();
    for(auto& node : newComponent->m_inputNodes) {
        m_nodes[{compId, node.id}] = &node;
    }
    for(auto& node : newComponent->m_outputNodes) { 
        m_nodes[{compId, node.id}] = &node;
    }
    
    Component* rawPtr = newComponent.get();
    m_components.push_back(std::move(newComponent));
    return rawPtr;
}

const Component* Circuit::getComponentById(unsigned int id) const {
    for(const auto& component : m_components) {
        if(component->getId() == id) {
            return component.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Component>>& Circuit::getAllComponents() const {
    return m_components;
}

Component* Circuit::getComponentById(unsigned int id) {
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

void Circuit::removeComponent(unsigned int id) {
    // Remove wires connected to nodes of this component
    for(const auto& [idPair, nodePtr] : m_nodes) {
        if(idPair.first == id) {
            removeWireWithNode(nodePtr);
        }
    }
    
    // Remove nodes from map
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ) {
        if (it->first.first == id) {
            it = m_nodes.erase(it);
        } else {
            ++it;
        }
    }
    
    // Remove component from m_components
    auto it = std::remove_if(m_components.begin(), m_components.end(), 
        [id](const std::unique_ptr<Component>& component) { return component->getId() == id; });
    m_components.erase(it, m_components.end());
}

bool Circuit::connectNodes(Node* node1, Node* node2) {
    Node* src = nullptr;
    Node* dst = nullptr;

    // The connection is in the correct order
    if (node1->type == NodeType::OUTPUT && node2->type == NodeType::INPUT) {
        src = node1;
        dst = node2;
    } 
    // The connection is in the reversed order
    else if (node1->type == NodeType::INPUT && node2->type == NodeType::OUTPUT) {
        src = node2;
        dst = node1;
    } 
    // The connection is invalid (e.g., input to input)
    else {
        return false;
    }

    if(dst->incomingConnection){return false;}
    dst->incomingConnection = src;

    Wire w;
    w.src = src;
    w.dst = dst;
    m_wires.push_back(w);
    
    return true;
}