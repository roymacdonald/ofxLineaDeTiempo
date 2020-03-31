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
			
	KeyframeView* addKeyframe(float value, uint64_t time);

	bool removeKeyframe(KeyframeView* k);

	
	virtual void onDraw() const override;
		
	Selector<KeyframeView>& getSelector();
	const Selector<KeyframeView>& getSelector() const;

	KeyframeCollectionView* getCollectionView() {return _collectionView;}
	
protected:

	KeyframeCollectionView* _collectionView;
	
	Selector<KeyframeView> _selector;
		
	
	
		
};


} } // ofx::LineaDeTiempo
