//
//  TracksController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

//#include "LineaDeTiempo/Controller/TracksController.h"
#include "LineaDeTiempo/Controller/TracksPanelController.h"
//#include "ofxMUI.h"
namespace ofx {
namespace LineaDeTiempo {




//,public BaseViewController<TracksPanel>

TracksPanelController::TracksPanelController(const std::string& name)
: TrackGroupController(name, nullptr)
{
	
}

void TracksPanelController::setWindow(ofAppBaseWindow* window)
{
	if(_currentWindow != window)
	{
		_currentWindow = window;
		
		_mainView = std::make_unique<MUI::MUI>(window);
	}
}

void TracksPanelController::generateView()
{
	
	if(!_panel){
		if(_currentWindow == nullptr)
		{
			setWindow(ofGetWindowPtr());
		}

		if(!_mainView){
			_mainView = std::make_unique<MUI::MUI>(_currentWindow);
//			setView(_mainView);
		}

//		_mainView->setShape(viewport);
		_panel = _mainView->addChild<TracksPanel>( this->getId(), _mainView.get(), ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), this);
//		_panel->printStructure();

		setView(_panel);//->getContainer());
		
		generateChildrenViews(this);
//		for(auto child : children())
//		{
//			auto c = dynamic_cast<BaseHasViews*>(child);
//			if(c) c->generateView();
//		}
		
		
		_panel->setup();
		
	}
	
	
	
	
//	auto groupView = _panel->addChild<TrackGroupView>(_panel, this);
//
//	groupView->setShape(_panel->getShape());
//	
	
//
//	_mainViewListeners.push(_mainView.move.newListener(this , &TracksPanelController::_mainViewMoved));
//	_mainViewListeners.push(_mainView.resize.newListener(this , &TracksPanelController::_mainViewResized));
//
	
	
	_mainViewListeners.push(_mainView->move.newListener(this , &TracksPanelController::_mainViewMoved));
	_mainViewListeners.push(_mainView->resize.newListener(this , &TracksPanelController::_mainViewResized));

	
	
}

void TracksPanelController::destroyView()
{
	if(_mainView && _panel)
	{

		destroyChildrenViews(this);
		
		_mainView->removeChild(_panel);

		_mainViewListeners.unsubscribeAll();

		_panel = nullptr;
		_mainView = nullptr;
		setView(nullptr);

	}
}

//
//MUI::MUI * TracksPanelController::getMainView()
//{
//	return _mainView.get();
//}
//
//const MUI::MUI * TracksPanelController::getMainView() const
//{
//	return _mainView.get();
//}

KeyFrameTrackController* TracksPanelController::addKeyFrameTrack(const std::string& name)
{
	return addTrack<KeyFrameTrackController>(name);
}

void TracksPanelController::_mainViewMoved(DOM::MoveEventArgs&)
{
	if(_panel)
	{
		ofRectangle s(0,0,ofGetWidth(), ofGetHeight());
		ofRectangle r = _mainView->getShape().getIntersection(s);
		
		_panel->setShape(r);
	}
	else
	{
		ofLogError("TracksPanelController::_mainViewMoved") << "the mainView moved but the panel is null. This should never happen.";
	}
	
}
void TracksPanelController::_mainViewResized(DOM::ResizeEventArgs&)
{
	if(_panel)
	{
		ofRectangle s(0,0,ofGetWidth(), ofGetHeight());
		ofRectangle r = _mainView->getShape().getIntersection(s);
		
		_panel->setShape(r);
	}
	else
	{
		ofLogError("TracksPanelController::_mainViewMoved") << "the mainView was resized but the panel is null. This should never happen.";
	}
}


} } // ofx::LineaDeTiempo
