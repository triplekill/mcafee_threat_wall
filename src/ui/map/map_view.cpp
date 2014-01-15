#include "map_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/image.h>
#include <ds/app/environment.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "model/ticker_model.h"
#include "ui/ticker/ticker_item.h"

namespace mcafee {
MapView::MapView( Globals& g)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mEventClient(g.mEngine.getNotifier(),	[this](const ds::Event* e) { if (e) this->onAppEvent(*e); })
{
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));

	ds::ui::Image* backgroundImage = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_bkgrnd.png"));
	backgroundImage->setSize(mEngine.getWorldWidth(), mEngine.getWorldHeight());
	addChild(*backgroundImage);

	ds::ui::Image* grid = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_grid.png"));
	grid->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	addChild(*grid);

	ds::ui::Image* mappy = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_globalMapScaled2.png"));
	mappy->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	addChild(*mappy);
	float mapOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("map:y_offset", 0, 0.0f);
	mappy->setPosition(mEngine.getWorldWidth() - mappy->getWidth() * mappy->getScale().x, mapOffset * backgroundImage->getScale().y);


	ds::ui::Image* gradientOverMap = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_gradientOverMap.png"));
	gradientOverMap->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	addChild(*gradientOverMap);

	ds::ui::Image* logo = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_logo.png"));
	logo->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	logo->setPosition(mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("logo:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f)));
	addChild(*logo);

	ds::ui::Image* title = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_GlobalThreatCenter_title.png"));
	title->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	title->setPosition(mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("threat_title:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f)));
	addChild(*title);
}

void MapView::loadCountries(){

}

void mcafee::MapView::onAppEvent( const ds::Event& e){

}

void mcafee::MapView::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

}

}