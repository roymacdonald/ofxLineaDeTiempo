//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Label.h"
#include "ofx/MUI/AutoReziseContainer.h"

namespace ofx {
namespace MUI {


class Panel
: public DOM::Element
{
public:
    
	Panel(const std::string& id, const ofRectangle& rect);
	
    /// \brief Destroy the Panel.
	virtual ~Panel() = default;

    // void onDraw() const override;

	
	

	virtual void updateLayout() override;
	AutoReziseContainer * container = nullptr;
	
	
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
	
};


} } // ofx::MUI
