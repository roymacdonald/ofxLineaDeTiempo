//
//  TracksController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

//#include "LineaDeTiempo/Controller/TracksController.h"
#include "LineaDeTiempo/Controller/TracksPanelController.h"

namespace ofx {
namespace LineaDeTiempo {




//,public BaseViewController<TracksPanel>

TracksPanelController::TracksPanelController(const std::string& name)
: TrackGroupController(name, nullptr)
, BaseViewController<TracksPanel>()



{
	
}

void TracksPanelController::createMainView(const ofRectangle& viewport, ofAppBaseWindow* window)
{
	_mainView = std::make_unique<MUI::MUI>(window);
	_mainView->setShape(viewport);
	this->BaseViewController<TracksPanel>::createView(_mainView.get(), this->getId(), viewport, this);
}


MUI::MUI * TracksPanelController::getMainView()
{
	return _mainView;
}

const MUI::MUI * TracksPanelController::getMainView() const
{
	return _mainView;
}





} } // ofx::LineaDeTiempo
