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


namespace ofx {
namespace LineaDeTiempo {


class TracksPanelController
:public TrackGroupController

{
public:

	TracksPanelController(const std::string& name);
	
	virtual ~TracksPanelController() = default;
	
	

	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	
	
	void setWindow(ofAppBaseWindow* window);
	
	///\brief Enable automatic drawing of timeline(no need to call its draw() function.
	/// it will draw on top of everything else.
	/// Enabled by default
	void enableAutoDraw();

	
	///\brief Disable automatic drawing of timeline.
	/// you need to call its draw() function for it to draw.
	void disableAutoDraw();
	
	///\brief get if the auto draw feature is enabled or not.
	///\returns true if it is enabled, false if not.
	bool isAutoDrawEnabled();
	
	
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
	
	
protected:
	
	
	virtual void fromJson(const ofJson& j) override;

	virtual ofJson toJson() override;
	
	TracksPanel* _panel = nullptr;
	
	
	ofAppBaseWindow* _currentWindow = nullptr;
	
	std::unique_ptr<MUI::MUI> _mainView = nullptr;
	
	
	ofEventListeners _mainViewListeners;
	
	void _mainViewMoved(DOM::MoveEventArgs&);
	void _mainViewResized(DOM::ResizeEventArgs&);

	std::unique_ptr<TimeControl> _uniqueTimeControl = nullptr;
	
	
private:
	
	bool bAutoDrawEnabled = true;
	
};

} } // ofx::LineaDeTiempo
