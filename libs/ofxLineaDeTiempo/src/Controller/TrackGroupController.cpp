//
//  TrackGroupController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//
//
#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/Utils/CollectionHelper.h"
//
namespace ofx {
namespace LineaDeTiempo {


TrackGroupController::TrackGroupController(const std::string& name, TrackGroupController * parent, TimeControl* timeControl)
: DOM::Node(name, parent)
, BaseHasTimeControl(timeControl, "TrackGroupController : " + name)
//,_parentGroup(parent)
//,BaseHasTracks<TrackController>()
//,BaseHasGroups<TrackGroupController>()
,BaseViewController<TrackGroupView>()
{
}

void TrackGroupController::generateView()
{
	if(getView()) return;
	
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p && p->getView())
	{
		
		setView(p->getView()->addGroup<TrackGroupView>(this));
			
	}
	generateChildrenViews(this);
	
}
void TrackGroupController::destroyView()
{
	
	if(getView() == nullptr) return;
	
	destroyChildrenViews(this);
	
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p && p->getView())
	{
		
		if(p->getView()->removeGroup(this))
		{
			ofLogError("TrackGroupController::destroyView") << "Could not remove group correctly";
		}
		
		setView(nullptr);
			
	}
}

bool TrackGroupController::removeTrack(TrackController* track)
{
	return CollectionHelper::_remove<TrackController, TrackGroupController>( track, this,   _tracksCollection);
}

bool TrackGroupController::removeGroup(TrackGroupController* group)
{
	return CollectionHelper::_remove<TrackGroupController, TrackGroupController>( group,this,   _groupsCollection);
}

TrackGroupController* TrackGroupController::add(ofParameterGroup& _parameters)
{
	auto group = addGroup<TrackGroupController>(_parameters.getName());
	
	if(group->getId() != _parameters.getName())
	{
		ofLogWarning("TracksPanelController::add") << "There is already another group named: \"" << _parameters.getName() << "\".\nRenamed to: \"" << group->getId() << "\"" ;
		_parameters.setName(group->getId());
	}
	
	
	
	for(std::size_t i = 0; i < _parameters.size(); i++){
		
		if(_parameters[i].isReadOnly()){
			ofLogVerbose("TracksPanelController::add") << "Not adding parameter \""<< _parameters[i].getName() << "\" as it is read-only, which does not make much sense adding to the timeline";
			continue;
		}
		
		string type = _parameters.getType(i);
		if(type == typeid(ofParameter <int32_t> ).name()){
			auto p = _parameters.getInt(i);
			group->add(p);
		}
		 else if(type == typeid(ofParameter <uint32_t> ).name()){
		 	auto p = _parameters.get<uint32_t>(i);
		 	group->add(p);
		 }
		 else if(type == typeid(ofParameter <int64_t> ).name()){
		 	auto p = _parameters.get<int64_t>(i);
		 	group->add(p);
		 }
		 else if(type == typeid(ofParameter <uint64_t> ).name()){
		 	auto p = _parameters.get<uint64_t>(i);
		 	group->add(p);
		 }
		 else if(type == typeid(ofParameter <int8_t> ).name()){
		 	auto p = _parameters.get<int8_t>(i);
		 	group->add(p);
		 }
		 else if(type == typeid(ofParameter <uint8_t> ).name()){
		 	auto p = _parameters.get<uint8_t>(i);
		 	group->add(p);
		 }
		 else if(type == typeid(ofParameter <int16_t> ).name()){
		 	auto p = _parameters.get<int16_t>(i);
		 	group->add(p);
		 }
		 else if(type == typeid(ofParameter <uint16_t> ).name()){
		 	auto p = _parameters.get<uint16_t>(i);
		 	group->add(p);
		 }
		 else if(type == typeid(ofParameter <size_t> ).name()){
		 	auto p = _parameters.get<size_t>(i);
		 	group->add(p);
		 }
		else if(type == typeid(ofParameter <float> ).name()){
			auto p = _parameters.getFloat(i);
			group->add(p);
		}
		// else if(type == typeid(ofParameter <double> ).name()){
		// 	auto p = _parameters.get<double>(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <bool> ).name()){
		// 	auto p = _parameters.getBool(i);
		// 	group->add(p);
		// }
			// else if(type == typeid(ofParameter <void> ).name()){
//			auto p = _parameters.getVoid(i);
//			group->add(p);
		// }
		// else if(type == typeid(ofParameter <ofVec2f> ).name()){
		// 	auto p = _parameters.get<ofVec2f>(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <ofVec3f> ).name()){
		// 	auto p = _parameters.get<ofVec3f>(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <ofVec4f> ).name()){
		// 	auto p = _parameters.get<ofVec4f>(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <glm::vec2> ).name()){
		// 	auto p = _parameters.get<glm::vec2>(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <glm::vec3> ).name()){
		// 	auto p = _parameters.get<glm::vec3>(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <glm::vec4> ).name()){
		// 	auto p = _parameters.get<glm::vec4>(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <ofColor> ).name()){
		// 	auto p = _parameters.getColor(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <ofShortColor> ).name()){
		// 	auto p = _parameters.getShortColor(i);
		// 	group->add(p);
		// }
		// else if(type == typeid(ofParameter <ofFloatColor> ).name()){
		// 	auto p = _parameters.getFloatColor(i);
		// 	group->add(p);
		// }
		else if(_parameters[i].valueType() == typeid(string).name()){
			ofLogVerbose("TracksPanelController::add") << "Not adding string parameter \""<< _parameters[i].getName() << "\" as it does not make much sense adding to the timeline";
//			auto p = _parameters.getString(i);
//			group->add(p);
			
		}
		else if(type == typeid(ofParameterGroup).name()){
			auto p = _parameters.getGroup(i);
			group->add(p);
		}
		else{
			ofLogWarning("TracksPanelController::add") << "no control for parameter of type " << type;
		}
	}
	return group;
}


} } // ofx::LineaDeTiempo

