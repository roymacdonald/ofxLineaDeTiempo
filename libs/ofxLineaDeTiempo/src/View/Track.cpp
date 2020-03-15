//
//  Track.cpp
//
//  Created by Roy Macdonald on 2/18/20.
//

#include "Track.h"
#include "Tracks.h"
#include "MUI/Utils.h"
#include "MUI/Styles.h"
//#include "KeyFrames.h"
#include "TrackHeaderView.h"

namespace ofx {
namespace LineaDeTiempo {

const float BaseTrack::initialHeight = 150;
ofColor BaseTrack::backgroundColor = ofColor(80);
ofColor BaseTrack::edgeColor = ofColor(120);


//---------------------------------------------------------------------------------------------------------------------
BaseTrack::BaseTrack(const std::string& id, const std::string& viewTypeName, TrackController* controller)
:_viewTypeName(viewTypeName)
,DOM::Element(id, 0, 0, initialHeight, initialHeight)
,BaseHasController<TrackController>(controller)
,AbstractHasRegions<TrackRegion, false_type>()

{
	_regionsStyle = make_shared<MUI::Styles>();
}
//---------------------------------------------------------------------------------------------------------------------
float BaseTrack::getHeightFactor(){
	return _heightFactor;
}
//---------------------------------------------------------------------------------------------------------------------
void BaseTrack::setHeightFactor(float factor){
	_heightFactor = factor;
}
//---------------------------------------------------------------------------------------------------------------------
float BaseTrack::timeToScreenPosition(uint64_t time) const
{
	return localToScreen({timeToLocalPosition(time),0}).x;
}
//---------------------------------------------------------------------------------------------------------------------
uint64_t BaseTrack::screenPositionToTime(float x) const
{
	return localPositionToTime(screenToLocal({x,0}).x);
}

//---------------------------------------------------------------------------------------------------------------------
uint64_t BaseTrack::localPositionToTime(float x) const
{
//	if(_timeControl)
//	{
		return MUI::Math::lerp(x, 0, getWidth(), 0, getTimeControl().getTotalTime());
//	}
//	ofLogError("BaseTrack::timeRangeToLocalPosition") << "_timeControl is null. returning 0";
//	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
float BaseTrack::timeToLocalPosition(const uint64_t& t)  const
{
	
//	if(_timeControl)
//	{
		return MUI::Math::lerp(t, 0, getTimeControl().getTotalTime(), 0, getWidth());
//	}
//	ofLogError("BaseTrack::timeRangeToLocalPosition") << "_timeControl is null. returning 0";
//	return 0;
}
//---------------------------------------------------------------------------------------------------------------------
ofRectangle BaseTrack::timeRangeToRect(const ofRange64u& t) const
{
	
	ofRectangle r (timeToLocalPosition(t.min), 0,timeToLocalPosition(t.max), getHeight());
//	std::cout << "BaseTrack::timeRangeToRect" << _regions.size() << "  :  " << getShape() << " - "<< r <<"\n";
	r.width -= r.x;
	return r;
	
}
//---------------------------------------------------------------------------------------------------------------------
void BaseTrack::onDraw() const
{
//	ofPushStyle();
	ofFill();
	ofSetColor(backgroundColor);
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofNoFill();
	ofSetColor(edgeColor);
	ofDrawRectangle(0, 0, getWidth(), getHeight());
	
}
//---------------------------------------------------------------------------------------------------------------------
void BaseTrack::setColor(const ofColor& color)
{
	_color = color;
	
	_regionsStyle->setColor(_color, MUI::Styles::ROLE_BACKGROUND);
	
}
//---------------------------------------------------------------------------------------------------------------------
const ofColor& BaseTrack::getColor()
{
	return _color;
}

//---------------------------------------------------------------------------------------------------------------------

bool BaseTrack::removeRegion( TrackRegion* region)
{
	
	if(region == nullptr) return false;
	
	
	
	auto tr = this->removeChild(region);
	
	
	removeElement(region);
	
	
	return true;

}

//---------------------------------------------------------------------------------------------------------------------
template<typename R>
R* BaseTrack::addRegion( const ofRange64u & timeRange, TrackRegionController * controller){

	return addRegion<R>("Region", timeRange, controller);
}
//---------------------------------------------------------------------------------------------------------------------
template<typename R>
R* BaseTrack::addRegion(std::string name, const ofRange64u & timeRange, TrackRegionController * controller)
{
	
	static_assert(std::is_base_of< TrackRegion, R>::value,
					  "RegionType must inherit from ofx::LineaDeTiempo::TrackRegion");
	
	
	
	auto  r = addChild<R>(name, this, timeRange, controller);

	addElement(r);


	r->setStyles(_regionsStyle);
	
	
	r->updateRectFromTimeRange();
	

	return r;
	
}


//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
template<typename R>
Track_<R>::Track_(const std::string& id, TrackController* controller):
BaseTrack(id, typeid(R).name(), controller)
{

	clear();
}
//
////---------------------------------------------------------------------------------------------------------------------
//template<typename R>
//R* Track_<R>::getRegionByIndex(size_t index)
//{
//	if(index < _regions.size()){
//		return _regions[index];
//	}
//	return nullptr;
//}
////---------------------------------------------------------------------------------------------------------------------
//template<typename R>
//R* Track_<R>::getRegionByName(const std::string& name)
//{
//	if(_regionsNameMap.count(name)){
//		return _regionsNameMap[name];
//	}
//	return nullptr;
//}

////---------------------------------------------------------------------------------------------------------------------
//template<typename R>
//bool Track_<R>::removeRegionByIndex(size_t index)
//{
//	return removeRegion(getRegionByIndex(index));
//}
////---------------------------------------------------------------------------------------------------------------------
//template<typename R>
//bool Track_<R>::removeRegionByName(const std::string& name)
//{
//	return removeRegion(getRegionByName(name));
//}
////---------------------------------------------------------------------------------------------------------------------
//template<typename R>
//size_t Track_<R>::getNumRegions()
//{
//	return _regions.size();
//}
////---------------------------------------------------------------------------------------------------------------------
//template<typename R>
//const std::vector<R*>& Track_<R>::getRegions() const
//{
//	return _regions;
//}//---------------------------------------------------------------------------------------------------------------------
//template<typename R>
//std::vector<R*>& Track_<R>::getRegions()
//{
//	return _regions;
//}
//---------------------------------------------------------------------------------------------------------------------
template<typename R>
void Track_<R>::updateLayout()
{
	
	for(auto r: children())
	{
		
		if(r)
		{
			r->updateLayout();
			
		}
	}
}
//template class Track_<KeyFrames>;

} } // ofx::LineaDeTiempo
