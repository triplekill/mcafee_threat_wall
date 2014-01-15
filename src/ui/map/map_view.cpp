#include "map_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/image.h>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/query/query_client.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "model/country_time.h"
#include "ui/map/country_view.h"

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

	mGlobals.mGlobalScale = ci::Vec2f(backgroundImage->getScale().x, backgroundImage->getScale().y);

	ds::ui::Image* grid = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_grid.png"));
	grid->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	addChild(*grid);

	ds::ui::Image* mappy = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_globalMapScaled2.png"));
	mappy->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	addChild(*mappy);
	float mapOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("map:y_offset", 0, 0.0f);
	mappy->setPosition(mEngine.getWorldWidth() - mappy->getWidth() * mappy->getScale().x, mapOffset * backgroundImage->getScale().y);


	mCountryHolder = new ds::ui::Sprite(mEngine);
	mCountryHolder->setPosition(mappy->getPosition().x, mappy->getPosition().y - 3.0f);
	mCountryHolder->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	addChild(*mCountryHolder);

	ds::ui::Image* gradientOverMap = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_gradientOverMap.png"));
	gradientOverMap->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	addChild(*gradientOverMap);

	ds::ui::Image* logo = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_logo.png"));
	logo->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	ci::Vec3f logoOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("logo:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));
	logoOffset.x *= mGlobals.mGlobalScale.x;
	logoOffset.y *= mGlobals.mGlobalScale.y;
	logo->setPosition(logoOffset);
	addChild(*logo);

	float titleOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("threat_title:offset", 0, 50.0f);
	titleOffset *= mGlobals.mGlobalScale.y;
	titleOffset += logoOffset.y + logo->getHeight();

	ds::ui::Image* title = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/static/", "firewall_GlobalThreatCenter_title.png"));
	title->setScale(backgroundImage->getScale().x, backgroundImage->getScale().y);
	title->setPosition(logoOffset.x, titleOffset);
	addChild(*title);

	loadCountries();
}

void MapView::loadCountries(){
	std::vector<CountryTime>		mCountryTimeLemonade;
	const ds::Resource::Id			cms(ds::Resource::Id::CMS_TYPE, 0);
	std::stringstream				buf;
	ds::query::Result				r;
	//               0       1         2    3   4   5     6     7      8     9    10
	buf << "SELECT country,htPath,fullName,htX,htY,dotX1,dotY1,dotX2,dotY2,dotX3,dotY3 FROM countries";
	if (!ds::query::Client::query(cms.getDatabasePath(), buf.str(), r, ds::query::Client::INCLUDE_COLUMN_NAMES_F)) {
		DS_LOG_WARNING("MediaQuery::queryType() error querying movies");
	}
	if (r.rowsAreEmpty()) return;


	// Add the media
	ds::query::Result::RowIterator	it(r);
	while (it.hasValue()) {
		std::wstring lowerCaseCountryCode = it.getWString(0);
		std::transform(lowerCaseCountryCode.begin(), lowerCaseCountryCode.end(), lowerCaseCountryCode.begin(), tolower);

		CountryTime ct;
		ct.mCountryCode			 = lowerCaseCountryCode;
		ct.mImagePath			 = it.getString(1);
		ct.mCountryName			 = it.getWString(2);
		ct.mPosition			 = ci::Vec3f(it.getFloat(3), it.getFloat(4), 0.0f);
		ct.mVirusPosition		 = ci::Vec3f(it.getFloat(5), it.getFloat(6), 0.0f);
		ct.mVirusPositionTwo	 = ci::Vec3f(it.getFloat(7), it.getFloat(8), 0.0f);
		ct.mVirusPositionThree	 = ci::Vec3f(it.getFloat(9), it.getFloat(10), 0.0f);
		mCountryTimeLemonade.push_back(ct);
		++it;
	}

	for(auto tit = mCountryTimeLemonade.begin(); tit < mCountryTimeLemonade.end(); ++tit){
		CountryView* cv = new CountryView(mGlobals, (*tit));
		cv->setPosition((*tit).getPosition());
		mCountryHolder->addChild(*cv);
		mCountryLookup[(*tit).getCountryCode()] = cv;
	}
}

void mcafee::MapView::onAppEvent( const ds::Event& e){

}

void mcafee::MapView::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

}

}