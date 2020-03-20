//
//  TracksPanel.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once
#include "MUI/ScrollablePanel.h"

//#include "LineaDeTiempo/BaseTypes/BaseHasTracks.h"

#include "LineaDeTiempo/View/Playhead.h"
//#include "LineaDeTiempo/View/Tracks.h"
//#include "LineaDeTiempo/View/TrackView.h"
//#include "LineaDeTiempo/View/KeyframesRegionView.h"

//#include "LineaDeTiempo/BaseTypes/BaseHasController.h"

#include "LineaDeTiempo/View/TrackGroupView.h"
//#include "LineaDeTiempo/Controller/TracksPanelController.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasHeader.h"

namespace ofx {
namespace LineaDeTiempo {



class TracksPanelController;
class TrackController;

class TracksPanel
: public TrackGroupView



{
public:
	TracksPanel(const std::string& id, DOM::Element* parentView, const ofRectangle& rect, TracksPanelController* controller);
	
	virtual ~TracksPanel() = default;


	virtual void updateLayout() override;
	
//	virtual void onDraw() const override;
	
	
	float timeToScreenPosition(uint64_t time) const;
	uint64_t  screenPositionToTime(float x) const;
	

	Playhead * _playhead = nullptr;
	
	TracksClippedView* getClippingView();
	const TracksClippedView* getClippingView()const;
	
	DOM::Element* getContainer();
	const DOM::Element* getContainer() const;
	
	void setup()
	{
		if(tracksView)
		{
			tracksView->setScrollH({0,1});
			tracksView->setScrollV({0,1});
		}
	}
protected:
	
	MUI::TracksScrollPanel* tracksView;
	MUI::ClippedView * headersView;
	
	virtual DOM::Element* _getTracksContainer() override;
	virtual DOM::Element* _getHeadersContainer() override;


	virtual void _updateContainers() override;


	ofEventListeners _tracksContainerListeners;
	
	
	void _updateHeadersFromTracks();

	
	
	void _tracksMoved(DOM::MoveEventArgs& e);
	void _tracksResized(DOM::ResizeEventArgs& e);
	
	
	
//	std::shared_ptr<LineaDeTiempo::TimeControl> _timeControl ;
	
	
	ofRectangle _makeHeadersViewRect();
	ofRectangle _makeTracksViewRect();
	
private:
	
	
	
	
};
} } // ofx::LineaDeTiempo
