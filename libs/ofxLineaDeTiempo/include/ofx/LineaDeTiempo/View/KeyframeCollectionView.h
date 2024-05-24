//
//  KeyframeCollectionView.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/28/20.
//

//
#pragma once

#include "MUI/Widget.h"
#include "LineaDeTiempo/View/KeyframeView.h"
#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"

#include "LineaDeTiempo/View/Selector.h"

#include "ofPolyline.h"


namespace ofx {
namespace LineaDeTiempo {

class KeyframesRegionView;
class RegionController;
class TrackView;


struct AddKeyframeEventArgs
{
	AddKeyframeEventArgs(){}
	AddKeyframeEventArgs(float value, uint64_t _time, KeyframeCollectionView* _view)
	:normalizedValue(value)
	,time(_time)
	,view(_view)
	{}
	
	
	float normalizedValue = 0;
	uint64_t time = 0;
	KeyframeCollectionView* view = nullptr;
};

struct RemoveKeyframesEventArgs
{
	RemoveKeyframesEventArgs(){}
	RemoveKeyframesEventArgs(KeyframeCollectionView* _view)
	:view(_view)
	{}

	std::vector<KeyframeView*> keyframes;
	KeyframeCollectionView* view = nullptr;
};


class KeyframeCollectionView
: public MUI::Widget
, public BaseHasCollection<KeyframeView>
{
public:
	KeyframeCollectionView (const std::string & name, const ofRectangle& rect, KeyframesRegionView* parentRegion, Selector<KeyframeView>* selector, RegionController *controller);
	virtual ~KeyframeCollectionView() = default;
		
	void onKeyframeDrag(KeyframeView* k, const glm::vec2& delta);
	
	void selectKeyframe(KeyframeView* k);
	void unselectKeyframe(KeyframeView* k);
    bool isKeyframeSelected(KeyframeView* k);
    void unselectAllKeyframes();
    void selectAllKeyframes();

	
	KeyframeView* addKeyframe(uint64_t time);
	
	KeyframeView* addKeyframe(float value, uint64_t time);
	
	bool removeKeyframe(KeyframeView* k);
	
	void updateKeyframeSort();
	
	virtual void onDraw() const override;
	
	virtual void updateLayout() override;
	
	virtual const std::vector<KeyframeView*> & getCollection() const override;
	virtual std::vector<KeyframeView*> & getCollection() override;
	
	
	ofEvent<AddKeyframeEventArgs> addKeyframeEvent;
	ofEvent<RemoveKeyframesEventArgs> removeKeyframeEvent;
	
	TrackView* parentTrack();


	void onKeyboardEvent(DOM::KeyboardUIEventArgs& evt) ;
	
	float keyframePositionToValue(float pos);
	float keyframeValueToPosition(float value);

	
	
	virtual void removeElements(std::vector<KeyframeView*> & elementsToRemove) override;

	
	bool isParamTypeIsBool();
	bool isParamTypeIsVoid();
	
protected:
	
	
	bool _bParamTypeIsVoid = false;
	bool _bParamTypeIsBool = false;
	
	
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& ) override;
	
	
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

	
	KeyframesRegionView* _parentRegion = nullptr;
	
	std::vector<KeyframeView*> keyFrames;
	
	void _makeInterpolationLine();
	ofPolyline _interpolationLine;
	ofPolyline _inLine;
	ofPolyline _outLine;
	
	Selector<KeyframeView>* _selector = nullptr;
	
private:
	
	
};

} } // ofx::LineaDeTiempo
