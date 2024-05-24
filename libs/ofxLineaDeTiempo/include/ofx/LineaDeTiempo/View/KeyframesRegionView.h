//
//  KeyframesRegionView.hpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#pragma once

#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/View/KeyframeView.h"
#include "LineaDeTiempo/View/Selector.h"
#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"
#include "LineaDeTiempo/View/KeyframeCollectionView.h"

namespace ofx {
namespace LineaDeTiempo {



class KeyframesRegionView
: public RegionView
{
public:
	KeyframesRegionView (TrackView* parentTrack, RegionController *controller, shared_ptr<MUI::Styles> regionStyles);
	virtual ~KeyframesRegionView() = default;
			
	KeyframeView* addKeyframe(float value, uint64_t time, size_t viewIndex);

	bool removeKeyframe(KeyframeView* k, size_t viewIndex);

	
	virtual void onDraw() const override;
	
	
	virtual void updateLayout() override;
	
	
	Selector<KeyframeView>& getSelector();
	const Selector<KeyframeView >& getSelector() const;

	const std::vector<KeyframeCollectionView *>& getViews();
	const std::vector<KeyframeCollectionView *>& getViews() const;
	
	
protected:

	float _getCollectionViewHeight() const;
	
	ofRectangle _allViewsRect;
	
	std::vector<KeyframeCollectionView *> _views;
	
	Selector<KeyframeView> _selector;
		
	
		
	RegionController * _controller = nullptr;
	
	
};


} } // ofx::LineaDeTiempo
