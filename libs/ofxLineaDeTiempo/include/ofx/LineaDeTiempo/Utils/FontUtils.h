//
//  FontUtils.h
//  example
//
//  Created by Roy Macdonald on 4/11/20.
//

#include "ofTrueTypeFont.h"

namespace ofx {
namespace LineaDeTiempo {


static inline float getTextVCenteredPos( const ofRectangle& container, const ofTrueTypeFont& font)
{
	return  container.getCenter().y  + (font.getAscenderHeight()  + font.getDescenderHeight()) *0.5;
}



static inline void drawTextCentered(const std::string& text, const ofRectangle& container, const ofTrueTypeFont& font){
	float y =  getTextVCenteredPos(container, font);
	float x = container.x + (container.width - font.stringWidth(text))*0.5;
	font.drawString(text, x, y);
	
}


}} //ofx::LineaDeTiempo
