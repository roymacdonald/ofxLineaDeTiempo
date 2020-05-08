//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Label.h"

namespace ofx {
namespace MUI {


template<typename ContainerType>
class Panel
: public DOM::Element
{
public:
	
	static_assert(std::is_base_of<DOM::Element, ContainerType>(), "ContainerType must be an DOM::Element or derived from DOM::Element.");
	
	template <typename... Args>
	Panel(const std::string& id, const ofRectangle& rect, Args&&... args);
	
    
	virtual ~Panel() = default;

    

	virtual void updateLayout() override;
	ContainerType * container = nullptr;
	
	
	void setCornerHandleSize(float cornerHandleSize );
	float getCornerHandleSize() const;
	
	void setResizable(bool resizable);
	bool isResizable() const;
	
	
	void setEnableHeaderHandle(bool enable);
	bool hasHeaderHandle() const;
	
	
	void setHeaderLabel(const std::string& label);
	const std::string& getHeaderLabel() const;
	
protected:
	Widget * _cornerHandle = nullptr;
	Label *  _headerHandle = nullptr;
	
private:
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& e) override;
	
	bool _ignoreCornerHandleChange = false;
	bool _ignoreHeaderHandleChange = false;
	
	void _setHeaderHandleShape();
	void _setCornerHandleViewRect();
	
	ofEventListener _cornerHandleListener;
	ofEventListener _headerHandleListener;
	
	
    /// \brief True if the Panel can be resized.
    bool _resizeable = false;
	bool _bUsingHandles = false;
	
	void _cornerHandleChanged(DOM::ShapeChangeEventArgs&);
	void _headerHandleChanged(DOM::ShapeChangeEventArgs&);


	float _cornerHandleSize = 20;
	
	void _addCornerHandle();
	void _removeCornerHandle();
	
	void _addHeaderHandle();
	void _removeHeaderHandle();

	
	std::string _headerLabel = "";
	
	void _updateContainerShape();
	
	
};
template<typename T>
template <typename... Args>
Panel<T>::Panel(const std::string& id, const ofRectangle& rect, Args&&... args)
: DOM::Element(id, rect)
{
	container = addChild<T>(id+ "_container", ofRectangle(0, 0, rect.width, rect.height), std::forward<Args>(args)...);
}



} } // ofx::MUI
