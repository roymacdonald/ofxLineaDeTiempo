//
//  Keyframe.hpp
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
class KeyframeCollectionView;


class KeyframeView
: public MUI::Widget
, public BaseSelectable
{
private:
	
	
public:
	
	friend class KeyframesRegionView;
	friend class KeyframeCollectionView;

	
	KeyframeView(const std::string& id, float value, uint64_t time,  KeyframeCollectionView * parentView, bool paramTypeIsVoid);
	
	
	virtual ~KeyframeView(){}
	

	virtual void onDraw() const override;
	
	
	static float positionToValue(float pos, KeyframeView * k);
	
	static float valueToPosition(float value, KeyframeView * k);
	
	virtual bool isSelected() const override;
	
	virtual void setSelected(bool selected) override;
	
	virtual void setSelectedNoEvents(bool selected) override;
	
	
	float getValue() const;
	uint64_t getTime() const;
	
	ofEvent<float> valueChangedEvent;
	ofEvent<uint64_t> timeChangedEvent;
	
	bool isParamTypeVoid() const;
protected:
	KeyframeCollectionView * _parentView = nullptr;

	bool _bParamTypeIsVoid = false;
	
	uint64_t _time = 0;
	float _value =0; //normalized

	void _updatePosition();
	void _updateValue();
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	
    virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

private:
	bool _moved = false;
	
	bool _isSelected = false;

	
	
};

} } // ofx::LineaDeTiempo
