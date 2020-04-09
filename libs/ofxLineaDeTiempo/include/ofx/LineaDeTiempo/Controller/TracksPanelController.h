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
	
protected:
	
	
	virtual void fromJson(const ofJson& j) override;

	virtual ofJson toJson() override;
	

	TracksPanel* _panel = nullptr;
	
	
	ofAppBaseWindow* _currentWindow = nullptr;

	std::unique_ptr<MUI::MUI> _mainView = nullptr;
	

	std::unique_ptr<TimeControl> _uniqueTimeControl = nullptr;
	
	
private:
	
	
};

} } // ofx::LineaDeTiempo
