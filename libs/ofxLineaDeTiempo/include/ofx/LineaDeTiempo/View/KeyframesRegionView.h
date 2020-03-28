//
//  KeyframesRegionView.hpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#pragma once
//#include "ofxMUI.h"
#include "LineaDeTiempo/View/KeyframeView.h"
#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/View/Selector.h"


namespace ofx {
namespace LineaDeTiempo {


class RegionController;

class TrackView;


class KeyframesRegionView
: public RegionView
, public Selector<KeyframeView>
{
public:
	KeyframesRegionView (TrackView* parentTrack, RegionController *controller);
	virtual ~KeyframesRegionView() = default;
		
	void onKeyframeDrag(KeyframeView* k, const glm::vec2& delta);
	
	void selectKeyframe(KeyframeView* k);
	void unselectKeyframe(KeyframeView* k);
    bool isKeyframeSelected(KeyframeView* k);
    void unselectAllKeyframes();
    void selectAllKeyframes();

	
	KeyframeView* addKeyframe(const glm::vec2& localPos);
	KeyframeView* addKeyframe(float value, uint64_t time);
	
	bool removeKeyframe(KeyframeView* k);
	
	void updateKeyframeSort();
	
	virtual void onDraw() const override;
	
	virtual void updateLayout() override;
	
	
	virtual const std::vector<KeyframeView*> & getCollection() const override;
	virtual std::vector<KeyframeView*> & getCollection() override;
	
	void onKeyboardEvent(DOM::KeyboardUIEventArgs& evt) ;
	
	
	ofEvent<glm::vec2> addKeyframeEvent;
	ofEvent<KeyframeView*> removeKeyframeEvent;
	

	
	
protected:

	virtual void _removeSelectedElements() override;
	

	bool _bIsMultiDim =  false;
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

	virtual void _onTimeRangeChange() override;
	

	std::vector<KeyframeView*> keyFrames;
	
	void _makeInterpolationLine();
	ofPolyline _interpolationLine;
	ofPolyline _inLine;
	ofPolyline _outLine;
private:
	
	
};


} } // ofx::LineaDeTiempo
