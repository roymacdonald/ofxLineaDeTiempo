//
//  ofxGuiView.hpp
//  ofxGuiWidgetDOMintegration
//
//  Created by Roy Macdonald on 4/12/20.
//


#include "ofx/MUI/Widget.h"
#include "ofxGui.h"


namespace ofx {
namespace LineaDeTiempo {

class TrackHeader;

template <typename ParamType>
class ofxGuiView
: public MUI::Widget

{
public:
	ofxGuiView(ofParameter<ParamType>& param, float width, TrackHeader* trackHeader);
	
	virtual ~ofxGuiView() = default;

	
	virtual void onDraw() const override;

	virtual void onUpdate() override;
	
//	ofxGuiGroup & getOfxGui();
//	const ofxGuiGroup & getOfxGui() const;
//
protected:
	
	
	void _makeGui(ofParameter<ParamType>& param, float width);
	
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& ) override;
	
    virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;


//	mutable ofxGuiGroup _gui;

	std::unique_ptr<ofxBaseGui> _gui = nullptr;
	
	ofRectangle _ofxGuiShape;
	bool _ignoreOfxGuiShapeChange = false;
	void _updateShapeFromOfxGui();
	
//	float _minimizedHeightFactor = 1;

	TrackHeader* _trackHeader = nullptr;

	
	
	bool _bOfxGuiIsMinimizable = false;

	
};


} } // ofx::LineaDeTiempo
