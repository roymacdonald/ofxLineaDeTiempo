#include "ofApp.h"

using namespace ofx::MUI;



//--------------------------------------------------------------


void ofApp::setup(){
		
	
	ofSetCircleResolution(200);
	ofSetBackgroundColor(0);


	parameters.setName("parameters");
	parameters.add(radius.set("radius",50,1,100));
	
	
	timeline.add(parameters);
	
	
	timeline.generateView();
	
	timeline.setShape(ofRectangle(0,ofGetHeight()/2,ofGetWidth(), ofGetHeight()/2));
	
	
	gui.setup(ConstVars::getParameters());
	
	
	colorsGui.setup("colorsGui");
	colorsGui.setPosition(gui.getShape().getBottomLeft());
#ifdef USE_SINGLE_VALUE_FOR_ROLE

	colorsGui.add(FOREGROUND);
	colorsGui.add(BACKGROUND);
	colorsGui.add(BORDER_BACKGROUND);
	colorsGui.add(BORDER_FOREGROUND);
	colorsGui.add(ACCENT);
	colorsGui.add(TEXT);

	auto s = timeline.getStyles();
	if(s)
	{

		FOREGROUND = s->getColor(Styles::ROLE_FOREGROUND, Styles::STATE_DOWN).r;
		BACKGROUND = s->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_DOWN).r;
		BORDER_BACKGROUND = s->getColor(Styles::ROLE_BORDER_BACKGROUND, Styles::STATE_DOWN).r;
		BORDER_FOREGROUND = s->getColor(Styles::ROLE_BORDER_FOREGROUND, Styles::STATE_DOWN).r;
		ACCENT = s->getColor(Styles::ROLE_ACCENT, Styles::STATE_DOWN).r;
		TEXT = s->getColor(Styles::ROLE_TEXT, Styles::STATE_DOWN).r;

	}	


	listeners.push(FOREGROUND.newListener(this, &ofApp::FOREGROUND_CHANGED));
	listeners.push(BACKGROUND.newListener(this, &ofApp::BACKGROUND_CHANGED));
	listeners.push(BORDER_BACKGROUND.newListener(this, &ofApp::BORDER_BACKGROUND_CHANGED));
	listeners.push(BORDER_FOREGROUND.newListener(this, &ofApp::BORDER_FOREGROUND_CHANGED));
	listeners.push(ACCENT.newListener(this, &ofApp::ACCENT_CHANGED));
	listeners.push(TEXT.newListener(this, &ofApp::TEXT_CHANGED));






