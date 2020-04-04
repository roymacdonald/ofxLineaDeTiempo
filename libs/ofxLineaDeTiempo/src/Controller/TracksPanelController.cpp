//
//  TracksController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

//#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/TracksPanelController.h"
//#include "ofxMUI.h"
namespace ofx {
namespace LineaDeTiempo {



TracksPanelController::TracksPanelController():
TracksPanelController("LineaDeTiempo")
{}

TracksPanelController::TracksPanelController(const std::string& name)
: TrackGroupController(name, nullptr, nullptr)
{

	_uniqueTimeControl = make_unique<TimeControl>();
	_setTimeControl(  _uniqueTimeControl.get());
	disableAutoDraw();
}

void TracksPanelController::setWindow(ofAppBaseWindow* window)
{
	if(_currentWindow != window)
	{
		_currentWindow = window;
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
			if(!bAutoDrawEnabled)
				disableAutoDraw();
		}
		
		_panel = _mainView->addChild<TracksPanel>( this->getId(), _mainView.get(), ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), this);

		setView(_panel);
		
		generateChildrenViews(this);

		_panel->_setup();
		
	}
	
	
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


void TracksPanelController::enableAutoDraw()
{
	if(_mainView)
	{
		_mainView->enableEventListener(DOM::DRAW_EVENT);
	}
	bAutoDrawEnabled = true;
}

void TracksPanelController::disableAutoDraw()
{
	if(_mainView)
	{
		_mainView->disableEventListener(DOM::DRAW_EVENT);
	}
	bAutoDrawEnabled = false;
}

bool TracksPanelController::isAutoDrawEnabled()
{
	if(_mainView)
	{
		return _mainView->isListeningEvent(DOM::DRAW_EVENT);
	}
	return bAutoDrawEnabled;
}

void TracksPanelController::draw()
{
	if(!isAutoDrawEnabled())
	{
		if(_mainView)
		{
			ofEventArgs e;
			_mainView->draw(e);
		}
	}
	else
	{
		ofLogWarning("TracksPanelController::draw") << "Do not call TracksPanelController::draw() function when it has auto draw enabled.";
	}
}
bool TracksPanelController::save(const std::filesystem::path& filepath)
{
	
	
	
	ofSaveJson(filepath, toJson());
}

bool TracksPanelController::load(const std::filesystem::path& filepath)
{
	fromJson(ofLoadJson(filepath));
}


void TracksPanelController::fromJson(const ofJson& j)
{
	
	TrackGroupController::fromJson(j);

			
			if(_uniqueTimeControl)
			{
				_uniqueTimeControl->fromJson(j["timeControl"]);
			}
			
			
	if(j["bAutoDrawEnabled"].get<bool>())
	{
		enableAutoDraw();
	}
	else
	{
		disableAutoDraw();
	}

	if(j["_mainView"].get<bool>())// = (_mainView != nullptr);
	{
		generateView();
	}
	
	
}

ofJson TracksPanelController::toJson()
{
	ofJson j = TrackGroupController::toJson();
	j["class"] = "TracksPanelController";
		if(_panel)
		{
//			j["_panel"] = _panel->toJson();
		}
		
		
//		ofAppBaseWindow* _currentWindow = nullptr;
		
		j["_mainView"] = (_mainView != nullptr);
		
		
		
		if(_uniqueTimeControl)
		{
			j["timeControl"] =_uniqueTimeControl->toJson();
		}
		
		
		j["bAutoDrawEnabled"] = bAutoDrawEnabled;
	
	return j;
}

void TracksPanelController::setTotalTime(const uint64_t& totalTime )
{
	 _uniqueTimeControl->setTotalTime(totalTime);
}


const uint64_t& TracksPanelController::getTotalTime() const
{
	return _uniqueTimeControl->getTotalTime();
}


} } // ofx::LineaDeTiempo
