//
//  Follower.cpp
//  example-easing
//
//  Created by Roy Macdonald on 8/30/20.
//

#include "Follower.h"
#include "ofLog.h"

namespace ofx {
namespace MUI {

Follower::Follower(DOM::Element* follower)
:_follower(follower)
{
	
}


void Follower::follow(DOM::Element* following, int followerType, int followMode)
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


void Follower::disableFollowing()
{
	_followingListener.unsubscribe();
}


void Follower::enableFollowing()
{
	if(_following)
	{
		_followingListener = _following->shapeChanged.newListener(this, &Follower::_followingShapeChanged);
	}
}


void Follower::mutuallyFollow(Follower* f0, int followerType0, int followMode0, int followerType1, int followMode1)
{
	
	if(f0)
	{
		f0->follow(this->_follower, followerType1, followMode1);
		f0->_mutuallyFollowing = this;
		this->follow(f0->_follower, followerType0, followMode0);
		this->_mutuallyFollowing = f0;
	}
}


void Follower::mutuallyFollow(Follower* f0, int followType, int followMode)
{
	mutuallyFollow(f0, followType, followMode, followType, followMode);
}


bool  Follower::isFollowingX()
{
	return (_type & FOLLOW_X) != 0;
}


bool  Follower::isFollowingY()
{
	return (_type & FOLLOW_Y) != 0;
}


bool  Follower::isFollowingWidth()
{
	return (_type & FOLLOW_WIDTH) != 0;
}


bool  Follower::isFollowingHeight()
{
	return (_type & FOLLOW_HEIGHT) != 0;
}


void Follower::_followingShapeChanged(DOM::ShapeChangeEventArgs& e)
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

} } // ofx::MUI