#else
	foregroundGroup.add(FOREGROUND_NORMAL);
	foregroundGroup.add(FOREGROUND_OVER);
	foregroundGroup.add(FOREGROUND_DOWN);
	foregroundGroup.add(FOREGROUND_DISABLED);

	backgroundGroup.add(BACKGROUND_NORMAL);
	backgroundGroup.add(BACKGROUND_OVER);
	backgroundGroup.add(BACKGROUND_DOWN);
	backgroundGroup.add(BACKGROUND_DISABLED);

	borderBackgroundGroup.add(BORDER_BACKGROUND_NORMAL);
	borderBackgroundGroup.add(BORDER_BACKGROUND_OVER);
	borderBackgroundGroup.add(BORDER_BACKGROUND_DOWN);
	borderBackgroundGroup.add(BORDER_BACKGROUND_DISABLED);

	borderForegroundGroup.add(BORDER_FOREGROUND_NORMAL);
	borderForegroundGroup.add(BORDER_FOREGROUND_OVER);
	borderForegroundGroup.add(BORDER_FOREGROUND_DOWN);
	borderForegroundGroup.add(BORDER_FOREGROUND_DISABLED);

	accentGroup.add(ACCENT_NORMAL);
	accentGroup.add(ACCENT_OVER);
	accentGroup.add(ACCENT_DOWN);
	accentGroup.add(ACCENT_DISABLED);

	textGroup.add(TEXT_NORMAL);
	textGroup.add(TEXT_OVER);
	textGroup.add(TEXT_DOWN);
	textGroup.add(TEXT_DISABLED);



	listeners.push(FOREGROUND_NORMAL.newListener(this, &ofApp::FOREGROUND_NORMAL_CHANGED));
	listeners.push(FOREGROUND_OVER.newListener(this, &ofApp::FOREGROUND_OVER_CHANGED));
	listeners.push(FOREGROUND_DOWN.newListener(this, &ofApp::FOREGROUND_DOWN_CHANGED));
	listeners.push(FOREGROUND_DISABLED.newListener(this, &ofApp::FOREGROUND_DISABLED_CHANGED));
	listeners.push(BACKGROUND_NORMAL.newListener(this, &ofApp::BACKGROUND_NORMAL_CHANGED));
	listeners.push(BACKGROUND_OVER.newListener(this, &ofApp::BACKGROUND_OVER_CHANGED));
	listeners.push(BACKGROUND_DOWN.newListener(this, &ofApp::BACKGROUND_DOWN_CHANGED));
	listeners.push(BACKGROUND_DISABLED.newListener(this, &ofApp::BACKGROUND_DISABLED_CHANGED));
	listeners.push(BORDER_BACKGROUND_NORMAL.newListener(this, &ofApp::BORDER_BACKGROUND_NORMAL_CHANGED));
	listeners.push(BORDER_BACKGROUND_OVER.newListener(this, &ofApp::BORDER_BACKGROUND_OVER_CHANGED));
	listeners.push(BORDER_BACKGROUND_DOWN.newListener(this, &ofApp::BORDER_BACKGROUND_DOWN_CHANGED));
	listeners.push(BORDER_BACKGROUND_DISABLED.newListener(this, &ofApp::BORDER_BACKGROUND_DISABLED_CHANGED));
	listeners.push(BORDER_FOREGROUND_NORMAL.newListener(this, &ofApp::BORDER_FOREGROUND_NORMAL_CHANGED));
	listeners.push(BORDER_FOREGROUND_OVER.newListener(this, &ofApp::BORDER_FOREGROUND_OVER_CHANGED));
	listeners.push(BORDER_FOREGROUND_DOWN.newListener(this, &ofApp::BORDER_FOREGROUND_DOWN_CHANGED));
	listeners.push(BORDER_FOREGROUND_DISABLED.newListener(this, &ofApp::BORDER_FOREGROUND_DISABLED_CHANGED));
	listeners.push(ACCENT_NORMAL.newListener(this, &ofApp::ACCENT_NORMAL_CHANGED));
	listeners.push(ACCENT_OVER.newListener(this, &ofApp::ACCENT_OVER_CHANGED));
	listeners.push(ACCENT_DOWN.newListener(this, &ofApp::ACCENT_DOWN_CHANGED));
	listeners.push(ACCENT_DISABLED.newListener(this, &ofApp::ACCENT_DISABLED_CHANGED));
	listeners.push(TEXT_NORMAL.newListener(this, &ofApp::TEXT_NORMAL_CHANGED));
	listeners.push(TEXT_OVER.newListener(this, &ofApp::TEXT_OVER_CHANGED));
	listeners.push(TEXT_DOWN.newListener(this, &ofApp::TEXT_DOWN_CHANGED));
	listeners.push(TEXT_DISABLED.newListener(this, &ofApp::TEXT_DISABLED_CHANGED));





//

	colorsGui.add(foregroundGroup);
	colorsGui.add(borderForegroundGroup);
	colorsGui.add(backgroundGroup);
	colorsGui.add(borderBackgroundGroup);
	colorsGui.add(accentGroup);
	colorsGui.add(textGroup);
