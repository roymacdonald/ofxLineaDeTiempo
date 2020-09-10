//
//  TrackHeaderGroup.h
//  example-easing
//
//  Created by Roy Macdonald on 8/29/20.
//

#pragma once
#include "LineaDeTiempo/View/TrackHeader.h"

namespace ofx {
namespace LineaDeTiempo {


class TrackHeaderGroup
: public TrackHeader

{
public:
	
	
	TrackHeaderGroup(const std::string& id, const ofRectangle& rect, TrackGroupView* group, bool belongsToPanel);
	
	virtual ~TrackHeaderGroup(){}
	
	template< typename HeaderType, typename... Args>
	HeaderType* addTrackHeader(Args&&... args);
    
	
	bool removeTrackHeader(TrackHeader* header);
	
	
	TrackHeaderGroup* addGroupHeader(const std::string& id, TrackGroupView* group, bool belongsToPanel);
	
	
	bool removeGroupHeader(TrackHeaderGroup * groupHeader);

		
protected:
	
	std::vector<TrackHeaderGroup*> _groupHeaders;
	std::vector<TrackHeader*> _trackHeaders;
	
	
};



template< typename HeaderType, typename... Args>
HeaderType* TrackHeaderGroup::addTrackHeader(Args&&... args)
{
	auto h = addChild<HeaderType>(std::forward<Args>(args)...);
	_trackHeaders.push_back(h);
	return h;
}


} } // ofx::LineaDeTiempo
