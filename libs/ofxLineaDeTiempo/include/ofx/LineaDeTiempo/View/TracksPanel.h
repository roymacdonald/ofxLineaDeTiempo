//
//  TracksPanel.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once
#include "MUI/ScrollablePanel.h"
#include "MUI/BaseClasses.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasTracks.h"
#include "LineaDeTiempo/BaseTypes/BaseHasTracks.h"

#include "LineaDeTiempo/View/Playhead.h"
#include "LineaDeTiempo/View/Tracks.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/View/KeyFrames.h"

#include "LineaDeTiempo/BaseTypes/BaseHasController.h"

#include "LineaDeTiempo/Controller/TracksPanelController.h"

namespace ofx {
namespace LineaDeTiempo {



class TracksController;


class TracksPanel
: public BaseHasTracks<BaseTrack>
, public BaseHasController<TracksPanelController>
, public MUI::Widget
, public BaseHasLayout


{
public:
	TracksPanel(const std::string& id, const ofRectangle& rect, TracksController* controller);//,  std::shared_ptr<LineaDeTiempo::TimeControl> timeControl );
	virtual ~TracksPanel() = default;

//	BaseTrack* addTrack();
//	KeyFramesTrack* addKeyframesTrack(const std::string& name);

	template< template<typename> class TrackViewType, typename RegionViewType >
	TrackViewType<RegionViewType>* addTrack(const std::string& name, bool bCreateFullTrackRegion);
	
	
	virtual bool removeTrack(BaseTrack* track) override ;


	float getTrackHeaderWidth();
	void setTrackHeaderWidth(float w);


	MUI::ClippedView * headersView;
	
	MUI::TracksScrollPanel* tracksView;
	
	
	virtual void updateLayout() override;
	
	virtual void onDraw() const override;
	
	
	float timeToScreenPosition(uint64_t time) const;
	uint64_t  screenPositionToTime(float x) const;
	

	Playhead * _playhead = nullptr;
	
protected:
	
	
	                                                                   
	

	float _trackHeaderWidth = 200;


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
