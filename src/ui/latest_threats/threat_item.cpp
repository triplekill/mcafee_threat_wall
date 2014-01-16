#include "threat_item.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/image.h>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>

#include "app/globals.h"
#include "app/app_defs.h"

namespace mcafee {
ThreatItem::ThreatItem( Globals& g, LatestThreatModel& ltm)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mLatestThreatModel(ltm)
	, mThreatTitle(g.mEngine.getEngineCfg().getText("latest:threat").createOrThrow(g.mEngine, this))
{
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));
	ci::Color backy = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("latest:threat:background",0, ci::Color(1.0f, 0.0f, 0.0f));
	float touchPadding = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("latest:threat:touch_padding", 0, 10.0f);

	std::wstring titley = ltm.getName();
	std::transform(titley.begin(),titley.end(),titley.begin(), toupper);

	addChild(mThreatTitle);
	mThreatTitle.setText(titley);
	mThreatTitle.setPosition(touchPadding, touchPadding - 1.0f);

	setSize(touchPadding * 2.0f + mThreatTitle.getWidth(), touchPadding * 2.0f + mThreatTitle.getHeight());
	setColorA(ci::ColorA(backy.r, backy.g, backy.b, 1.0));
	enable(true);
	enableMultiTouch(ds::ui::MULTITOUCH_INFO_ONLY);

}

void ThreatItem::highlight(){
	setTransparent(false);
}

void ThreatItem::unhighlight(){
	setTransparent(true);
}

}