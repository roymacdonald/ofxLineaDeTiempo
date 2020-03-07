//
//  TracksPanel.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once
//#include "ofxMUI.h"
#include "Tracks.h"
#include "TrackHeader.h"
#include "ClippedView.h"
#include "ScrollablePanel.h"
#include "TimeControl.h"
#include "BaseClasses.h"
#include "Playhead.h"

namespace ofx {
namespace LineaDeTiempo {


struct TrackAndHeader{

	TrackAndHeader(TrackHeader* _header, BaseTrack* _track):
	header(_header),
	track(_track)
	{
		
	}
				   
	TrackHeader* header = nullptr;
	BaseTrack* track = nullptr;
	
};

class TracksPanel: public MUI::Widget, public BaseHasLayout
{
public:
	TracksPanel(const std::string& id, const ofRectangle& rect,  std::shared_ptr<LineaDeTiempo::TimeControl> timeControl );
	~TracksPanel(){}

//	TrackAndHeader* addTrack();
	TrackAndHeader* addKeyframesTrack(const std::string& name);

	template<typename RegionType>
	TrackAndHeader* addTrack(const std::string& name, bool bCreateFullTrackRegion);
	
	
	TrackAndHeader* getTrackByIndex(size_t index);
//	TrackAndHeader* getTrackByName(const std::string& name);

	bool removeTrack(TrackAndHeader* track);
	bool removeTrackByIndex(size_t index);
//	bool removeTrackByName(const std::string& name);

	size_t getNumTracks();


//	const std::vector<TrackAndHeader*>& getTracks() const;
//	std::vector<TrackAndHeader*> & getTracks();


	float getTrackHeaderWidth();
	void setTrackHeaderWidth(float w);


	MUI::ClippedView * headersView;
	
	MUI::TracksScrollPanel* tracksView;
	
	
	virtual void updateLayout() override;
	
	virtual void onDraw() const override;
	
	
//	ofRectangle timeRangeToRect(const ofRange64u& t) const;
//	float timeToLocalPosition(const uint64_t& t) const;
	
//	uint64_t localPositionToTime(float x) const;
	
	float timeToScreenPosition(uint64_t time) const;
	uint64_t  screenPositionToTime(float x) const;
	

	Playhead * _playhead = nullptr;
	
protected:
	
	
	                                                                   
	std::vector<std::unique_ptr<TrackAndHeader>> _trackCollection;




	float _trackHeaderWidth = 200;


	ofEventListeners _tracksContainerListeners;
	
	void _tracksMoved(DOM::MoveEventArgs& e);
	void _tracksResized(DOM::ResizeEventArgs& e);
	
	void _updateHeadersFromTracks();

	
	std::shared_ptr<LineaDeTiempo::TimeControl> _timeControl ;
	
	
	ofRectangle _makeHeadersViewRect();
	ofRectangle _makeTracksViewRect();
	
	
};
} } // ofx::LineaDeTiempo
