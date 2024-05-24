#pragma once

#include "ofMain.h"
#include "ofxLineaDeTiempo.h"

#include "ofxGui.h"
#include "ConstVars.h"
#include "MUI/Styles.h"


// comment the following line to use a different value for each state
#define USE_SINGLE_VALUE_FOR_ROLE


///This example is based on the basic example. Look at it for a thorough explanation of what each thing does.
///This example is intended to be use to set the color scheme only using grays.
///TODO: Save the colorscheme and be able to load it. ATM, it has to be hardcoded as the defaults


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void draw() override;
	void update() override;
	
	void keyReleased(int key) override;
	


	
	ofxLineaDeTiempo timeline = {"Timeline"};

	ofParameterGroup parameters;
	ofParameter<float> radius;

	ofxPanel gui;
	
	
	
	// some helper stuff
	bool bDrawGui = true;
	bool bDrawHelp = true;
	
	string helpString;
	float helpStringWidth;
	void setHelpString();
	
	ofxPanel colorsGui;
	
	ofRectangle drawColorGroup(ofx::MUI::Styles::Role role, const glm::vec3& pos);

#ifdef USE_SINGLE_VALUE_FOR_ROLE
	
	ofParameter<uint8_t> FOREGROUND = {"FOREGROUND", 120 , 0, 255};
	ofParameter<uint8_t> BACKGROUND = {"BACKGROUND", 60 , 0, 255};
	ofParameter<uint8_t> BORDER_BACKGROUND = {"BORDER BACKGROUND", 30 , 0, 255};
	ofParameter<uint8_t> BORDER_FOREGROUND = {"BORDER FOREGROUND", 80 , 0, 255};
	ofParameter<uint8_t> ACCENT = {"ACCENT", 220 , 0, 255};
	ofParameter<uint8_t> TEXT = {"TEXT", 255 , 0, 255};

	void FOREGROUND_CHANGED(uint8_t&){setGrayColor(FOREGROUND.get(), ofx::MUI::Styles::ROLE_FOREGROUND);}
	void BACKGROUND_CHANGED(uint8_t&){setGrayColor(BACKGROUND.get(), ofx::MUI::Styles::ROLE_BACKGROUND);}
	void BORDER_BACKGROUND_CHANGED(uint8_t&){setGrayColor(BORDER_BACKGROUND.get(), ofx::MUI::Styles::ROLE_BORDER_BACKGROUND);}
	void BORDER_FOREGROUND_CHANGED(uint8_t&){setGrayColor(BORDER_FOREGROUND.get(), ofx::MUI::Styles::ROLE_BORDER_FOREGROUND);}
	void ACCENT_CHANGED(uint8_t&){setGrayColor(ACCENT.get(), ofx::MUI::Styles::ROLE_ACCENT);}
	void TEXT_CHANGED(uint8_t&){setGrayColor(TEXT.get(), ofx::MUI::Styles::ROLE_TEXT);}


