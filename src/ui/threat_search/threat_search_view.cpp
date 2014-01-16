#include "threat_search_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/image.h>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/query/query_client.h>
#include <ds/app/event_notifier.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "ui/button/image_button.h"
#include "events/state_events.h"

namespace mcafee {
ThreatSearchView::ThreatSearchView( Globals& g)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mEventClient(g.mEngine.getNotifier(),	[this](const ds::Event* e) { if (e) this->onAppEvent(*e); })
	, mLaunchButton(nullptr)
	, mSearchActive(false)
	, mTitle(g.mEngine.getEngineCfg().getText("nav:title").createOrThrow(g.mEngine, this))
{
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));

	ci::Vec3f buttOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("search:button:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));
	buttOffset.x *= mGlobals.mGlobalScale.x;
	buttOffset.y *= mGlobals.mGlobalScale.y;

	mLaunchButton = new ImageButton(mGlobals, "BTN_firewall_threatSearch_UP.png", "BTN_firewall_threatSearch_SELECTED.png", 10.0f);
	mLaunchButton->setPosition(buttOffset);
	mLaunchButton->setClickCallback([this](ImageButton* butty){handleButtonTap();});
	mLaunchButton->setScale(mGlobals.mGlobalScale.x, mGlobals.mGlobalScale.y);
	addChild(*mLaunchButton);

	float titleOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("search:title:offset", 0, 0.0f);

	addChild(mTitle);
	mTitle.setText("Threat Search");
	mTitle.setScale(mGlobals.mGlobalScale.x, mGlobals.mGlobalScale.y);
	mTitle.setPosition((float)(mLaunchButton->getPosition().x + mLaunchButton->getWidth() * mLaunchButton->getScale().x), 
		(float)(mLaunchButton->getPosition().y + mLaunchButton->getHeight() * mLaunchButton->getScale().y/2.0 - mTitle.getHeight()/2.0f) + titleOffset);

	mLaunchButton->setSize(mLaunchButton->getWidth() + mTitle.getWidth(), mLaunchButton->getHeight());
}

void ThreatSearchView::toggleThreatSearch(){
	if(!mSearchActive){
		activate();
	} else {
		deactivate();
	}
}

void ThreatSearchView::activate(){
	mSearchActive = true;
	mGlobals.mEngine.getNotifier().notify(ThreatSearchStarted());
}

void ThreatSearchView::deactivate(){
	mSearchActive = false;
	if(mLaunchButton) mLaunchButton->setState(ImageButton::STATE_NORMAL);
	mGlobals.mEngine.getNotifier().notify(ThreatSearchEnded());
}

void mcafee::ThreatSearchView::handleButtonTap(){
	toggleThreatSearch();

}

void mcafee::ThreatSearchView::onAppEvent( const ds::Event& in_e){
	if(in_e.mWhat == VideoModeStarted::WHAT()){
		deactivate();
	}
}

void mcafee::ThreatSearchView::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

	if(mSearchActive){
		mLaunchButton->setState(ImageButton::STATE_HIGHLIGHT);
	} 
}



}