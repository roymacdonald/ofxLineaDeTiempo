//
//  Scrollbar.hpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/5/20.
//

#pragma once

//#include "ofxMUI.h"
#include "ZoomHandle.h"
#include "ScrollHandle.h"

namespace ofx {
namespace MUI {


/// \brief Scrollbar
///

template<typename HandleType, typename ScrollData>
class Scrollbar_: public Widget
{
public:
    /// \brief Create a Scrollbar with the given parameters.
    /// \param id The Widget's id string.
    /// \param orientation The orientation of the .
    /// \param mode The DragMode of the Scrollbar.
	Scrollbar_(const std::string& id, DOM::Orientation orientation);
	
	static_assert(std::is_base_of<BaseScrollHandle<ScrollData>, HandleType>(), "Wrong handle types");
    /// \brief Destroy the Scrollbar.
	virtual ~Scrollbar_(){}

//    virtual void onDraw() const override;
	virtual void onUpdate()override;
	  

    /// \returns the current orientation.
    DOM::Orientation getOrientation() const;

    /// \brief Set the Orientation of the slider.
    /// \param the Desired Orientation.
    void setOrientation(DOM::Orientation orientation);


	
	ofEvent<ScrollData> & handleChangedEvent(){
		return _handle->handleChangeEvent;
	}
	
	
	
	void updateLayout(const ofRectangle& rect);
	
	void setValue(const ScrollData& val );
	
	const ScrollData& getValue() const ;

	///\brief will move the scroll handle by amt
	///\param amt amount to scroll by. Normalized
	///\return true if it was able to move the scroll handle
	bool scroll(float amt);
	
	static float scrollSpeed;
	
	
protected:
	
	bool bUpdateLayout = true;//work around so the scroller layouts initially. I might be doing something wrong because I need this
	
	bool _onScrollEvent(ofMouseEventArgs & e);
	
	
	void _onResize(DOM::ResizeEventArgs&);
	void _onMove(DOM::MoveEventArgs&);
	
	HandleType* _handle = nullptr;

private:
	ofEventListeners shapeChangeListeners;
	ofEventListener scrollListener;

	ScrollData currentScrollData;
};

typedef Scrollbar_<ScrollHandle, float> Scrollbar;
typedef Scrollbar_<ZoomHandle, ofRange> ZoomScrollbar;

} } // ofx::MUI



