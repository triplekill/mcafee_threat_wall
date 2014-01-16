#include "video_thumbnail.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/app/environment.h>
#include <ds/ui/tween/tweenline.h>
#include <Poco/Path.h>

#include "app/globals.h"
#include "app/app_defs.h"

namespace mcafee {
VideoThumbnail::VideoThumbnail( Globals& g, MovieModel& mm)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mMovieModel(mm)
	, mTitle(nullptr)
	, mThumbnail(nullptr)
	, mSelectedOverlay(nullptr)
{
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));

	ci::Vec3f playerOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("video:player:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));
	ci::Vec3f buttOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("video:button:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));

	Poco::Path p(ds::Environment::getDownstreamDocumentsFolder());
	p.append( "/mcafee/");
	p.append(mMovieModel.getThumbnail());
	mThumbnail = new ds::ui::Image(mEngine, p.toString());
	mThumbnail->setScale(0.5f, 0.5f);
	addChild(*mThumbnail);

	mTitle = &(g.mEngine.getEngineCfg().getText("video:thumb").createOrThrow(g.mEngine, this));
	mTitle->setText(mMovieModel.getTitle());
	addChild(*mTitle);
	mTitle->setPosition(0.0f, mThumbnail->getHeight() * mThumbnail->getScale().y + 5.0f);

	setSize(mThumbnail->getWidth() * mThumbnail->getScale().x, mTitle->getPosition().y + mTitle->getHeight() + 10.0f);
	enable(true);
	enableMultiTouch(ds::ui::MULTITOUCH_INFO_ONLY);
}


}