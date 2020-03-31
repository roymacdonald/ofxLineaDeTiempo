//
//  KeyframeRegionController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#pragma once
#include "LineaDeTiempo/Controller/RegionController.h"
#include "LineaDeTiempo/Controller/KeyframeController.h"
#include "LineaDeTiempo/View/KeyframesRegionView.h"
#include "LineaDeTiempo/View/KeyframeView.h"

#include "LineaDeTiempo/Data/KeyframedData.h"
#include <unordered_map>
namespace ofx {
namespace LineaDeTiempo {

template<typename DataType>
class KeyframeTrackController_;

class TrackController;


template<typename DataType>
class KeyframeRegionController_
: public RegionController


{
public:

	KeyframeRegionController_( const std::string& name, TrackController* parentTrack, TimeControl* timeControl);
	KeyframeRegionController_( const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack, TimeControl* timeControl);
	
	virtual ~KeyframeRegionController_() = default;
	
	virtual void generateView() override;
	virtual void destroyView() override;

	
	KeyframeController<DataType>* addKeyframe(DataType value, uint64_t time);
	
	bool removeKeyframe(KeyframeController<DataType>* keyframe);
	
	void removeAllKeyframes();
	
	
	const KeyframedData_<DataType>& getKeyframedData() const;
	
	virtual void update(uint64_t& t) override;
	
	
	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;
	
	
protected:

	friend class KeyframeTrackController_< DataType >;
	friend class KeyframeController<DataType>;

	
	ofEventListener addKeyframeListener;
	void _addKeyframeAtScreenPos(glm::vec2& pos);
	
	ofEventListener removeKeyframeListener;
	void _removeKeyframe(KeyframeView*& v);
	
	KeyframedData_<DataType> _keyframedData;

	std::vector<KeyframeController<DataType>* > _keyframes;
	std::unordered_map<KeyframeView*, KeyframeController<DataType>*>_keyframesViewMap;
	
	
	KeyframeTrackController_<DataType>* _parentTrack = nullptr;
	
private:
	
	
	KeyframesRegionView* _keyframesRegionView = nullptr;
	
};


} } // ofx::LineaDeTiempo
