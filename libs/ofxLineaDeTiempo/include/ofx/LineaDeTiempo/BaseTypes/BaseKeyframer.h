//
//  BaseKeyframer.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/23/20.
//

namespace ofx {
namespace LineaDeTiempo {


class BaseKeyframer{
public:
	void enableKeyframing()
	{
		setEnableKeyframing(true);
	}
	
	void disableKeyframing()
	{
		setEnableKeyframing(false);
	}
	
	bool isKeyFramingEnabled() const
	{
		return _bKeyframingEnabled;
	}
	
	ofEvent<bool> keyframingEnableEvent;

	void setEnableKeyframing(bool e)
	{
		if(_bKeyframingEnabled != e){
			_bKeyframingEnabled = e;
			_bKeyframingEnabledProxy = _bKeyframingEnabled;
			ofNotifyEvent(keyframingEnableEvent, _bKeyframingEnabledProxy, this);
		}
	}
private:
	
	bool _bKeyframingEnabled = true;
	bool _bKeyframingEnabledProxy = true;
	

	
};

}}// ofx::LineaDeTiempo
