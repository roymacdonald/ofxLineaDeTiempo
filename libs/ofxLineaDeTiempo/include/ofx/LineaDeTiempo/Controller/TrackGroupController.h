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

#include "LineaDeTiempo/BaseTypes/BaseHasTimeControl.h"

#include "ofParameter.h"
#include "LineaDeTiempo/Controller/KeyframeTrackController.h"


namespace ofx {
namespace LineaDeTiempo {



class TrackGroupController
:public DOM::Node
, public BaseHasTimeControl
, public BaseViewController<TrackGroupView>
{
public:
	
	
	TrackGroupController(const std::string& name, TrackGroupController * parent, TimeControl* timeControl);
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	virtual ~TrackGroupController() = default;
	
	TrackGroupController* add(ofParameterGroup& paramGroup);
	
	
	template<typename DataType>
	KeyframeTrackController_<DataType>* add(ofParameter<DataType>& parameter);

	
	template<typename DataType>
	KeyframeTrackController_<DataType> * addTrack( ofParameter<DataType>& parameter);

	
	template<typename NewTrackControllerType>
	NewTrackControllerType * addTrack( const std::string& trackName = "");
	
	
	template<typename DataType>
	KeyframeTrackController_<DataType>* addKeyframeTrack(const std::string& name);
	
	
	bool removeTrack(TrackController* track);
	
	
	template<typename NewTrackControllerType>
	NewTrackControllerType * addGroup( const std::string& groupName = "");
	
	bool removeGroup(TrackGroupController* group);
	
	bool removeGroup(const std::string& name)
	{
		return removeGroup(_groupsCollection.at(name));
	}
	
	bool removeGroup(const size_t& index)
	{
		return removeGroup(_groupsCollection.at(index));
	}
	
	TrackGroupController* getGroup(const std::string& name)
	{
		return _groupsCollection.at(name);
	}
	
	const TrackGroupController* getGroup(const std::string& name) const
	{
		return _groupsCollection.at(name);
	}
	
	TrackGroupController* getGroup(const size_t& index)
	{
		return _groupsCollection.at(index);
	}
	
	const TrackGroupController* getGroup(const size_t& index)const
	{
		return _groupsCollection.at(index);
	}
	
	const std::vector<TrackGroupController*>& getGroups()
	{
		return _groupsCollection.getCollection();
	}
	
	const std::vector<const TrackGroupController*>& getGroups() const
	{
		return _groupsCollection.getCollection();
	}
	
	size_t getNumGroups() const
	{
		return _groupsCollection.size();
	}
	
	
	
	bool removeTrack(const std::string& name)
	{
		return removeTrack(_tracksCollection.at(name));
	}
	
	bool removeTrack(const size_t& index)
	{
		return removeTrack(_tracksCollection.at(index));
	}
	
	TrackController* getTrack(const std::string& name)
	{
		return _tracksCollection.at(name);
	}
	
	const TrackController* getTrack(const std::string& name) const
	{
		return _tracksCollection.at(name);
	}
	
	TrackController* getTrack(const size_t& index)
	{
		return _tracksCollection.at(index);
	}
	
	const TrackController* getTrack(const size_t& index)const
	{
		return _tracksCollection.at(index);
	}
	
	const std::vector<TrackController*>& getTracks()
	{
		return _tracksCollection.getCollection();
	}
	
	const std::vector<const TrackController*>& getTracks() const
	{
		return _tracksCollection.getCollection();
	}
	
	size_t getNumTracks() const
	{
		return _tracksCollection.size();
	}
	
	using BaseHasTimeControl::getTimeControl;
	
	using BaseViewController<TrackGroupView>::getView;
	using BaseViewController<TrackGroupView>::setView;
	
	
protected:
	
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
KeyframeTrackController_<DataType> * TrackGroupController::addTrack( ofParameter<DataType>& parameter)
{
	
	auto uniqueName = _tracksCollection.makeUniqueName(parameter.getName(), "Parameter");
	
	if(uniqueName != parameter.getName())
	{
		ofLogWarning("TrackGroupController::addTrack") << "There is already another track named: \"" << parameter.getName() << "\".\nRenamed to: \"" << uniqueName << "\"" ;
		parameter.setName(uniqueName);
	}
	
	return CollectionHelper::
	_add< KeyframeTrackController_<DataType>, TrackGroupController, TrackController>
	
	( _tracksCollection, this, parameter, this, getTimeControl());
	
}


template<typename NewTrackControllerType>
NewTrackControllerType * TrackGroupController::addTrack( const std::string& trackName)
{
	
	auto uniqueName = _tracksCollection.makeUniqueName(trackName, "Track");
	
	return CollectionHelper::
	_add< NewTrackControllerType, TrackGroupController, TrackController>
	
	( _tracksCollection, this, uniqueName, this, getTimeControl());
	
}

template<typename DataType>
KeyframeTrackController_<DataType>* TrackGroupController::addKeyframeTrack(const std::string& name)
{
	return addTrack<KeyframeTrackController_<DataType>> (name);
}

template<typename NewTrackControllerType>
NewTrackControllerType * TrackGroupController::addGroup( const std::string& groupName )
{
	auto uniqueName = _groupsCollection.makeUniqueName(groupName, "Group");
	
	return CollectionHelper::
	_add< NewTrackControllerType, TrackGroupController, TrackGroupController >
	
	( _groupsCollection,  this, uniqueName, this, getTimeControl());
	
}



} } // ofx::LineaDeTiempo
