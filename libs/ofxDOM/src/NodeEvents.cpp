////
////  NodeEvents.cpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/14/20.
////
//
#include "ofx/DOM/NodeEvents.h"
#include "ofx/DOM/Node.h"
#include <type_traits>

namespace ofx {
namespace DOM {


Node* NodeEventArgs::node()
{
    return _node;
}


const Node* NodeEventArgs::node() const
{
    return _node;
}

NodeEventArgs::NodeEventArgs(Node* node):
    _node(node)
{
//	static_assert(std::is_base_of<Node< decltype(Node) >, Node>::value, "NodeEventArgs Node must be a Node or inherit from it.");
	
}


NodeEventArgs::~NodeEventArgs()
{
}


NodeOrderEventArgs::NodeOrderEventArgs(Node* node,
                                             std::size_t oldIndex,
                                             std::size_t newIndex):
    NodeEventArgs(node),
    _oldIndex(oldIndex),
    _newIndex(newIndex)
{

}


NodeOrderEventArgs::~NodeOrderEventArgs()
{
	
}


std::size_t NodeOrderEventArgs::oldIndex() const
{
    return _oldIndex;
}
    

std::size_t NodeOrderEventArgs::newIndex() const
{
    return _newIndex;
}


bool NodeOrderEventArgs::wasMovedForward() const
{
    return _oldIndex > _newIndex;
}


bool NodeOrderEventArgs::wasMovedBackward() const
{
    return _newIndex > _oldIndex;
}


bool NodeOrderEventArgs::isAtFront() const
{
    return _newIndex == 0;
}


bool NodeOrderEventArgs::isAtBack() const
{
    return NodeEventArgs::node()->numSiblings() == _newIndex;
}



} } // namespace ofx::DOM
