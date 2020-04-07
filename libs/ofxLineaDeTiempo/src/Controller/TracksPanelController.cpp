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



TracksPanelController::TracksPanelController(const std::string& name)
: TrackGroupController(name, nullptr, nullptr)
{
	printDepth("TracksPanelController::TracksPanelController | ");
	_uniqueTimeControl = make_unique<TimeControl>();
	_setTimeControl(  _uniqueTimeControl.get());
	
}

void TracksPanelController::setWindow(ofAppBaseWindow* window)
{
	printDepth("void TracksPanelController::setWindow(ofAppBaseWindow* window) | ");
	if(_currentWindow != window)
	{
		_currentWindow = window;
	}
}

void TracksPanelController::generateView()
{
	printDepth("void TracksPanelController::generateView() | ");
	
	if(!_panel){
		if(_currentWindow == nullptr)
		{
			setWindow(ofGetWindowPtr());
		}
		
		if(!_mainView){
			DOM::DocumentSettings docSettings;
			docSettings.window = _currentWindow;
			
			docSettings.enabledListeners[DOM::DRAW_EVENT] = false;
			
			_mainView = std::make_unique<MUI::MUI>(docSettings);
			
		}
		
		_panel = _mainView->addChild<TracksPanel>( this->getId(), _mainView.get(), ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), this);
		
		setView(_panel);
		
		generateChildrenViews(this);
		
		_panel->_setup();
		
	}
	
}

void TracksPanelController::destroyView()
{
	printDepth("void TracksPanelController::destroyView() | ");
	if(_mainView && _panel)
	{
		
		destroyChildrenViews(this);
		
		_mainView->removeChild(_panel);
		
		
		_panel = nullptr;
		_mainView = nullptr;
		setView(nullptr);
		
	}
}


void TracksPanelController::draw()
{
	
	if(_mainView)
	{
		if(!_mainView->isListeningEvent(DOM::DRAW_EVENT)){
			ofEventArgs e;
			_mainView->draw(e);
		}
	}
}


bool TracksPanelController::save(const std::filesystem::path& filepath)
{
	printDepth("bool TracksPanelController::save(const std::filesystem::path& filepath) | ");
	
	ofSaveJson(filepath, toJson());
}

bool TracksPanelController::load(const std::filesystem::path& filepath)
{
	printDepth("bool TracksPanelController::load(const std::filesystem::path& filepath) | ");
	fromJson(ofLoadJson(filepath));
}


void TracksPanelController::fromJson(const ofJson& j)
{
	printDepth("void TracksPanelController::fromJson(const ofJson& j) | ");
	
	TrackGroupController::fromJson(j);
	
	
	if(_uniqueTimeControl)
	{
		_uniqueTimeControl->fromJson(j["timeControl"]);
	}
	
	if(j["_mainView"].get<bool>())// = (_mainView != nullptr);
	{
		generateView();
	}
}

ofJson TracksPanelController::toJson()
{
	printDepth("ofJson TracksPanelController::toJson() | ");
	ofJson j = TrackGroupController::toJson();
	j["class"] = "TracksPanelController";
	if(_panel)
	{
		//			j["_panel"] = _panel->toJson();
	}
	
	
	j["_mainView"] = (_mainView != nullptr);
	
	
	
	if(_uniqueTimeControl)
	{
		j["timeControl"] =_uniqueTimeControl->toJson();
	}
	
	
	return j;
}

void TracksPanelController::setTotalTime(const uint64_t& totalTime )
{
	printDepth("void TracksPanelController::setTotalTime(const uint64_t& totalTime ) | ");
	_uniqueTimeControl->setTotalTime(totalTime);
}


const uint64_t& TracksPanelController::getTotalTime() const
{
	printDepth("const uint64_t& TracksPanelController::getTotalTime() const | ");
	return _uniqueTimeControl->getTotalTime();
}


} } // ofx::LineaDeTiempo
