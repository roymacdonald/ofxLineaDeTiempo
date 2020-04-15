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
	destroyView();
}


void TrackGroupController::generateView()
{
	if(getView()) return;
	
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p && p->getView())
	{
		
		setView(p->getView()->addGroup(this));
		
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

TrackGroupController* TrackGroupController::add(ofxGuiGroup& guiGroup)
{
	return add(guiGroup.getParameter().castGroup());
}

TrackGroupController* TrackGroupController::add(ofParameterGroup& _parameters)
{

	auto group = addGroup(_parameters.getName());

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
			 if(type == typeid(ofParameter <int32_t> ).name())      { auto p = _parameters.getInt(i);group->add(p);}
		else if(type == typeid(ofParameter <uint32_t> ).name())     { auto p = _parameters.get<uint32_t>(i);group->add(p);}
		else if(type == typeid(ofParameter <int64_t> ).name())      { auto p = _parameters.get<int64_t>(i);group->add(p);}
		else if(type == typeid(ofParameter <uint64_t> ).name())     { auto p = _parameters.get<uint64_t>(i);group->add(p);}
		else if(type == typeid(ofParameter <int8_t> ).name())       { auto p = _parameters.get<int8_t>(i);group->add(p);}
		else if(type == typeid(ofParameter <uint8_t> ).name())      { auto p = _parameters.get<uint8_t>(i);group->add(p);}
		else if(type == typeid(ofParameter <int16_t> ).name())      { auto p = _parameters.get<int16_t>(i);group->add(p);}
		else if(type == typeid(ofParameter <uint16_t> ).name())     { auto p = _parameters.get<uint16_t>(i);group->add(p);}
		else if(type == typeid(ofParameter <size_t> ).name())       { auto p = _parameters.get<size_t>(i);group->add(p);}
		else if(type == typeid(ofParameter <float> ).name())        { auto p = _parameters.getFloat(i);group->add(p);}
		else if(type == typeid(ofParameter <double> ).name())       { auto p = _parameters.get<double>(i);group->add(p);}
		else if(type == typeid(ofParameter <bool> ).name())         { auto p = _parameters.getBool(i);group->add(p);}
//		else if(type == typeid(ofParameter <void> ).name())         { auto p = _parameters.getVoid(i);group->add(p);}
//		else if(type == typeid(ofParameter <ofVec2f> ).name())      { auto p = _parameters.get<ofVec2f>(i);group->add(p);}
//		else if(type == typeid(ofParameter <ofVec3f> ).name())      { auto p = _parameters.get<ofVec3f>(i);group->add(p);}
//		else if(type == typeid(ofParameter <ofVec4f> ).name())      { auto p = _parameters.get<ofVec4f>(i);group->add(p);}
		else if(type == typeid(ofParameter <glm::vec2> ).name())    { auto p = _parameters.get<glm::vec2>(i);group->add(p);}
		else if(type == typeid(ofParameter <glm::vec3> ).name())    { auto p = _parameters.get<glm::vec3>(i);group->add(p);}
		else if(type == typeid(ofParameter <glm::vec4> ).name())    { auto p = _parameters.get<glm::vec4>(i);group->add(p);}
		else if(type == typeid(ofParameter <ofColor> ).name())      { auto p = _parameters.getColor(i);group->add(p);}
		else if(type == typeid(ofParameter <ofShortColor> ).name()) { auto p = _parameters.getShortColor(i);group->add(p);}
		else if(type == typeid(ofParameter <ofFloatColor> ).name()) { auto p = _parameters.getFloatColor(i);group->add(p);}
		else if(_parameters[i].valueType() == typeid(string).name()){
			ofLogVerbose("TracksPanelController::add") << "Not adding string parameter \""<< _parameters[i].getName() << "\" as it does not make much sense adding to the timeline";
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
					addGroup(name);
					//}
//					_addGroup(name)->fromJson(j);
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
						_addTrack(name, dataTypeName)->fromJson(j);
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

//TrackGroupController * TrackGroupController:: _addGroup( const std::string& groupName)
//{
//	return addGroup<TrackGroupController>(groupName);
//}


TrackController* TrackGroupController:: _addTrack(const std::string& trackName, const std::string& paramType)
{
	
//		     if(typeid(              ofRectangle).name() == paramType){ return addKeyframeTrack<              ofRectangle> (trackName); }
//		else
//			if(typeid(            ofColor_<char>).name() == paramType){ return addTrack<           ofColor_<char>> (trackName); }
//		else if(typeid(  ofColor_<unsigned char>).name() == paramType){ return addTrack<  ofColor_<unsigned char>> (trackName); }
//		else if(typeid(          ofColor_<short>).name() == paramType){ return addTrack<          ofColor_<short>> (trackName); }
//		else if(typeid( ofColor_<unsigned short>).name() == paramType){ return addTrack< ofColor_<unsigned short>> (trackName); }
//		else if(typeid(            ofColor_<int>).name() == paramType){ return addTrack<            ofColor_<int>> (trackName); }
//		else if(typeid(   ofColor_<unsigned int>).name() == paramType){ return addTrack<   ofColor_<unsigned int>> (trackName); }
//		else if(typeid(           ofColor_<long>).name() == paramType){ return addTrack<           ofColor_<long>> (trackName); }
//		else if(typeid(  ofColor_<unsigned long>).name() == paramType){ return addTrack<  ofColor_<unsigned long>> (trackName); }
//		else if(typeid(          ofColor_<float>).name() == paramType){ return addTrack<          ofColor_<float>> (trackName); }
//		else if(typeid(         ofColor_<double>).name() == paramType){ return addTrack<         ofColor_<double>> (trackName); }
			 if(typeid(                  ofColor).name() == paramType){ return addTrack<  	              ofColor> (trackName); }
		else if(typeid(             ofFloatColor).name() == paramType){ return addTrack<			 ofFloatColor> (trackName); }
		else if(typeid(             ofShortColor).name() == paramType){ return addTrack<			 ofShortColor> (trackName); }
		else if(typeid(                glm::vec2).name() == paramType){ return addTrack<                glm::vec2> (trackName); }
		else if(typeid(                glm::vec3).name() == paramType){ return addTrack<                glm::vec3> (trackName); }
		else if(typeid(                glm::vec4).name() == paramType){ return addTrack<                glm::vec4> (trackName); }
//		else if(typeid(                glm::quat).name() == paramType){ return addTrack<                glm::quat> (trackName); }
//		else if(typeid(                glm::mat4).name() == paramType){ return addTrack<                glm::mat4> (trackName); }
//		else if(typeid(                  ofVec2f).name() == paramType){ return addTrack<                  ofVec2f> (trackName); }
//		else if(typeid(                  ofVec3f).name() == paramType){ return addTrack<                  ofVec3f> (trackName); }
//		else if(typeid(                  ofVec4f).name() == paramType){ return addTrack<                  ofVec4f> (trackName); }
		else if(typeid(                     bool).name() == paramType){ return addTrack<                     bool> (trackName); }
//		else if(typeid(                     void).name() == paramType){ return addTrack<                     void> (trackName); }
		// else if(typeid(                     char).name() == paramType){ return addTrack<                     char> (trackName); }
		// else if(typeid(            unsigned char).name() == paramType){ return addTrack<            unsigned char> (trackName); }
		// else if(typeid(              signed char).name() == paramType){ return addTrack<              signed char> (trackName); }
		// else if(typeid(                    short).name() == paramType){ return addTrack<                    short> (trackName); }
		// else if(typeid(           unsigned short).name() == paramType){ return addTrack<           unsigned short> (trackName); }
		// else if(typeid(                      int).name() == paramType){ return addTrack<                      int> (trackName); }
		// else if(typeid(             unsigned int).name() == paramType){ return addTrack<             unsigned int> (trackName); }
		// else if(typeid(                     long).name() == paramType){ return addTrack<                     long> (trackName); }
		// else if(typeid(            unsigned long).name() == paramType){ return addTrack<            unsigned long> (trackName); }
		// else if(typeid(                long long).name() == paramType){ return addTrack<                long long> (trackName); }
		// else if(typeid(       unsigned long long).name() == paramType){ return addTrack<       unsigned long long> (trackName); }
		// else if(typeid(                    float).name() == paramType){ return addTrack<                    float> (trackName); }
		// else if(typeid(                   double).name() == paramType){ return addTrack<                   double> (trackName); }
//		else if(typeid(              long double).name() == paramType){ return addTrack<              long double> (trackName); }
	

		else if(typeid(                   int8_t).name() == paramType){ return addTrack<                   int8_t> (trackName); }
		else if(typeid(                  uint8_t).name() == paramType){ return addTrack<                  uint8_t> (trackName); }
		else if(typeid(                  int16_t).name() == paramType){ return addTrack<                  int16_t> (trackName); }
		else if(typeid(                 uint16_t).name() == paramType){ return addTrack<                 uint16_t> (trackName); }
		else if(typeid(                  int32_t).name() == paramType){ return addTrack<                  int32_t> (trackName); }
		else if(typeid(                 uint32_t).name() == paramType){ return addTrack<                 uint32_t> (trackName); }
		else if(typeid(                  int64_t).name() == paramType){ return addTrack<                  int64_t> (trackName); }
		else if(typeid(                 uint64_t).name() == paramType){ return addTrack<                 uint64_t> (trackName); }
		else if(typeid(                    float).name() == paramType){ return addTrack<                    float> (trackName); }
		else if(typeid(                   double).name() == paramType){ return addTrack<                   double> (trackName); }
		else if(typeid(                   size_t).name() == paramType){ return addTrack<                   size_t> (trackName); }
	// typename std::conditional<std::is_same<uint32_t, size_t>::value || std::is_same<uint64_t, size_t>::value, bool, size_t>::type>;



	
	return nullptr;
}

TrackGroupController * TrackGroupController::addGroup( const std::string& groupName )
{
	auto uniqueName = _groupsCollection.makeUniqueName(groupName, "Group");
	
	return CollectionHelper::
	_add< TrackGroupController, TrackGroupController, TrackGroupController >
	
	( _groupsCollection,  this, uniqueName, this, getTimeControl());
	
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

