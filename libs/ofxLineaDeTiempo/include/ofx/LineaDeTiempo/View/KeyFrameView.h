//
//  KeyFrame.hpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#pragma once
#include "ofx/MUI/Widget.h"
#include "LineaDeTiempo/BaseTypes/BaseSelectable.h"
namespace ofx {
namespace LineaDeTiempo {

class KeyframesRegionView;
class KeyFrameView
: public MUI::Widget
, public BaseSelectable
{
public:
	friend class KeyframesRegionView;
	KeyFrameView(const std::string& id, const glm::vec2& pos);
	virtual ~KeyFrameView(){}
	

	virtual void onDraw() const override;
	
	
	virtual void setSelected(bool select) override;
//	bool isSelected();
		
	
	static float defaultKeyFrameSize;
	
	
	float getValue() const;
	uint64_t getTime() const;
protected:
	uint64_t _time = 0;
	float _value =0; //normalized

	void _updatePosition();
	void _updateValue();
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	
    virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

//	bool bSelected = false;
	
	bool _moved = false;
};


} } // ofx::LineaDeTiempo
