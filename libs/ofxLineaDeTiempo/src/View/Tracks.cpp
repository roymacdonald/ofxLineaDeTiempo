//
//  TrackRegion.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#include "Tracks.h"

namespace ofx {
namespace LineaDeTiempo {

TracksClippedView::TracksClippedView(const std::string& id, const ofRectangle& rect):
MUI::ClippedView(id, rect)
{

	_zoom[0] = {0,1};
	_zoom[1] = {0,1};
	
	_updateTracksWidth();
}

//---------------------------------------------------------------------
void TracksClippedView::setZoom(const std::vector<ofRange>& zooms){
	if(zooms.size() != 2){
		ofLogError("Tracks::setZoom")<< "the passed vector's size must be 2";
		return;
	}
	for(int i = 0; i < zooms.size(); i++){
		_zoom[i] = zooms[i];
		MUI::keepRangeMinSpan(_zoom[i], _minZoom[i], {0,1});

	}
	updateLayout();
	
}
//---------------------------------------------------------------------
void TracksClippedView::setZoom(int index, const ofRange& zoom){
	if(index < 2){
		_zoom[index] = zoom;
		MUI::keepRangeMinSpan(_zoom[index], _minZoom[index], {0,1});
		updateLayout();
	}
}

//---------------------------------------------------------------------
ofRange TracksClippedView::getZoom(int index) const{
	if(index < 2){
		return _zoom[index];
	}
	return {0,1};
}
//---------------------------------------------------------------------
float TracksClippedView::getTracksWidth() const
{
	return _tracksWidth;
}
//---------------------------------------------------------------------
void TracksClippedView::_updateTracksWidth()
{
	_tracksWidth  = ofMap(1, 0, _zoom[0].span(), 0, getWidth());
}
//---------------------------------------------------------------------
void TracksClippedView::updateLayout()
{
	

	_updateTracksWidth();
	
	
	float unscaledHeight = 0;
	for (auto c : container->children()){
		auto t = dynamic_cast<BaseTrack*>(c);
		if (t)	unscaledHeight += BaseTrack::initialHeight * t->getHeightFactor();
	}
	
	unscaledHeight = std::max(getHeight(), unscaledHeight);
	
	
	float yScale = getHeight() / (unscaledHeight * _zoom[1].span());
	
	float totalHeight = yScale*unscaledHeight;
	
	
	
	glm::vec2 offset (0,0);
	offset.x =  _tracksWidth * _zoom[0].min;
	offset.y =  totalHeight * _zoom[1].min;
	
	
	setOffset(offset * -1.f);
	
	
	float currentY = 0;
	for (auto c : container->children()){
		auto t = dynamic_cast<BaseTrack*>(c);
		if (t){
			auto h = BaseTrack::initialHeight * t->getHeightFactor()* yScale;
			t->setShape({0, currentY, _tracksWidth, h});
			
//			std::cout << "    " << t->getShape() << "\n";
			t->updateLayout();
			
			currentY += h;
		}
	}
	
	container->setSize(_tracksWidth , totalHeight);
	
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

TracksClippedViewLayout::TracksClippedViewLayout(TracksClippedView* parent):
DOM::Layout(parent),
_tracks(parent)
{

}

//---------------------------------------------------------------------
void TracksClippedViewLayout::doLayout()
{
    if (_tracks && !_isDoingLayout)
    {
        // Prevent recursive calls to doLayout.
        _isDoingLayout = true;

		_tracks->updateLayout();

        _isDoingLayout = false;
    }
}





} } // ofx::LineaDeTiempo
