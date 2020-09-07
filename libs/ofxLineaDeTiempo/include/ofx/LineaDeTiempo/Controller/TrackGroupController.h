//
//  TrackGroupController.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//

#pragma once
//#include "LineaDeTiempo/BaseTypes/BaseController.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/Utils/CollectionHelper.h"
#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"

#include "LineaDeTiempo/Controller/BaseController.h"

//#include "LineaDeTiempo/BaseTypes/BaseHasTimeControl.h"

#include "ofParameter.h"
#include "LineaDeTiempo/Controller/KeyframeTrackController.h"
#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"
#include "ofxGuiGroup.h"

namespace ofx {
namespace LineaDeTiempo {



class TrackGroupController
: public BaseController<TrackGroupView>
, public AbstractSerializable
{
public:
	
	
	TrackGroupController(const std::string& name, TrackGroupController * parent, TimeControl* timeControl);
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	virtual ~TrackGroupController();
	
	
	TrackGroupController* add(ofxGuiGroup& guiGroup);
	
	TrackGroupController* add(ofParameterGroup& paramGroup);
		
	template<typename DataType>
	KeyframeTrackController_<DataType>* add(ofParameter<DataType>& parameter);
	
	
	template<typename DataType>
	KeyframeTrackController_<DataType> * addTrack( ofParameter<DataType>& parameter);
	
	
	template<typename DataType>
	KeyframeTrackController_<DataType>* addTrack(const std::string& name = "");
	
	
	bool removeTrack(TrackController* track);
	
	
	
	TrackGroupController * addGroup( const std::string& groupName = "");
	
	
	
	bool removeGroup(TrackGroupController* group);
	
	bool removeGroup(const std::string& name);
	
	bool removeGroup(const size_t& index);
	
	TrackGroupController* getGroup(const std::string& name);
	
	const TrackGroupController* getGroup(const std::string& name) const;
	
	TrackGroupController* getGroup(const size_t& index);
	
	const TrackGroupController* getGroup(const size_t& index)const;
	
	const std::vector<TrackGroupController*>& getGroups();
	
	const std::vector<const TrackGroupController*>& getGroups() const;
	
	size_t getNumGroups() const;
	
	
	
	bool removeTrack(const std::string& name);
	
	bool removeTrack(const size_t& index);
	
	TrackController* getTrack(const std::string& name);
	
	const TrackController* getTrack(const std::string& name) const;
	
	TrackController* getTrack(const size_t& index);
	
	const TrackController* getTrack(const size_t& index)const;
	
	const std::vector<TrackController*>& getTracks();
	
	const std::vector<const TrackController*>& getTracks() const;
	
	size_t getNumTracks() const;
	
	
	
	
	virtual void fromJson(const ofJson& j) override;
	
	virtual ofJson toJson() override;
	
	
protected:
	void _makeFromJson(const ofJson& j);
	
	TrackController* _addTrack(const std::string& trackName, const std::string& paramType);
	

	NamedConstPointerCollection<TrackGroupController> _groupsCollection;
	NamedConstPointerCollection<TrackController> _tracksCollection;
	
	
private:
	
	
};


template<typename DataType>
KeyframeTrackController_<DataType>* TrackGroupController::add(ofParameter<DataType>& parameter)
{
	return addTrack<DataType> (parameter);
}


template<typename DataType>
KeyframeTrackController_<DataType>* TrackGroupController::addTrack(const std::string& trackName)
{
	
	auto uniqueName = _tracksCollection.makeUniqueName(trackName, "Track");
	
	auto t = CollectionHelper::
	_add< KeyframeTrackController_<DataType>, TrackGroupController, TrackController>
	
	( _tracksCollection, this, uniqueName, this, getTimeControl());
	
	if(hasView())
	{
		t->generateView();
	}
	
	
	return t;
}

template<typename DataType>
KeyframeTrackController_<DataType> * TrackGroupController::addTrack( ofParameter<DataType>& parameter)
{
	
	auto uniqueName = _tracksCollection.makeUniqueName(parameter.getName(), "Parameter");
	
	if(uniqueName != parameter.getName())
	{
		ofLogWarning("TrackGroupController::addTrack") << "There is already another track named: \"" << parameter.getName() << "\".\nRenamed to: \"" << uniqueName << "\"" ;
		parameter.setName(uniqueName);
	}
	
	auto t = CollectionHelper::
	_add< KeyframeTrackController_<DataType>, TrackGroupController, TrackController>
	
	( _tracksCollection, this, parameter, this, getTimeControl());
	
	t->addRegion(uniqueName);
	
	if(hasView())
	{
		t->generateView();
	}
	
	return t;
	
	
}



} } // ofx::LineaDeTiempo