#else

	ofParameter<uint8_t> FOREGROUND_NORMAL = {"FOREGROUND NORMAL", 120* 0.5, 0, 255};
	ofParameter<uint8_t> FOREGROUND_OVER = {"FOREGROUND OVER", 120* 0.75, 0, 255};
	ofParameter<uint8_t> FOREGROUND_DOWN = {"FOREGROUND DOWN",120 , 0, 255};
	ofParameter<uint8_t> FOREGROUND_DISABLED = {"FOREGROUND DISABLED", 120 *0.3, 0, 255};

	ofParameter<uint8_t> BACKGROUND_NORMAL = {"BACKGROUND NORMAL", 60* 0.5, 0, 255};
	ofParameter<uint8_t> BACKGROUND_OVER = {"BACKGROUND OVER", 60* 0.75, 0, 255};
	ofParameter<uint8_t> BACKGROUND_DOWN = {"BACKGROUND DOWN",60 , 0, 255};
	ofParameter<uint8_t> BACKGROUND_DISABLED = {"BACKGROUND DISABLED", 60 *0.3, 0, 255};

	ofParameter<uint8_t> BORDER_BACKGROUND_NORMAL = {"BORDER BACKGROUND NORMAL", 30* 0.5, 0, 255};
	ofParameter<uint8_t> BORDER_BACKGROUND_OVER = {"BORDER BACKGROUND OVER", 30* 0.75, 0, 255};
	ofParameter<uint8_t> BORDER_BACKGROUND_DOWN = {"BORDER BACKGROUND DOWN",30 , 0, 255};
	ofParameter<uint8_t> BORDER_BACKGROUND_DISABLED = {"BORDER BACKGROUND DISABLED", 30 *0.3, 0, 255};

	ofParameter<uint8_t> BORDER_FOREGROUND_NORMAL = {"BORDER FOREGROUND NORMAL", 80* 0.5, 0, 255};
	ofParameter<uint8_t> BORDER_FOREGROUND_OVER = {"BORDER FOREGROUND OVER", 80* 0.75, 0, 255};
	ofParameter<uint8_t> BORDER_FOREGROUND_DOWN = {"BORDER FOREGROUND DOWN",80 , 0, 255};
	ofParameter<uint8_t> BORDER_FOREGROUND_DISABLED = {"BORDER FOREGROUND DISABLED", 80 *0.3, 0, 255};

	ofParameter<uint8_t> ACCENT_NORMAL = {"ACCENT NORMAL", 200, 0, 255};
	ofParameter<uint8_t> ACCENT_OVER = {"ACCENT OVER", 200 + 10, 0, 255};
	ofParameter<uint8_t> ACCENT_DOWN = {"ACCENT DOWN",200 + 20 , 0, 255};
	ofParameter<uint8_t> ACCENT_DISABLED = {"ACCENT DISABLED", 200 *0.3, 0, 255};

	ofParameter<uint8_t> TEXT_NORMAL = {"TEXT NORMAL", 235, 0, 255};
	ofParameter<uint8_t> TEXT_OVER = {"TEXT OVER", 235 + 10, 0, 255};
	ofParameter<uint8_t> TEXT_DOWN = {"TEXT DOWN",235 + 20 , 0, 255};
	ofParameter<uint8_t> TEXT_DISABLED = {"TEXT DISABLED", 235 *0.3, 0, 255};


	ofParameterGroup accentGroup = {"Accent Group"};
	ofParameterGroup borderForegroundGroup = {"Border Foreground Group"};
	ofParameterGroup borderBackgroundGroup = {"Border Background Group"};
	ofParameterGroup textGroup = {"Text Group"};
	ofParameterGroup foregroundGroup = {"Foreground Group"};
	ofParameterGroup backgroundGroup = {"Background Group"};


