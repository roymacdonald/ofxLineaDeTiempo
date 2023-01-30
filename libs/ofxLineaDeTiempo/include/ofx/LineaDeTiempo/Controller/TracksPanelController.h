////
////  TracksController.hpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/6/20.
////
//
#pragma once
//#include "LineaDeTiempo/BaseTypes/BaseViewController.h"

#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/Controller/KeyframeTrackController.h"

#include "LineaDeTiempo/View/TracksPanel.h"

#include "LineaDeTiempo/View/TimelineDocument.h"
#include "MUI/Panel.h"

namespace ofx {
namespace LineaDeTiempo {


class TracksPanelController
:public TrackGroupController

{
public:

	TracksPanelController(const std::string& name);
	
	virtual ~TracksPanelController();
	

	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	
	
	void setWindow(ofAppBaseWindow* window);

	
	void draw();
	
	///\brief saves the whole timeline state and data.
	/// uses a JSON file. If the passed filepath does not have an extension or it has one different from ".json"
	/// it will add/replace the extension with ".json"
	///\returns true if saved correctly. false otherwise
	bool save(const std::filesystem::path& filepath);
	
	///\brief loads the whole timeline state and data.
	/// must be a .json file. Otherwise it will return false.
	///
	///\returns true if loaded corectly. If the file is malformed or if the parser finds any inconsistency it will return false.
	bool load(const std::filesystem::path& filepath);
	
	
	///\brief Sets the timeline's total time or length.
	///\param totalTime the total time in milliseconds
	void setTotalTime(const uint64_t& totalTime );
	
	
	///\brief Gets the timeline's total time or length.
	///\returns the total time in milliseconds
	const uint64_t& getTotalTime() const;
	

	TracksPanel * getPanel();
	const TracksPanel * getPanel() const;
	
	
	
	///\brief Enable Automatic resizing it draw using the complete window. It is enabled by default.
	void enableAutoFillScreen();
	
	///\brief Disable Automatic resizing.
	void disableAutoFillScreen();
	
	///\brief Set the Automatic resizing.  It is enabled by default.
	///\param autoFill if true will automatically resize to fill the whole window, if false will stay at the same size it is set to.
	void setAutoFillScreen(bool autoFill);
	
	///\brief get if it is automatically resizing to fill the screen.  It is enabled by default.
	///\returns true if it is automaticaly resizing, false otherwise.
	bool isAutoFillScreenEnabled();
	
	
	///\brief Set the shape of the ofxLineaDeTiempo instance.
	/// If autoFillScreen is enable calling this function will disable it.
	///\param shape A rectangle that defines the position of the top left corner, width and height.
	void setShape(const ofRectangle& shape);
	
	
	///\brief Get the shape of the ofxLineaDeTiempo instance.
	///\returns A rectangle that defined by the position of the top left corner, width and height.
	const ofRectangle& getShape();
	
	
	
	std::shared_ptr<ofx::MUI::Styles> getStyles();
	
	
	///\brief Creates a new window and displays the timeline in it.
	///\param windowShape The rectangle that defines the shape of the window. In screen coordinates
	///\param bShareCurrentContext set to true if you want this window to share the context with the current context.
	///\returns shared_ptr (smart pointer) to the newly created window.
	shared_ptr<ofAppBaseWindow> displayOnNewWindow(const ofRectangle& windowShape, bool bShareCurrentContext = true);
	
	///\brief Creates a new window and displays the timeline in it. (Use this if you want more advanced and customized window settings).
	///\param settings the GLFW window settings for the new window.
	///\returns shared_ptr (smart pointer) to the newly created window.
	shared_ptr<ofAppBaseWindow> displayOnNewWindow(const ofGLFWWindowSettings& settings);
	
	///\brief Will close the window created with displayOnNewWindow(...)
	void closeWindow();
	
	
	///\brief get if the timeline has its own window or not.
	///\returns true if it is using a window created with displayOnNewWindow(...) otherwise false;
	bool hasWindow() const;
	
	
	///\brief returns the Timeline's main view document.
	///This is the outmost view of the timeline, the TimelineDocument instance. it might not be the most useful as the actual timeline is a few layers in.
	TimelineDocument* getMainView()
	{
		if(_mainView != nullptr)
		{
			return _mainView.get();
		}
		return nullptr;
	}
    
    ///\brief sets the vertical or horizontal scroll and zoom values. Think of it as setting the scroll handles.
    ///Their position is a normalized value between 0 and 1.
    ///when calling setVerticalScrollZoom({0,1}) it will zoom all the way out showing everything.
    /// when both values are equal zoom will be at its maximum.
    /// If the view is not active it will do nothing
    ///\param val. it is made by two float values between 0 and 1. Tip: You can call like setVerticalScrollZoom({0,1});
    void setVerticalScrollZoom(const ofRange& val );
    void setHorizontalScrollZoom(const ofRange& val );
    
    
    ///\brief gets the vertical or horizontal scroll and zoom values. Think of this values as the position of the scroll handles, in normalized values between 0 and 1.
    ///If there is no view it will return an empty ofRange.
    ///\returns an ofRange with the zoom/scroll values. an ofRange with values min == 0 and max == 1 means that it is zoomed all the way out.
    ofRange  getVerticalScrollZoom();
    ofRange  getHorizontalScrollZoom();
	
protected:
	
	
	virtual void fromJson(const ofJson& j) override;

	virtual ofJson toJson() override;
	

	TracksPanel* _panel = nullptr;
	
	
	ofAppBaseWindow* _currentWindow = nullptr;

	std::unique_ptr<TimelineDocument> _mainView = nullptr;
	

	std::unique_ptr<TimeControl> _uniqueTimeControl = nullptr;

	
	bool _bAutoFill = true;
	
	ofRectangle _shape;
	
	void _setPanelShapeListener();
	
	ofEventListener _panelShapeListener;
	
	void _onPanelShapeChanged(DOM::ShapeChangeEventArgs &);
	

	MUI::Panel<TracksPanel>* _parentPanel = nullptr;
	
private:
	
	shared_ptr<ofAppBaseWindow> _ownedWindow = nullptr;
	ofEventListener _ownedWindowExitListener;
	
	void _ownedWindowExited(ofEventArgs&);
	
	bool _bIgnoreShapeChange = false;
	
};

} } // ofx::LineaDeTiempo
