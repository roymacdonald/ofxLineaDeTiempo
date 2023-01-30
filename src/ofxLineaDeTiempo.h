#pragma once

#include "ofMain.h"
#include "LineaDeTiempo/Controller/TracksPanelController.h"

using ofxLineaDeTiempo = ofx::LineaDeTiempo::TracksPanelController;

namespace ofx{
namespace LineaDeTiempo{
    ///\brief Enable support for Hi DPI (retina) displays;
    ///\ use along with ofxGuiEnableHiResDisplay(); for it to work properly
    static void enableHiDpi(){
        MUI::ConstVars::enableHiDpi();
        ConstVars::enableHiDpi();
        
    }
    
    ///\brief Disable support for Hi DPI (retina) displays;
///\ use along with ofxGuiDisableHiResDisplay(); for it to work properly
    static void disableHiDpi(){
        MUI::ConstVars::disableHiDpi();
        ConstVars::disableHiDpi();
    }

    ///\brief Check if support for Hi DPI (retina) displays is enabled;
    ///\returns true if HiDpi support enabled, otherwise false
    static bool isHiDpiEnabled(){
        return MUI::ConstVars::isHiDpiEnabled();
    }

}
}