#endif
//
	float w = colorsGui.getShape().getMaxX();

	timeline.setShape(ofRectangle(w,ofGetHeight()/2,ofGetWidth() - w, ofGetHeight()/2));
	
	
	setHelpString();
	
}
void ofApp::setHelpString()
{
	
	helpString =  "[ Key ] : action\n";
	helpString += "[ v ] : Show/Hide Timeline\n";
	helpString += "[ space bar ] : Toggle Play\n";
	helpString += "[ return/enter ] : Stop\n";
	helpString += "[ s ] : Save\n";
	helpString += "[ l ] : Load\n";
	helpString += "[ g ] : Toggle Draw Gui\n";
	helpString += "[ h ] : Show/Hide this help\n";
	helpString += "[ f ] : Toggle AutoFillWindow mode\n";
	
	ofBitmapFont bf;
	helpStringWidth = bf.getBoundingBox(helpString, 0, 0).width;
	
}

//--------------------------------------------------------------
void ofApp::update(){

}
//--------------------------------------------------------------
ofRectangle ofApp::drawColorGroup(Styles::Role role, const glm::vec3& pos)
{
	
	ofRectangle r(pos.x, pos.y, 0,0);
	float w = 80;

	auto style = timeline.getStyles();
	if(style)
	{

	ofRectangle s(pos.x, pos.y,w, w);
	
	
	for(int i = 0; i <= Styles::STATE_DISABLED; ++i)
	{
		ofSetColor(style->getColor(role, Styles::State(i)));
		ofDrawRectangle(s);
		r.growToInclude(s);
		s.setPosition(s.getTopRight());
	}
	ofDrawBitmapStringHighlight(Styles::toString(role), r.getMaxX()+4, r.y + 14);
	}
	return r;
}
//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(color);
	ofDrawCircle(ofGetWidth()*0.5,ofGetHeight()*0.25,radius);
	
	
	timeline.draw();

	
	if(bDrawGui){
		gui.draw();
		colorsGui.draw();

			glm::vec3 pos = gui.getShape().getTopRight();
			
			for(int i = 0; i <= Styles::ROLE_TEXT; i++){
				pos = drawColorGroup(Styles::Role(i), pos).getBottomLeft();
			}
	}
	if(bDrawHelp) ofDrawBitmapStringHighlight(helpString, ofGetWidth() - helpStringWidth , 16, ofColor(0, 100));

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'v') {
		if(timeline.hasView())
		{
			timeline.destroyView();
		}
		else
		{
			timeline.generateView();
		}
	}
	else if (key == ' ')
	{
		timeline.getTimeControl()->tooglePlay();
	}
	else if (key == 's')
	{
		timeline.save( ofToDataPath("timelineData.json"));
	
	}
	else if (key == 'l')
	{
		timeline.load( ofToDataPath("timelineData.json"));
	
	}
	else if (key == 'g')
	{
		bDrawGui ^= true;
	}
	else if (key == 'h')
	{
		bDrawHelp ^= true;
	}
	else if (key == OF_KEY_RETURN){
		timeline.getTimeControl()->stop();		
	}
	else if (key == 'f')
	{
		timeline.setAutoFillScreen(!timeline.isAutoFillScreenEnabled());
	}
	else if (key == 't')
	{
		timeline.setTotalTime(60000);
	}
	else if (key == 'T')
	{
		timeline.setTotalTime(120000);
		
	}
	else if (key == 'p') {
		if(timeline.getMainView())
		{
			timeline.getMainView()->printStructure();
		}
	}
	else if (key == 'H')
	{
		
		
	}
	
	
}
void ofApp::setGrayColor(uint8_t c, Styles::Role role, Styles::State state)
{
	auto s = timeline.getStyles();
	if(s)
	{
		s->setColor(ofColor(c,c,c,255), role, state);
	}

}

void ofApp::setGrayColor(uint8_t c, Styles::Role role)
{
	auto s = timeline.getStyles();
	if(s)
	{
		s->setColor(ofColor(c,c,c,255), role);
	}

}
