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


class KeyframeCollectionView
: public MUI::Widget
, public BaseHasCollection<KeyframeView>
{
public:
	KeyframeCollectionView (const std::string & name, float width, float height, KeyframesRegionView* parentRegion, Selector<KeyframeView>* selector, RegionController *controller);
	virtual ~KeyframeCollectionView() = default;
		
	void onKeyframeDrag(KeyframeView* k, const glm::vec2& delta);
	
	void selectKeyframe(KeyframeView* k);
	void unselectKeyframe(KeyframeView* k);
    bool isKeyframeSelected(KeyframeView* k);
    void unselectAllKeyframes();
    void selectAllKeyframes();

	
//	KeyframeView* addKeyframe(const glm::vec2& screenPos);
	KeyframeView* addKeyframe(float value, uint64_t time);
	
	bool removeKeyframe(KeyframeView* k);
	
	void updateKeyframeSort();
	
	virtual void onDraw() const override;
	
	virtual void updateLayout() override;
	
//
	virtual const std::vector<KeyframeView*> & getCollection() const override;
	virtual std::vector<KeyframeView*> & getCollection() override;
	
//	void onKeyboardEvent(DOM::KeyboardUIEventArgs& evt) ;
	
	
	ofEvent<glm::vec2> addKeyframeEvent;
	ofEvent<KeyframeView*> removeKeyframeEvent;
	
	TrackView* parentTrack();


	void onKeyboardEvent(DOM::KeyboardUIEventArgs& evt) ;
	
	
	
protected:

	void _parentResized(DOM::ResizeEventArgs &);
	
//	Selector<KeyframeView> _selector;
	
	virtual void removeElements(std::vector<KeyframeView*> & elementsToRemove) override;
	

//	bool _bIsMultiDim =  false;
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

//	virtual void _onTimeRangeChange() override;
	
	ofEventListener _parentListener;
	
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
