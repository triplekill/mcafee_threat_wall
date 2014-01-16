#include "latest_threats_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/app/event_notifier.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "events/threat_events.h"
#include "ui/latest_threats/threat_item.h"
#include "ui/button/image_button.h"

namespace mcafee {
LatestThreatsView::LatestThreatsView( Globals& g)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mEventClient(g.mEngine.getNotifier(),	[this](const ds::Event* e) { if (e) this->onAppEvent(*e); })
	, mCurrentThreat(nullptr)
	, mNextArrow(nullptr)
	, mPrevArrow(nullptr)
{
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));
	ci::Vec3f offset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("latest:threat:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));
	offset.x *= mGlobals.mGlobalScale.x;
	offset.y *= mGlobals.mGlobalScale.y;
	float titlePad = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("latest:threat:title_pad", 0, 10.0f);
	titlePad *= mGlobals.mGlobalScale.y;

	setScale(mGlobals.mGlobalScale.x, mGlobals.mGlobalScale.y);

	ds::ui::Image* title = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_latestThreats.png"));
	addChild(*title);

	mPrevArrow = new ImageButton(mGlobals, "video_larrow_UP.png", "video_larrow_PUSHED.png", 10.0f);
	mPrevArrow->setClickCallback([this](mcafee::ImageButton*){ prevThreat(); });
	addChild(*mPrevArrow);

	mNextArrow = new ImageButton(mGlobals, "video_rarrow_UP.png", "video_rarrow_PUSHED.png", 10.0f);
	mNextArrow->setClickCallback([this](mcafee::ImageButton*){ nextThreat(); });
	addChild(*mNextArrow);


	mYOffset = title->getPosition().y + title->getHeight() * title->getScale().y + titlePad;
	setPosition(offset.x, offset.y);

	displayLatestThreats();
}

void LatestThreatsView::displayLatestThreats() {
	for (auto it = mThreatItems.begin(); it < mThreatItems.end(); ++it){
		removeAndDelete((*it));
	}

	mThreatItems.clear();

	float pad = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("latest:threat:y_padding", 0, 10.0f);
	float yp = mYOffset;
	bool firsty = true;
	for (auto it = mGlobals.mLatestThreats.begin(); it < mGlobals.mLatestThreats.end(); ++it){
		ThreatItem* ti = new ThreatItem(mGlobals, (*it));
		addChild(*ti);
		ti->setPosition(0.0f, yp);
		ti->setTapCallback([this](ds::ui::Sprite*sp, const ci::Vec3f & pos){this->handleThreatTap(sp, pos);});
		yp += ti->getHeight() + pad;
		mThreatItems.push_back(ti);

		if(firsty){
			handleThreatTap(ti, ci::Vec3f(0.0f, 0.0f, 0.0f));
			firsty = false;
		}
	}

	if(mPrevArrow && mNextArrow){
		mPrevArrow->setPosition(0.0f, yp);
		mNextArrow->setPosition(mPrevArrow->getPosition().x + mPrevArrow->getWidth() * mPrevArrow->getScale().x, mPrevArrow->getPosition().y);
	}
}

void LatestThreatsView::onAppEvent( const ds::Event& e){
	// refresh latest threats
}

void LatestThreatsView::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

}

void LatestThreatsView::handleThreatTap( ds::ui::Sprite* spritey, const ci::Vec3f& pos ){

	ThreatItem* ti = dynamic_cast<ThreatItem*>(spritey);
	highlightThreat(ti);
}

void LatestThreatsView::highlightThreat( ThreatItem* ti ){
	mCurrentThreat = ti;
	if(mCurrentThreat){
		mGlobals.mEngine.getNotifier().notify(ShowThreat(mCurrentThreat->getModel()));
	}

	for (auto it = mThreatItems.begin(); it < mThreatItems.end(); ++it){
		if((*it) == mCurrentThreat){
			(*it)->highlight();
		} else {
			(*it)->unhighlight();
		}
	}
}

void LatestThreatsView::nextThreat(){
	if(!mCurrentThreat) return;

	int indy(-1);
	for (int i = 0; i < mThreatItems.size(); i++){
		if(mThreatItems[i] == mCurrentThreat){
			indy = i;
		}
	}

	indy++;
	if(indy > mThreatItems.size() -1 || indy < 0 ){
		indy = 0;
	}

	highlightThreat(mThreatItems[indy]);
}

void LatestThreatsView::prevThreat(){
	if(!mCurrentThreat) return;

	int indy(-1);
	for (int i = 0; i < mThreatItems.size(); i++){
		if(mThreatItems[i] == mCurrentThreat){
			indy = i;
		}
	}

	indy--;
	if(indy < 0){
		indy = mThreatItems.size() -1;
	}

	highlightThreat(mThreatItems[indy]);

}

}