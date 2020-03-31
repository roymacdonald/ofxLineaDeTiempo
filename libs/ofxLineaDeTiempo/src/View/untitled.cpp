#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"

, public AbstractSerializable

virtual void fromJson(const ofJson& j) override;
virtual ofJson toJson() override;


void ::fromJson(const ofJson& j)
{


}

ofJson ::toJson()
{
	ofJson j;
	j["class"] = "TrackGroupController";
	j["name"] = getId();
	j["view"] = bool(getView());
	

	j["keyframe_type"] = std::string(typeid(T).name());
	j["keyframes"] = nlohmann::json::array();
	for(auto& d: _data){
		if(d) j["keyframes"].emplace_back(*(d.get())) ;
	}
	j["num_keyframes"] = j["keyframes"].size();
	

	return j;
}
