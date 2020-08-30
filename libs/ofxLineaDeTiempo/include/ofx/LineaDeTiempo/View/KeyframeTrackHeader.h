//
//  KeyframeTrackHeader.hpp
//  ofxGuiWidgetDOMintegration
//
//  Created by Roy Macdonald on 4/12/20.
//

#include "LineaDeTiempo/View/ofxGuiView.h"
#include "LineaDeTiempo/View/TrackHeader.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename ParamType>
class KeyframeTrackHeader
: public TrackHeader

{
public:

	KeyframeTrackHeader(ofParameter<ParamType> & param, const std::string& id, const ofRectangle& rect, BaseTrackView* track,  TrackGroupView* group, bool belongsToPanel);
	
	virtual ~KeyframeTrackHeader(){}
	
	
//	virtual void onDraw() const override
//	{
//		TrackHeader::onDraw();
//		ofDrawBitmapStringHighlight(ofToString(_gui->getHeight()), 20, 18 );
//
//	}
//	
protected:
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& ) override;

	ofxGuiView<ParamType> * _gui = nullptr;
	
	virtual float _getMinHeight() override;
	
	ofEventListener _ofxGuiHeightChangeListener;
	
	void _ofxGuiHeightChange( DOM::ShapeChangeEventArgs& );

	float _minimizedHeightFactor;
	
};
} } // ofx::LineaDeTiempo
