//
//  Header.h
//  example-easing
//
//  Created by Roy Macdonald on 8/29/20.
//

#pragma once
#include "DOM/Element.h"
#include "ofLog.h"

namespace ofx {
namespace MUI {

enum FollowerType
{
	FOLLOW_NONE = 0,
	FOLLOW_X = 1,
	FOLLOW_Y = 2,
	FOLLOW_WIDTH = 4,
	FOLLOW_HEIGHT = 8,
	FOLLOW_ALL = 15
};

enum FollowMode
{
	///\brief Follows based on screen position
	FOLLOW_SCREEN,
	///\brief The Follower will follow the local position of the followed
	FOLLOW_LOCAL
	
};


/// This class will make one DOM::Element to follow anothers shape changes
class Follower
{
public:
	///\brief Constructor
	///\param follower the the follower element
	Follower(DOM::Element* follower)
	:_follower(follower)
	{}
	
	///\ Destructor
	virtual ~Follower(){}

	
	///\Brief set the follower element to follow the following element's shape changes
	///\param following the element that the follower should follow
	///\param type The type of the follower.
	///\param mode The following mode
	void follow(DOM::Element* following, int followerType, int followMode)
	{
		if(following == _follower)
		{
			ofLogError("ofxMUI::Follower") << ": follower and follwing can not be the same";
			return;
		}
		
		_following = following;
		_type = followerType;
		_mode = followMode;
		enableFollowing();
	}
	
	
	///\brief Disable following. This can be reenabled later
	void disableFollowing()
	{
		_followingListener.unsubscribe();
	}
	///\brief Enable following. This can get called at any time
	void enableFollowing()
	{
		if(_following)
		{
			_followingListener = _following->shapeChanged.newListener(this, &Follower::_followingShapeChanged);
		}
	}
	
	
	///\brief Make this follower to follow and be followed back.
	/// This takes into account the possible circular callback and avoids it to happen.
	///\param f0 the followed follower
	///\param followerType0 this' follower type.
	///\param followMode0 this' follower mode.
	///\param followerType1 The followed follower's type.
	///\param followMode1 The followed follower's mode.
	/// Not sure if it makes any sense to have different types and modes
	void mutuallyFollow(Follower* f0, int followerType0, int followMode0, int followerType1, int followMode1)
	{
		
		if(f0)
		{
			f0->follow(this->_follower, followerType1, followMode1);
			f0->_mutuallyFollowing = this;
			this->follow(f0->_follower, followerType0, followMode0);
			this->_mutuallyFollowing = f0;
		}
	}
	
	
	
	///\brief Make this follower to follow and be followed back.
	/// This takes into account the possible circular callback and avoids it to happen.
	///\param f0 the followed follower
	///\param followerType The followers type. The same will be used for both followers.
	///\param followMode The followers mode. The same will be used for both followers.
	/// Not sure if it makes any sense to have different types and modes
	void mutuallyFollow(Follower* f0, int followType, int followMode)
	{
		mutuallyFollow(f0, followType, followMode, followType, followMode);
	}
	
	
	
	
	bool  isFollowingX()
	{
		return (_type & FOLLOW_X) != 0;
	}
	bool  isFollowingY()
	{
		return (_type & FOLLOW_Y) != 0;
	}
	bool  isFollowingWidth()
	{
		return (_type & FOLLOW_WIDTH) != 0;
	}
	bool  isFollowingHeight()
	{
		return (_type & FOLLOW_HEIGHT) != 0;
	}
	
	
private:
	
	Follower * _mutuallyFollowing = nullptr;
	
	ofEventListener _followingListener;
	
	DOM::Element* _following = nullptr;
	
	DOM::Element* _follower = nullptr;
	
	int _type = FOLLOW_ALL;
	
	int _mode = FOLLOW_SCREEN;
	
	void _followingShapeChanged(DOM::ShapeChangeEventArgs& e)
	{
		if(_type == FOLLOW_NONE) return;
		if(!_follower || !_following) return;
		
		auto s = _follower->getShape();
		bool bUpdateShape = false;
		if( e.xChanged() && isFollowingX())
		{
			s.x = e.shape.x;
			bUpdateShape = true;
		}
		if( e.yChanged() && isFollowingY())
		{
			s.y = e.shape.y;
			bUpdateShape = true;
		}
		if( e.widthChanged() && isFollowingWidth())
		{
			s.width = e.shape.width;
			bUpdateShape = true;
		}
		if( e.heightChanged() && isFollowingHeight())
		{
			s.height = e.shape.height;
			bUpdateShape = true;
		}
		if(bUpdateShape)
		{
			if(_mode == FOLLOW_SCREEN)
			{
				auto p = _follower->screenToParent(_following->parentToScreen(s.getPosition()));
				if(isFollowingX()) s.x = p.x;
				if(isFollowingY()) s.y = p.y;
			}
			
			if(_mutuallyFollowing)
			{
				_mutuallyFollowing->disableFollowing();
			}
			
			_follower->setShape(s);
			
			if(_mutuallyFollowing)
			{
				_mutuallyFollowing->enableFollowing();
			}
		}
	}
	
	
};

} } // ofx::MUI
