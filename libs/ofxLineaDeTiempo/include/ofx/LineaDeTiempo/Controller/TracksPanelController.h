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

#include "ofx/MUI/MUI.h"
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
	
	
protected:
	
	
	virtual void fromJson(const ofJson& j) override;

	virtual ofJson toJson() override;
	

	TracksPanel* _panel = nullptr;
	
	
	ofAppBaseWindow* _currentWindow = nullptr;

	std::unique_ptr<MUI::MUI> _mainView = nullptr;
	

	std::unique_ptr<TimeControl> _uniqueTimeControl = nullptr;

	
	bool _bAutoFill = true;
	
	ofRectangle _shape;
	
	void _setPanelShapeListener();
	
	ofEventListener _panelShapeListener;
	
	void _onPanelShapeChanged(DOM::ShapeChangeEventArgs &);
	

	MUI::Panel<TracksPanel>* _parentPanel = nullptr;
	
private:
	
	
};

} } // ofx::LineaDeTiempo
