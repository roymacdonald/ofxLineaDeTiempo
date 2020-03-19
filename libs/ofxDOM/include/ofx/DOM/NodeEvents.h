//
//  NodeEvents.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//
#pragma once


//#include <string>
//#include <type_traits>
//#include <utility>
//#include <ctime>
#include "ofEvents.h" 
//#include "ofx/PointerEvents.h"
//#include "ofx/DOM/Exceptions.h"
//#include "ofx/DOM/Types.h"


namespace ofx {
namespace DOM {

class Node;

class NodeEventArgs
{
public:
	
    /// \brief Construct the NodeEventArgs.
    /// \param node The node associated with this Node event.
    NodeEventArgs(Node* node);

    /// \brief Destroy the NodeEventArgs.
    virtual ~NodeEventArgs();

    /// \returns a pointer to the node or nullptr if not available.
    Node* node();
    
    /// \returns a pointer to the node or nullptr if not available.
    const Node* node() const;

protected:
    /// \brief A pointer to the node or nullptr if not available.
    Node* _node = nullptr;
	

};


class NodeOrderEventArgs: public NodeEventArgs
{
public:
	
	
    /// \brief Create an NodeOrderEventArgs.
    /// \param node The node associated with this Node order event.
    /// \param oldIndex old index before the Node order event.
    /// \param newIndex The new index after the Node order event.
    NodeOrderEventArgs(Node* node,
                          std::size_t oldIndex,
                          std::size_t newIndex);

    /// \brief Destroys the NodeOrderEventArgs.
    virtual ~NodeOrderEventArgs();

    /// \returns the old index before the Node order event.
    std::size_t oldIndex() const;

    /// \returns the new index after the Node order event.
    std::size_t newIndex() const;

    /// \returns true if the Node was moved forward.
    bool wasMovedForward() const;

    /// \returns true if the Node was moved backward.
    bool wasMovedBackward() const;

    /// \returns true if the Node is at the front.
    bool isAtFront() const;

    /// \returns true if the Node is at the back.
    bool isAtBack() const;

protected:
    /// \brief The old index before the Node order event.
    std::size_t _oldIndex = 0;

    /// \brief The new index after the Node order event.
    std::size_t _newIndex = 0;

};



} } // namespace ofx::DOM
