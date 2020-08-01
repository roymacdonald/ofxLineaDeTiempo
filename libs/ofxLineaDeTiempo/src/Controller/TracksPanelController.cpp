//
//  TracksController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

//#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/TracksPanelController.h"
#include "MUI/Constants.h"
//#include "ofxMUI.h"
namespace ofx {
namespace LineaDeTiempo {



TracksPanelController::TracksPanelController(const std::string& name)
: TrackGroupController(name, nullptr, nullptr)
{
	_uniqueTimeControl = make_unique<TimeControl>();
	_setTimeControl(  _uniqueTimeControl.get());
	
}


TracksPanelController::~TracksPanelController()
{
	destroyView();
}


void TracksPanelController::setWindow(ofAppBaseWindow* window)
{
	if(_currentWindow != window)
	{
		if(_ownedWindow.get() != window) closeWindow();
		
		_currentWindow = window;
		if(hasView())
		{
			destroyView();
			generateView();
		}
	}
}

void TracksPanelController::generateView()
{
	if(!_panel){
		if(_currentWindow == nullptr)
		{
			setWindow(ofGetWindowPtr());
		}
			
		if(_bAutoFill)
		{
			_shape.set(0,0, _currentWindow->getWidth(), _currentWindow->getHeight());
		}
		
		
		
		if(!_mainView){
			DOM::DocumentSettings docSettings;
			docSettings.window = _currentWindow;
			
			if(_ownedWindow == nullptr)
			{
				docSettings.enabledListeners[DOM::DRAW_EVENT] = false;
			}
			_mainView = std::make_unique<MUI::MUI>(docSettings);
			_mainView->setShape(_shape);
			
			ofx::MUI::TrueTypeFontSettings::setDefaultFont(ofToDataPath("assets/fonts/OpenSans-Regular.ttf"));
			
//			auto s = _mainView->getDocumentStyles();
//			s->setColor(ConstVars::RegionBackgroundColor.get(), ofx::MUI::Styles::ROLE_BACKGROUND);
//			s->setColor(ofColor(220), ofx::MUI::Styles::ROLE_FOREGROUND);
			
			
			_parentPanel = _mainView->addChild<MUI::Panel<TracksPanel>>(getId(), ofRectangle (0,0, _shape.width, _shape.height), _mainView.get(), this);
			
			
			_parentPanel->setEnableHeaderHandle(!_bAutoFill);
			_parentPanel->setResizable(!_bAutoFill);
			_parentPanel->setCornerHandleSize(SCROLL_BAR_SIZE);
			
						
		}
		_panel = _parentPanel->container;
		
		
//		setAutoFillScreen(_bAutoFill);
		_setPanelShapeListener();
		
		
		setView(_panel);
		
//		if(!_bAutoFill)
//		{
//			_mainView->setShape(_shape);
//		}
//		else
//		{
//			_shape = _mainView->getShape();
//		}
		
	
		
		generateChildrenViews(this);
		_panel->recursiveUpdateLayout();
		
		getTimeControl()->setTotalTime(getTimeControl()->getTotalTime());
		
		
	}
}



void  TracksPanelController::enableAutoFillScreen()
{
	setAutoFillScreen(true);
}


void  TracksPanelController::disableAutoFillScreen()
{
	setAutoFillScreen(false);
}


bool  TracksPanelController::isAutoFillScreenEnabled()
{
	return _bAutoFill ;
}


void TracksPanelController::setAutoFillScreen(bool autoFill)
{
	if(_mainView && _parentPanel){
		_mainView->setAutoFillScreen(autoFill);
//		_panel->useHandles(!autoFill);
		
		_parentPanel->setEnableHeaderHandle(!autoFill);
		_parentPanel->setResizable(!autoFill);
		
		if(autoFill)
		{
			_mainView->setPosition(0, 0);
			_parentPanel->setShape(ofRectangle(0,0,_mainView->getWidth(), _mainView->getHeight()));
		}
		
	}
	_bAutoFill = autoFill;
	_setPanelShapeListener();
}


void TracksPanelController::setShape(const ofRectangle& shape)
{
	disableAutoFillScreen();
	_shape = shape;
	if(_mainView &&  _parentPanel)
	{
		_mainView->setShape(_shape);
		_parentPanel->setShape(ofRectangle(0,0,_shape.getWidth(), _shape.getHeight()));
//		_parentPanel->setShape(_shape);
//		_parentPanel->setShape(_shape);
//		_parentPanel->setShape(_shape);
//		_panel->recursiveUpdateLayout();
//		_panel->setShape({0,0, _shape.width, _shape.height});
	}
}


const ofRectangle& TracksPanelController::getShape()
{
	return _shape;
}

void TracksPanelController::_setPanelShapeListener()
{
	if (_mainView && _bAutoFill){
		_panelShapeListener = _mainView->shapeChanged.newListener(this, &TracksPanelController::_onPanelShapeChanged);
	}
	else
	{
		_panelShapeListener.unsubscribe();
	}
}
void TracksPanelController::_onPanelShapeChanged(DOM::ShapeChangeEventArgs & e)
{
	
	_shape = e.shape;
	if( _parentPanel && _bAutoFill)
	{
		_parentPanel->setShape(ofRectangle(0,0,_shape.width, _shape.height));
	}
	
}



std::shared_ptr<ofx::MUI::Styles> TracksPanelController::getStyles()
{
	if(_mainView)
	{
		return _mainView->getDocumentStyles();
	}
	return nullptr;
}


void TracksPanelController::destroyView()
{
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
	
	return ofSaveJson(filepath, toJson());
}

bool TracksPanelController::load(const std::filesystem::path& filepath)
{
	ofFile jsonFile(filepath);
	if(jsonFile.exists()){
		fromJson(ofLoadJson(filepath));
		return true;
	}
	return false;
}


void TracksPanelController::fromJson(const ofJson& j)
{
	
	TrackGroupController::fromJson(j);
	
	
	if(_uniqueTimeControl)
	{
		_uniqueTimeControl->fromJson(j["timeControl"]);
	}
	
	if(j["_panel"].get<bool>() && !getView())
	{
		generateView();
	}
}

ofJson TracksPanelController::toJson()
{
	ofJson j = TrackGroupController::toJson();
	j["class"] = "TracksPanelController";
		
	j["_panel"] = (_panel != nullptr);
	
	
	if(_uniqueTimeControl)
	{
		j["timeControl"] =_uniqueTimeControl->toJson();
	}
	
	
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

TracksPanel * TracksPanelController::getPanel()
{
	return _panel;
}

const TracksPanel * TracksPanelController::getPanel() const
{
	return _panel;
}

shared_ptr<ofAppBaseWindow> TracksPanelController::displayOnNewWindow(const ofRectangle& windowShape, bool bShareCurrentContext)
{
	if(_ownedWindow  == nullptr)
	{
		ofGLFWWindowSettings settings;
		settings.setSize(windowShape.width, windowShape.height);
		settings.setPosition(windowShape.getPosition());
		settings.resizable = true;
		if(bShareCurrentContext) settings.shareContextWith = ofGetCurrentWindow();
		return displayOnNewWindow(settings);
	}
	return nullptr;
}


shared_ptr<ofAppBaseWindow> TracksPanelController::displayOnNewWindow(const ofGLFWWindowSettings& settings)
{
	if(_ownedWindow == nullptr)
	{
		_ownedWindow = ofCreateWindow(settings);
		_ownedWindow->setVerticalSync(false);
		_bAutoFill = true;
		setWindow(_ownedWindow.get());
		if(!hasView())
		{
			generateView();
		}
		
		
		auto w = dynamic_cast<ofAppGLFWWindow*>(_ownedWindow.get());
		if(w)
		{
			std::cout << "_ownedWindowExitListener\n";
			_ownedWindowExitListener = w->events().exit.newListener(this, &TracksPanelController::_ownedWindowExited);
		}
		
		return _ownedWindow;
	}
	return nullptr;
}

void TracksPanelController::_ownedWindowExited(ofEventArgs&)
{
	_currentWindow = nullptr;
	destroyView();
	_ownedWindow = nullptr;
	_ownedWindowExitListener.unsubscribe();
	
	std::cout << " TracksPanelController::_ownedWindowExited(ofEventArgs&)\n";
}

void TracksPanelController::closeWindow()
{
	if(_ownedWindow)
	{
		auto w = dynamic_cast<ofAppGLFWWindow*>(_ownedWindow.get());
		if(w)
		{
			w->setWindowShouldClose();
			ofEventArgs a;
			_ownedWindowExited(a);
		}
	}
}
bool TracksPanelController::hasWindow() const
{
	return _ownedWindow != nullptr;
}

} } // ofx::LineaDeTiempo

//template class ofx::MUI::Panel<ofx::LineaDeTiempo::TracksPanel>;
