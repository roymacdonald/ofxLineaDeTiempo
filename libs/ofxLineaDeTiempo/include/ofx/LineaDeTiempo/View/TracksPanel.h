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
//#include "LineaDeTiempo/View/KeyFrames.h"

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
	TracksPanel(const std::string& id, const ofRectangle& rect, TracksPanelController* controller);
	
	virtual ~TracksPanel() = default;


	virtual void updateLayout() override;
	
//	virtual void onDraw() const override;
	
	
	float timeToScreenPosition(uint64_t time) const;
	uint64_t  screenPositionToTime(float x) const;
	

	Playhead * _playhead = nullptr;
	
	TracksClippedView* getClippingView();
	const TracksClippedView* getClippingView()const;
protected:
	
	MUI::TracksScrollPanel* tracksView;
	MUI::ClippedView * headersView;
	
	virtual DOM::Element* _getTracksContainer() override;
	virtual DOM::Element* _getHeadersContainer() override;


	virtual void _updateContainers() override;


	ofEventListeners _tracksContainerListeners;
	
	void _tracksMoved(DOM::MoveEventArgs& e);
	void _tracksResized(DOM::ResizeEventArgs& e);
	
	void _updateHeadersFromTracks();

	
//	std::shared_ptr<LineaDeTiempo::TimeControl> _timeControl ;
	
	
	ofRectangle _makeHeadersViewRect();
	ofRectangle _makeTracksViewRect();
	
private:
	
	
	
	
};
} } // ofx::LineaDeTiempo
