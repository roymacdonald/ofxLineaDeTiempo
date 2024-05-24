
//  KeyframeTrackController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#pragma once

#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/KeyframeRegionController.h"
#include "LineaDeTiempo/Data/KeyframedData.h"

#include "LineaDeTiempo/Utils/ofxTypeTraits.h"


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
	
	virtual ~KeyframeTrackController_();

	
	virtual void fromJson(const ofJson& j) override;
	
	virtual ofJson toJson() override;

	
	KeyframeRegionController_<DataType>* addRegion( const std::string& regionName, const ofRange64u& timeRange);
	
	KeyframeRegionController_<DataType>* addRegion( const std::string& regionName);
	


	ofParameter<DataType>& getParameter();
	
	const ofParameter<DataType>& getParameter() const;
	
	virtual void generateView() override;

protected:
	

	void _setup();
	
	
	virtual void _addRegionFromJson(const std::string& name, ofJson j) override;
	
	ofParameter<DataType> _parameter;
	
	ofEventListener _paramListener;
	
	//	// this is set to true when the param is being modified by the manager, so it does not generate an infinite loop because of the cyclic callbacks.
//	bool _bModifyingParam = false;

private:
	
	
};


} } // ofx::LineaDeTiempo

