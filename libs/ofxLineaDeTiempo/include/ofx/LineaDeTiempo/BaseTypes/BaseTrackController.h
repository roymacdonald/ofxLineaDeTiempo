//
//  BaseTrackController.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//

#pragma once

//#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"
#include "LineaDeTiempo/BaseTypes/BaseHasParent.h"
#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
//#include "LineaDeTiempo/BaseTypes/AbstractHasRegions.h"

//#include "LineaDeTiempo/Controller/TrackRegionController.h"
//#include "LineaDeTiempo/BaseTypes/BaseTrackController.h"
//#include "LineaDeTiempo/View/TrackRegionView.h"
//#include "LineaDeTiempo/View/Track.h"
//#include "ofRange.h"


#include <utility>
#include <type_traits>

namespace ofx {
namespace LineaDeTiempo {

class BaseTrackGroupController;

class BaseTrackController
:public BaseHasParent<BaseTrackGroupController>
,public BaseHasName
//,public BaseViewController<BaseTrack>
{
public:
	BaseTrackController(const std::string& name, BaseTrackGroupController* parent);
	~BaseTrackController() = default;
	
	
};

}} //ofx::LineaDeTiempo