void FOREGROUND_NORMAL_CHANGED(uint8_t&){setGrayColor(FOREGROUND_NORMAL.get(), ofx::MUI::Styles::ROLE_FOREGROUND, ofx::MUI::Styles::STATE_NORMAL);}
void FOREGROUND_OVER_CHANGED(uint8_t&){setGrayColor(FOREGROUND_OVER.get(), ofx::MUI::Styles::ROLE_FOREGROUND, ofx::MUI::Styles::STATE_OVER);}
void FOREGROUND_DOWN_CHANGED(uint8_t&){setGrayColor(FOREGROUND_DOWN.get(), ofx::MUI::Styles::ROLE_FOREGROUND, ofx::MUI::Styles::STATE_DOWN);}
void FOREGROUND_DISABLED_CHANGED(uint8_t&){setGrayColor(FOREGROUND_DISABLED.get(), ofx::MUI::Styles::ROLE_FOREGROUND, ofx::MUI::Styles::STATE_DISABLED);}
void BACKGROUND_NORMAL_CHANGED(uint8_t&){setGrayColor(BACKGROUND_NORMAL.get(), ofx::MUI::Styles::ROLE_BACKGROUND, ofx::MUI::Styles::STATE_NORMAL);}
void BACKGROUND_OVER_CHANGED(uint8_t&){setGrayColor(BACKGROUND_OVER.get(), ofx::MUI::Styles::ROLE_BACKGROUND, ofx::MUI::Styles::STATE_OVER);}
void BACKGROUND_DOWN_CHANGED(uint8_t&){setGrayColor(BACKGROUND_DOWN.get(), ofx::MUI::Styles::ROLE_BACKGROUND, ofx::MUI::Styles::STATE_DOWN);}
void BACKGROUND_DISABLED_CHANGED(uint8_t&){setGrayColor(BACKGROUND_DISABLED.get(), ofx::MUI::Styles::ROLE_BACKGROUND, ofx::MUI::Styles::STATE_DISABLED);}
void BORDER_BACKGROUND_NORMAL_CHANGED(uint8_t&){setGrayColor(BORDER_BACKGROUND_NORMAL.get(), ofx::MUI::Styles::ROLE_BORDER_BACKGROUND, ofx::MUI::Styles::STATE_NORMAL);}
void BORDER_BACKGROUND_OVER_CHANGED(uint8_t&){setGrayColor(BORDER_BACKGROUND_OVER.get(), ofx::MUI::Styles::ROLE_BORDER_BACKGROUND, ofx::MUI::Styles::STATE_OVER);}
void BORDER_BACKGROUND_DOWN_CHANGED(uint8_t&){setGrayColor(BORDER_BACKGROUND_DOWN.get(), ofx::MUI::Styles::ROLE_BORDER_BACKGROUND, ofx::MUI::Styles::STATE_DOWN);}
void BORDER_BACKGROUND_DISABLED_CHANGED(uint8_t&){setGrayColor(BORDER_BACKGROUND_DISABLED.get(), ofx::MUI::Styles::ROLE_BORDER_BACKGROUND, ofx::MUI::Styles::STATE_DISABLED);}
void BORDER_FOREGROUND_NORMAL_CHANGED(uint8_t&){setGrayColor(BORDER_FOREGROUND_NORMAL.get(), ofx::MUI::Styles::ROLE_BORDER_FOREGROUND, ofx::MUI::Styles::STATE_NORMAL);}
void BORDER_FOREGROUND_OVER_CHANGED(uint8_t&){setGrayColor(BORDER_FOREGROUND_OVER.get(), ofx::MUI::Styles::ROLE_BORDER_FOREGROUND, ofx::MUI::Styles::STATE_OVER);}
void BORDER_FOREGROUND_DOWN_CHANGED(uint8_t&){setGrayColor(BORDER_FOREGROUND_DOWN.get(), ofx::MUI::Styles::ROLE_BORDER_FOREGROUND, ofx::MUI::Styles::STATE_DOWN);}
void BORDER_FOREGROUND_DISABLED_CHANGED(uint8_t&){setGrayColor(BORDER_FOREGROUND_DISABLED.get(), ofx::MUI::Styles::ROLE_BORDER_FOREGROUND, ofx::MUI::Styles::STATE_DISABLED);}
void ACCENT_NORMAL_CHANGED(uint8_t&){setGrayColor(ACCENT_NORMAL.get(), ofx::MUI::Styles::ROLE_ACCENT, ofx::MUI::Styles::STATE_NORMAL);}
void ACCENT_OVER_CHANGED(uint8_t&){setGrayColor(ACCENT_OVER.get(), ofx::MUI::Styles::ROLE_ACCENT, ofx::MUI::Styles::STATE_OVER);}
void ACCENT_DOWN_CHANGED(uint8_t&){setGrayColor(ACCENT_DOWN.get(), ofx::MUI::Styles::ROLE_ACCENT, ofx::MUI::Styles::STATE_DOWN);}
void ACCENT_DISABLED_CHANGED(uint8_t&){setGrayColor(ACCENT_DISABLED.get(), ofx::MUI::Styles::ROLE_ACCENT, ofx::MUI::Styles::STATE_DISABLED);}
void TEXT_NORMAL_CHANGED(uint8_t&){setGrayColor(TEXT_NORMAL.get(), ofx::MUI::Styles::ROLE_TEXT, ofx::MUI::Styles::STATE_NORMAL);}
void TEXT_OVER_CHANGED(uint8_t&){setGrayColor(TEXT_OVER.get(), ofx::MUI::Styles::ROLE_TEXT, ofx::MUI::Styles::STATE_OVER);}
void TEXT_DOWN_CHANGED(uint8_t&){setGrayColor(TEXT_DOWN.get(), ofx::MUI::Styles::ROLE_TEXT, ofx::MUI::Styles::STATE_DOWN);}
void TEXT_DISABLED_CHANGED(uint8_t&){setGrayColor(TEXT_DISABLED.get(), ofx::MUI::Styles::ROLE_TEXT, ofx::MUI::Styles::STATE_DISABLED);}


#endif
	   
	   
	   ofxPanel constVarsGroup;
	   
	   
	   void setGrayColor(uint8_t c, ofx::MUI::Styles::Role role, ofx::MUI::Styles::State state);
	void setGrayColor(uint8_t c, ofx::MUI::Styles::Role role);
	   

	   
	   ofEventListeners listeners;

	
	
};
