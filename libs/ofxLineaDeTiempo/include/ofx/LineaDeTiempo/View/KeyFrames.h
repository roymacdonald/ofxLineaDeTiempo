//
//  KeyFrames.hpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#pragma once
//#include "ofxMUI.h"
#include "LineaDeTiempo/View/KeyFrame.h"
#include "LineaDeTiempo/View/RegionView.h"

class TrackView;

namespace ofx {
namespace LineaDeTiempo {

class KeyFrames: public RegionView{
public:
	KeyFrames (TrackView* parentTrack, RegionController *controller);
	virtual ~KeyFrames() = default;
		
	void selectKeyframe(KeyFrame* k);
	void unselectKeyframe(KeyFrame* k);
    bool isKeyframeSelected(KeyFrame* k);
	void onKeyFrameDrag(KeyFrame* k, const glm::vec2& delta);

    void unselectAllKeyframes();
    void selectAllKeyframes();

    

	KeyFrame* addKeyframe(const glm::vec2& k);
	bool removeKeyframe(KeyFrame* k);
    void updateKeyframeSort();
	
	virtual void onDraw() const override;
	
	virtual void updateLayout() override;
	
	ofEvent<KeyFrame*> keyframeAddedEvent;
	ofEvent<KeyFrame*> keyframeRemovedEvent;
	
protected:
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

	void _setSelectedKeyframesFromRect(const ofRectangle& r, bool bAddToCurrentSelection);
	
	void _onPointerDown(DOM::PointerUIEventArgs& e);
	void _onPointerUp(DOM::PointerUIEventArgs& e);

	std::vector<KeyFrame*> keyFrames;
	std::vector<KeyFrame*> selectedKeyFrames;

    void updateSelectionRect(const glm::vec2& args);

    ofRectangle selectionRect;
	glm::vec2 selectionRectStart;
	
	bool _isSelectingRect() const;
	
	
private:
	size_t _count = 0;
	
};


} } // ofx::LineaDeTiempo
