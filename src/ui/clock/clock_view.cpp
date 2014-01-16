#include "clock_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/image.h>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/query/query_client.h>
#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeFormatter.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "ui/button/image_button.h"

namespace mcafee {
ClockView::ClockView( Globals& g)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mEventClient(g.mEngine.getNotifier(),	[this](const ds::Event* e) { if (e) this->onAppEvent(*e); })
	, mBackground(nullptr)
	, mAm(nullptr)
	, mPm(nullptr)
	, mHours(nullptr)
	, mMins(nullptr)
{
	m24HourClock = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getBool("clock:24_hour", 0, false);
	mHoursWidth = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("clock:hour:width", 0, 112.0f);
	mMinWidth = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("clock:min:width", 0, 161.0f);
	mMinOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("clock:min:offset", 0, 117.0f);
	mTimeYOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("clock:time:y_offset", 0, 25.0f);
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));
	ci::Vec3f ampmOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("clock:ampm:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));
	ci::Vec3f buttOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("clock:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));
	buttOffset.x *= mGlobals.mGlobalScale.x;
	buttOffset.y *= mGlobals.mGlobalScale.y;
	setPosition(buttOffset);
	setScale(mGlobals.mGlobalScale.x, mGlobals.mGlobalScale.y);

	mBackground = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/", "clock_bg.png"));
	addChild(*mBackground);

	mAm = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/", "clock_am.png"));
	mAm->setPosition(mBackground->getWidth() - mAm->getWidth() - ampmOffset.x, ampmOffset.y);
	addChild(*mAm);

	mPm = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/", "clock_pm.png"));
	mPm->setPosition(mBackground->getWidth() - mPm->getWidth() - ampmOffset.x, ampmOffset.y);
	addChild(*mPm);

	mHours = &(g.mEngine.getEngineCfg().getText("clock:time").createOrThrow(g.mEngine, this));
	addChild(*mHours);
	mHours->setText("24");

	mMins = &(g.mEngine.getEngineCfg().getText("clock:time").createOrThrow(g.mEngine, this));
	addChild(*mMins);
	mMins->setText("24");

}

void mcafee::ClockView::onAppEvent( const ds::Event& in_e){
	//if(in_e.mWhat == ShowThreat::WHAT()){
	//	const ShowThreat& e((const ShowThreat&)in_e);
	//	highlightThreat(e.mThreat);
	//}
}

void mcafee::ClockView::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

	if(!mAm || !mPm || !mMins || !mHours) return;
	Poco::LocalDateTime dt; 
	std::string hourTime;
	std::string minTime = Poco::DateTimeFormatter::format(dt,"%M");
	if(m24HourClock){
		hourTime = Poco::DateTimeFormatter::format(dt,"%H");
	} else {
		hourTime = Poco::DateTimeFormatter::format(dt,"%h");
		if(hourTime.find("0") == 0) hourTime = hourTime.substr(1);
	}

	mHours->setText(hourTime);
	mMins->setText(minTime);

	mHours->setPosition(mHoursWidth/2.0f - mHours->getWidth()/2.0f, mTimeYOffset);
	mMins->setPosition(mMinWidth/2.0f - mMins->getWidth()/2.0f + mMinOffset, mTimeYOffset);

	if(dt.isAM()){
		mAm->show();
		mPm->hide();
	} else {
		mAm->hide();
		mPm->show();
	}
}



}