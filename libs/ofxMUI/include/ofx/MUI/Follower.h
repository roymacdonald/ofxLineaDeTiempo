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
	Follower(DOM::Element* follower);
	
	
	///\ Destructor
	virtual ~Follower(){}

	
	///\Brief set the follower element to follow the following element's shape changes
	///\param following the element that the follower should follow
	///\param type The type of the follower.
	///\param mode The following mode
	void follow(DOM::Element* following, int followerType, int followMode);
	
	
	///\brief Disable following. This can be reenabled later
	void disableFollowing();


	///\brief Enable following. This can get called at any time
	void enableFollowing();
	
	
	///\brief Make this follower to follow and be followed back.
	/// This takes into account the possible circular callback and avoids it to happen.
	///\param f0 the followed follower
	///\param followerType0 this' follower type.
	///\param followMode0 this' follower mode.
	///\param followerType1 The followed follower's type.
	///\param followMode1 The followed follower's mode.
	/// Not sure if it makes any sense to have different types and modes
	void mutuallyFollow(Follower* f0, int followerType0, int followMode0, int followerType1, int followMode1);
	
	
	///\brief Make this follower to follow and be followed back.
	/// This takes into account the possible circular callback and avoids it to happen.
	///\param f0 the followed follower
	///\param followerType The followers type. The same will be used for both followers.
	///\param followMode The followers mode. The same will be used for both followers.
	/// Not sure if it makes any sense to have different types and modes
	void mutuallyFollow(Follower* f0, int followType, int followMode);
	
	
	///\brief Is this follower following changes in the X coordinate
	///\returns true if this follower is following changes in the X coordinate of the followed object
	bool  isFollowingX();

	
	///\brief Is this follower following changes in the Y coordinate
	///\returns true if this follower is following changes in the Y coordinate of the followed object
	bool  isFollowingY();

	
	///\brief Is this follower following changes in  width
	///\returns true if this follower is following changes of the followed object's width
	bool  isFollowingWidth();

	
	///\brief Is this follower following changes in  height
	///\returns true if this follower is following changes of the followed object's height
	bool  isFollowingHeight();
	
	
private:
	
	Follower * _mutuallyFollowing = nullptr;
	
	ofEventListener _followingListener;
	
	DOM::Element* _following = nullptr;
	
	DOM::Element* _follower = nullptr;
	
	int _type = FOLLOW_ALL;
	
	int _mode = FOLLOW_SCREEN;

	
	///\ Function called when the followed elements' shape changes
	void _followingShapeChanged(DOM::ShapeChangeEventArgs& e);
	
	
};

} } // ofx::MUI
