//
//  NodeEvents.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//

#include "ofx/DOM/Events/NodeEvents.h"
#include "ofx/DOM/Node.h"
#include <type_traits>

namespace ofx {
namespace DOM {

template<typename NodeType>
NodeEventArgs_<NodeType>::NodeEventArgs_(NodeType* node):
    _node(node)
{
	static_assert(std::is_base_of<Node<NodeType>, NodeType>::value, "NodeEventArgs_ NodeType must be a Node or inherit from it.");
	
}

template<typename NodeType>
NodeEventArgs_<NodeType>::~NodeEventArgs_()
{
}

//template<typename NodeType>
//NodeType* NodeEventArgs_<NodeType>::node()
//{
//    return _node;
//}
//
//template<typename NodeType>
//const NodeType* NodeEventArgs_<NodeType>::node() const
//{
//    return _node;
//}

template<typename NodeType>
NodeOrderEventArgs_<NodeType>::NodeOrderEventArgs_(NodeType* node,
                                             std::size_t oldIndex,
                                             std::size_t newIndex):
    NodeEventArgs_<NodeType>(node),
    _oldIndex(oldIndex),
    _newIndex(newIndex)
{
	static_assert(std::is_base_of<Node<NodeType>, NodeType>::value, "NodeOrderEventArgs_ NodeType must be a Node or inherit from it.");
}

template<typename NodeType>
NodeOrderEventArgs_<NodeType>::~NodeOrderEventArgs_()
{
	
}

template<typename NodeType>
std::size_t NodeOrderEventArgs_<NodeType>::oldIndex() const
{
    return _oldIndex;
}
    
template<typename NodeType>    
std::size_t NodeOrderEventArgs_<NodeType>::newIndex() const
{
    return _newIndex;
}

template<typename NodeType>
bool NodeOrderEventArgs_<NodeType>::wasMovedForward() const
{
    return _oldIndex > _newIndex;
}

template<typename NodeType>
bool NodeOrderEventArgs_<NodeType>::wasMovedBackward() const
{
    return _newIndex > _oldIndex;
}

template<typename NodeType>
bool NodeOrderEventArgs_<NodeType>::isAtFront() const
{
    return _newIndex == 0;
}

template<typename NodeType>
bool NodeOrderEventArgs_<NodeType>::isAtBack() const
{
    return NodeEventArgs_<NodeType>::node()->numSiblings() == _newIndex;
}


} } // namespace ofx::DOM
