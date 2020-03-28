//
//  KeyframeTrackController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#pragma once

#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/KeyframeRegionController.h"
#include "LineaDeTiempo/Data/KeyframedData.h"

#include "ofParameter.h"

namespace ofx {
namespace LineaDeTiempo {

//parent type forward declaration
class TrackGroupController;

template <typename DataType>
class KeyframeTrackController_
: public TrackController
{
public:
		
	
	KeyframeTrackController_(ofParameter<DataType>& parameter, TrackGroupController* parent, TimeControl* timeControl);
	
	KeyframeTrackController_(const std::string& name, TrackGroupController* parent, TimeControl* timeControl);
	
	virtual ~KeyframeTrackController_() = default;
	
	KeyframeRegionController_<DataType>* addRegion( const std::string& regionName, const ofRange64u& timeRange);
	
	bool removeRegion(KeyframeRegionController_<DataType>* region);
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	
	ofParameter<DataType>& getParameter();
	const ofParameter<DataType>& getParameter() const;
	
	
	float getNormalizedValue(const DataType& val);
	DataType getUnnormalizedValue(float val);

protected:
	
	ofParameter<DataType> _parameter;
	
	ofEventListener _paramListener;
	
	void _paramChanged(DataType& );
	
	//	// this is set to true when the param is being modified by the manager, so it does not generate an infinite loop because of the cyclic callbacks.
	bool _bModifyingParam = false;

private:
	
	
};


} } // ofx::LineaDeTiempo

