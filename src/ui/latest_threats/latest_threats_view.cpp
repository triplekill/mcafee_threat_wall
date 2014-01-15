#include "latest_threats_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/image.h>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "ui/latest_threats/threat_item.h"

namespace mcafee {
LatestThreatsView::LatestThreatsView( Globals& g)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mEventClient(g.mEngine.getNotifier(),	[this](const ds::Event* e) { if (e) this->onAppEvent(*e); })
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
	for (auto it = mGlobals.mLatestThreats.begin(); it < mGlobals.mLatestThreats.end(); ++it){
	//	std::wcout << L"THREAT: " << (*it).getName() << std::endl;
		ThreatItem* ti = new ThreatItem(mGlobals, (*it));
		addChild(*ti);
		ti->setPosition(0.0f, yp);
		ti->setTapCallback([this](ds::ui::Sprite*sp, const ci::Vec3f & pos){this->handleThreatTap(sp, pos);});
		yp += ti->getHeight() + pad;
		mThreatItems.push_back(ti);
	}
}

void LatestThreatsView::onAppEvent( const ds::Event& e){
	// refresh latest threats
}

void LatestThreatsView::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

}

void LatestThreatsView::handleThreatTap( ds::ui::Sprite* spritey, const ci::Vec3f& pos ){

	for (auto it = mThreatItems.begin(); it < mThreatItems.end(); ++it){
		if((*it) == spritey){
			(*it)->highlight();
		} else {
			(*it)->unhighlight();
		}
	}


}

}