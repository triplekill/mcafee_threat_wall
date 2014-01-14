#include "threat_app.h"

#include <Poco/String.h>
#include <ds/app/environment.h>
#include <ds/data/tuio_object.h>
#include <ds/debug/logger.h>
#include <ds/ui/sprite/image.h>
#include <ds/util/string_util.h>

#include "ui/ticker/ticker_view.h"

#include "app/app_defs.h"
#include "events/media_events.h"

// For the screenshot
#include <Poco/Path.h>
#include <cinder/ip/Flip.h>
#include <cinder/ImageIo.h>

static bool			is_table(const ds::ui::SpriteEngine&);

namespace mcafee {

ThreatApp::ThreatApp()
		: mQueryEventHandler(mEngine, mMediaList, mNewsList)
		, mGlobals(mEngine, mNewsList )

{
	mEngine.loadSettings(SETTINGS_LAYOUT, "layout.xml");
	mEngine.loadSettings(SETTINGS_KEYBOARD, "keyboard.xml");
	mEngine.loadSettings(SETTINGS_TEXT, "text.xml");
#ifdef _DEBUG
	mEngine.loadSettings(SETTINGS_DEBUG_ONLY, "debug_only.xml");
#endif
	mEngine.loadTextCfg("text.xml");

	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIEBC.TTF"), FONT_FRUTIGER_EXTRA_BOLD_CONDENSED);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGBC.TTF"), FONT_FRUTIGER_BOLD_CONDENSED);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIG01.TTF"), FONT_FRUTIGER_ROMAN);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIG02.TTF"), FONT_FRUTIGER_BLACK_CONDENSED);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIG03.TTF"), FONT_FRUTIGER_BLACK);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIG04.TTF"), FONT_FRUTIGER_BLACK_ITALIC);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGBI.TTF"), FONT_FRUTIGER_BOLD_ITALIC);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGEB.TTF"), FONT_FRUTIGER_BOLD);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGEC.TTF"), FONT_FRUTIGER_CONDENSED);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGEI.TTF"), FONT_FRUTIGER_ITALIC);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGEL.TTF"), FONT_FRUTIGER_LIGHT);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGER.TTF"), FONT_FRUTIGER_ROMAN_55);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGLC.TTF"), FONT_FRUTIGER_LIGHT_CONDENSED);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGLI.TTF"), FONT_FRUTIGER_LIGHT_ITALIC);
	mEngine.editFonts().install(ds::Environment::getAppFolder("data", "fonts/FRUTIGUB.TTF"), FONT_FRUTIGER_ULTRA_BLACK);



}

void ThreatApp::setupServer() {
	ds::ui::Sprite&		rootSprite = mEngine.getRootSprite();

	TickerView* tv = new TickerView(mGlobals);
	rootSprite.addChild(*tv);

}

void ThreatApp::keyDown(KeyEvent e) {
	inherited::keyDown(e);

	if (e.getCode() == KeyEvent::KEY_ESCAPE)
	{
		quit();
	
	} 
}

void ThreatApp::keyUp(KeyEvent e) {
	inherited::keyUp(e);
}

void ThreatApp::touchesBegan(TouchEvent& e) {
	inherited::touchesBegan(e);
}

void ThreatApp::mouseDown(MouseEvent e) {
	inherited::mouseDown(e);
}

void ThreatApp::mouseDrag(MouseEvent e) {
	inherited::mouseDrag(e);
}

void ThreatApp::mouseUp(MouseEvent e) {
		inherited::mouseUp(e);
}

void ThreatApp::update() {
	inherited::update();
}


} // namespace mcafee

// This line tells Cinder to actually create the application
CINDER_APP_BASIC( mcafee::ThreatApp, RendererGl )