//
//  KeyFrame.hpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#pragma once
#include "ofx/MUI/Widget.h"

namespace ofx {
namespace LineaDeTiempo {

class KeyframesRegionView;
class KeyFrame: public MUI::Widget{
public:
	friend class KeyframesRegionView;
	KeyFrame(const std::string& id, const glm::vec2& pos);
	virtual ~KeyFrame(){}
	

	virtual void onDraw() const override;
	
	
	void setSelected(bool select);
	bool isSelected();
		
	
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

	bool bSelected = false;
	
	bool _moved = false;
};


} } // ofx::LineaDeTiempo
