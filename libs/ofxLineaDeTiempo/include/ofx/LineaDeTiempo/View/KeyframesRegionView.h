//
//  KeyframesRegionView.hpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#pragma once
//#include "ofxMUI.h"
#include "LineaDeTiempo/View/KeyFrameView.h"
#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/View/Selector.h"


namespace ofx {
namespace LineaDeTiempo {


class RegionController;

class TrackView;


class KeyframesRegionView
: public RegionView
, public Selector<KeyFrameView>
{
public:
	KeyframesRegionView (TrackView* parentTrack, RegionController *controller);
	virtual ~KeyframesRegionView() = default;
		
	void onKeyFrameDrag(KeyFrameView* k, const glm::vec2& delta);
	
	void selectKeyframe(KeyFrameView* k);
	void unselectKeyframe(KeyFrameView* k);
    bool isKeyframeSelected(KeyFrameView* k);
    void unselectAllKeyframes();
    void selectAllKeyframes();
//    void _setSelectedKeyframesFromRect(const ofRectangle& r, bool bAddToCurrentSelection);

	KeyFrameView* addKeyframe(const glm::vec2& k);
	bool removeKeyframe(KeyFrameView* k);
	
    void updateKeyframeSort();
	
	virtual void onDraw() const override;
	
	virtual void updateLayout() override;
	
	ofEvent<KeyFrameView*> keyframeAddedEvent;
	ofEvent<KeyFrameView*> keyframeRemovedEvent;
	
	
	virtual const std::vector<KeyFrameView*> & getCollection() const override;
	virtual std::vector<KeyFrameView*> & getCollection() override;
	
	void onKeyboardEvent(DOM::KeyboardUIEventArgs& evt) ;
	
protected:
	
	virtual void _removeSelectedElements() override;
	
//	virtual bool _sortSelectorElements() override;
	
//	ofEventListener selectorListener;
//	void _selectorRectChanged(ofRectangle& r);
//
	bool _bIsMultiDim =  false;
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

//	void _setSelectedKeyframesFromRect(const ofRectangle& r, bool bAddToCurrentSelection);
	
//	void _onPointerDown(DOM::PointerUIEventArgs& e);
//	void _onPointerUp(DOM::PointerUIEventArgs& e);

	std::vector<KeyFrameView*> keyFrames;
//	std::vector<KeyFrameView*> selectedKeyframes;

//    void updateSelectionRect(const glm::vec2& args);

//    ofRectangle selectionRect;
//	glm::vec2 selectionRectStart;
	
//	bool _isSelectingRect() const;
	
//	void
	
	
private:
	
	
	
	size_t _count = 0;
	
};


} } // ofx::LineaDeTiempo
