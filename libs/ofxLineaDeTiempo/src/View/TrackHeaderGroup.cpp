//
//  TrackHeaderGroup.cpp
//  example-easing
//
//  Created by Roy Macdonald on 8/30/20.
//

#include "LineaDeTiempo/View/TrackHeaderGroup.h"

#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include "LineaDeTiempo/Utils/FontUtils.h"

namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------
TrackHeaderGroup::TrackHeaderGroup(const std::string& id,const ofRectangle& rect, TrackGroupView* group, bool belongsToPanel)
: TrackHeader(id, rect , group, group, belongsToPanel)
{
	
}


bool TrackHeaderGroup::removeTrackHeader(TrackHeader* header)
{
	
	if(header == nullptr)
	{
		ofLogError("TrackHeaderGroup::removeTrackHeader") << "header is nullptr";
		return false;
	}
	
	auto h = removeChild(header);
	if(h){
		size_t prevSize = _trackHeaders.size();
		ofRemove(_trackHeaders, [&](TrackHeader* t){return t == header;});
		if(prevSize == _trackHeaders.size()){
			ofLogError("TrackHeaderGroup::removeTrackHeader") << "not removed from trackHeaders vector";
			return false;
		}
		return true;
	}

	return false;
	
}


TrackHeaderGroup* TrackHeaderGroup::addGroupHeader(const std::string& id, TrackGroupView* group, bool belongsToPanel)
{
	auto g = addChild<TrackHeaderGroup>(id, ofRectangle(), group, belongsToPanel);
	_groupHeaders.push_back(g);
	return g;
}


bool TrackHeaderGroup::removeGroupHeader(TrackHeaderGroup * groupHeader)
{
	if(groupHeader == nullptr)
	{
		ofLogError("TrackHeaderGroup::removeGroupHeader") << "groupHeader is nullptr";
		return false;
	}
	
	auto h = removeChild(groupHeader);
	if(h){
		size_t prevSize = _groupHeaders.size();
		ofRemove(_groupHeaders, [&](TrackHeader* t){return t == groupHeader;});
		
		if(prevSize == _groupHeaders.size()){
			ofLogError("TrackHeaderGroup::removeGroupHeader") << "not removed from groupHeaders vector";
			return false;
		}
		return true;
	}

	return false;
}


} } // ofx::LineaDeTiempo

