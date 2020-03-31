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
: BaseController<TrackGroupView>(name, parent, timeControl)
//,_parentGroup(parent)

{
}

TrackGroupController::~TrackGroupController()
{
//	destroyView();
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
		
		if(! p->getView()->removeGroup(this ))
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

void TrackGroupController::fromJson(const ofJson& j)
{
	//	j["class"] = "TrackGroupController";
	setId(j["name"]);
	
	
	if(j.count("_groupsCollection")){
		auto g = j["_groupsCollection"];
		if(_groupsCollection.checkJson(g))
		{
			_makeFromJson(g);
		}
	}
	
	if(j.count("_tracksCollection")){
		auto t = j["_tracksCollection"];
		if(_tracksCollection.checkJson(t))
		{
			_makeFromJson(t);
		}
	}
}

ofJson TrackGroupController::toJson()
{
	ofJson j;
	j["class"] = "TrackGroupController";
	j["name"] = getId();
	//	j["view"] = bool(getView());
	j["_groupsCollection"] = _groupsCollection.toJson();
	j["_tracksCollection"] = _tracksCollection.toJson();
	return j;
}


void TrackGroupController::_makeFromJson(const ofJson& json)
{
	for(auto j: json["elements"])
	{
		if(	j.count("class") > 0 && j.count("name") > 0){
			
			auto clss = j["class"].get<std::string>();
			auto name = j["name"].get<std::string>();
			
			if(clss == "TrackGroupController")
			{
				TrackGroupController* g = getGroup(name);
				if(g){
					g->fromJson(j);
				}
				else
				{
					_addGroup(name)->fromJson(j);
				}
			}
			else if(clss == "KeyframeTrackController_")
			{
				if(j.count("_dataTypeName")){
					auto dataTypeName = j["_dataTypeName"].get<std::string>();
					TrackController* t = getTrack(name);
					if(t)
					{
						if(dataTypeName == t->getDataTypeName())
						{
							t->fromJson(j);
						}
						else
						{
							ofLogWarning("TrackGroupController::_makeFromJson") << "dataTypeNames differ " << dataTypeName << " != " <<  t->getDataTypeName();
						}
					}
					else
					{
						_addTrack(name, clss, dataTypeName)->fromJson(j);
					}
				}
			}
			else
			{
				ofLogWarning("TrackGroupController::_makeFromJson") << "unknown class:  " << clss;
			}
		}
		else
		{
			ofLogWarning("TrackGroupController::_makeFromJson") << " malformed json. does not have name or class objects";
		}
	}
}

TrackGroupController * TrackGroupController:: _addGroup( const std::string& groupName)
{
	return addGroup<TrackGroupController>(groupName);
}


TrackController* TrackGroupController:: _addTrack(const std::string& trackName, const std::string& typeName, const std::string& paramType)
{
	if("KeyframeTrackController_" == typeName)
	{
// 		if(typeid(ofRectangle).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofRectangle>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<char>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<char>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<unsigned char>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<unsigned char>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<short>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<short>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<unsigned short>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<unsigned short>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<int>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<int>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<unsigned int>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<unsigned int>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<long>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<long>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<unsigned long>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<unsigned long>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<float>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<float>>(trackName);
// 		}
// 		else 
// 		if(typeid(ofColor_<double>).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofColor_<double>>(trackName);
// 		}
// 		else 
// 		if(typeid(glm::vec2).name() == paramType)
// 		{
// 			return addKeyframeTrack<glm::vec2>(trackName);
// 		}
// 		else 
// 		if(typeid(glm::vec3).name() == paramType)
// 		{
// 			return addKeyframeTrack<glm::vec3>(trackName);
// 		}
// 		else 
// 		if(typeid(glm::vec4).name() == paramType)
// 		{
// 			return addKeyframeTrack<glm::vec4>(trackName);
// 		}
// 		else 
// 		if(typeid(glm::quat).name() == paramType)
// 		{
// 			return addKeyframeTrack<glm::quat>(trackName);
// 		}
// 		else 
// 		if(typeid(glm::mat4).name() == paramType)
// 		{
// 			return addKeyframeTrack<glm::mat4>(trackName);
// 		}
// 		else 
// 		if(typeid(ofVec2f).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofVec2f>(trackName);
// 		}
// 		else 
// 		if(typeid(ofVec3f).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofVec3f>(trackName);
// 		}
// 		else 
// 		if(typeid(ofVec4f).name() == paramType)
// 		{
// 			return addKeyframeTrack<ofVec4f>(trackName);
// 		}
// 		else 
// 		if(typeid(bool).name() == paramType)
// 		{
// 			return addKeyframeTrack<bool>(trackName);
// 		}
// 		else 
// 		if(typeid(void).name() == paramType)
// 		{
//			return addKeyframeTrack<void>(trackName);
// 		}
// 		else 
//		if(typeid(char).name() == paramType)
//		{
//			return addKeyframeTrack<char>(trackName);
//		}
//		else
//		if(typeid(unsigned char).name() == paramType)
//		{
//			return addKeyframeTrack<unsigned char>(trackName);
//		}
//		else
//		if(typeid(signed char).name() == paramType)
//		{
//			return addKeyframeTrack<signed char>(trackName);
//		}
//		else
//		if(typeid(short).name() == paramType)
//		{
//			return addKeyframeTrack<short>(trackName);
//		}
//		else
//		if(typeid(unsigned short).name() == paramType)
//		{
//			return addKeyframeTrack<unsigned short>(trackName);
//		}
//		else
		if(typeid(int).name() == paramType)
		{
			return addKeyframeTrack<int>(trackName);
		}
		else 
//		if(typeid(unsigned int).name() == paramType)
//		{
//			return addKeyframeTrack<unsigned int>(trackName);
//		}
//		else
//		if(typeid(long).name() == paramType)
//		{
//			return addKeyframeTrack<long>(trackName);
//		}
//		else
//		if(typeid(unsigned long).name() == paramType)
//		{
//			return addKeyframeTrack<unsigned long>(trackName);
//		}
//		else
//		if(typeid(long long).name() == paramType)
//		{
//			return addKeyframeTrack<long long>(trackName);
//		}
//		else
//		if(typeid(unsigned long long).name() == paramType)
//		{
//			return addKeyframeTrack<unsigned long long>(trackName);
//		}
//		else
		if(typeid(float).name() == paramType)
		{
			return addKeyframeTrack<float>(trackName);
		}
//		else
//		if(typeid(double).name() == paramType)
//		{
//			return addKeyframeTrack<double>(trackName);
//		}
//		else
//		if(typeid(long double).name() == paramType)
//		{
//			return addKeyframeTrack<long double>(trackName);
//		}
	}
	
	
	return nullptr;
}


bool TrackGroupController::removeGroup(const std::string& name)
{
	return removeGroup(_groupsCollection.at(name));
}

bool TrackGroupController::removeGroup(const size_t& index)
{
	return removeGroup(_groupsCollection.at(index));
}

TrackGroupController* TrackGroupController::getGroup(const std::string& name)
{
	return _groupsCollection.at(name);
}

const TrackGroupController* TrackGroupController::getGroup(const std::string& name) const
{
	return _groupsCollection.at(name);
}

TrackGroupController* TrackGroupController::getGroup(const size_t& index)
{
	return _groupsCollection.at(index);
}

const TrackGroupController* TrackGroupController::getGroup(const size_t& index)const
{
	return _groupsCollection.at(index);
}

const std::vector<TrackGroupController*>& TrackGroupController::getGroups()
{
	return _groupsCollection.getCollection();
}

const std::vector<const TrackGroupController*>& TrackGroupController::getGroups() const
{
	return _groupsCollection.getCollection();
}

size_t TrackGroupController::getNumGroups() const
{
	return _groupsCollection.size();
}



bool TrackGroupController::removeTrack(const std::string& name)
{
	return removeTrack(_tracksCollection.at(name));
}

bool TrackGroupController::removeTrack(const size_t& index)
{
	return removeTrack(_tracksCollection.at(index));
}

TrackController* TrackGroupController::getTrack(const std::string& name)
{
	return _tracksCollection.at(name);
}

const TrackController* TrackGroupController::getTrack(const std::string& name) const
{
	return _tracksCollection.at(name);
}

TrackController* TrackGroupController::getTrack(const size_t& index)
{
	return _tracksCollection.at(index);
}

const TrackController* TrackGroupController::getTrack(const size_t& index)const
{
	return _tracksCollection.at(index);
}

const std::vector<TrackController*>& TrackGroupController::getTracks()
{
	return _tracksCollection.getCollection();
}

const std::vector<const TrackController*>& TrackGroupController::getTracks() const
{
	return _tracksCollection.getCollection();
}

size_t TrackGroupController::getNumTracks() const
{
	return _tracksCollection.size();
}



} } // ofx::LineaDeTiempo

