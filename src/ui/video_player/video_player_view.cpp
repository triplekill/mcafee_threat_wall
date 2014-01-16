#include "video_player_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/image.h>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/query/query_client.h>
#include <ds/ui/tween/tweenline.h>
#include <ds/app/event_notifier.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "ui/button/image_button.h"
#include "ui/video_player/video_thumbnail.h"
#include "events/state_events.h"
#include "events/threat_events.h"

namespace mcafee {
VideoPlayerView::VideoPlayerView( Globals& g)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mEventClient(g.mEngine.getNotifier(),	[this](const ds::Event* e) { if (e) this->onAppEvent(*e); })
	, mLaunchButton(nullptr)
	, mPlayerActive(false)
	, mTitle(g.mEngine.getEngineCfg().getText("nav:title").createOrThrow(g.mEngine, this))
	, mVideo(nullptr)
{

	setScale(mGlobals.mGlobalScale.x,mGlobals.mGlobalScale.y);
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));

	ci::Vec3f playerOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("video:player:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));
	ci::Vec3f buttOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("video:button:offset", 0, ci::Vec3f(0.0f, 0.0f, 0.0f));


	mLaunchButton = new ImageButton(mGlobals, "BTN_firewall_videos_UP.png", "BTN_firewall_videos_SELECTED.png", 10.0f);
	mLaunchButton->setPosition(buttOffset);
	mLaunchButton->setClickCallback([this](ImageButton* butty){handleVideoButtonTap();});
	addChild(*mLaunchButton);

	float titleOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("video:title:offset", 0, 0.0f);

	addChild(mTitle);
	mTitle.setText("Videos");
	mTitle.setPosition((float)(mLaunchButton->getPosition().x + mLaunchButton->getWidth() * mLaunchButton->getScale().x), 
						(float)(mLaunchButton->getPosition().y + mLaunchButton->getHeight() * mLaunchButton->getScale().y/2.0 - mTitle.getHeight()/2.0f) + titleOffset);

	mLaunchButton->setSize(mLaunchButton->getWidth() + mTitle.getWidth(), mLaunchButton->getHeight());

	mVideoHolder = new ds::ui::Sprite(mEngine);
	mVideoHolder->enable(true);
	mVideoHolder->setPosition(playerOffset.x, playerOffset.y);
	mVideoHolder->setSize((mGlobals.mEngine.getWorldWidth()) / mGlobals.mGlobalScale.x - playerOffset.x, (mGlobals.mEngine.getWorldHeight() ) / mGlobals.mGlobalScale.y- playerOffset.y);
	addChild(*mVideoHolder);

	ds::ui::Sprite* holderBackground = new ds::ui::Sprite(mEngine);
	holderBackground->setColor(0,0,0);
	holderBackground->setTransparent(false);
	holderBackground->setSize(mVideoHolder->getWidth(), mVideoHolder->getHeight());
	mVideoHolder->addChild(*holderBackground);

	mVideoHolder->setOpacity(0.0f);

	ci::Vec3f offset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getPoint("video:thumbnails:offset", 0, ci::Vec3f(0,0,0));
	std::vector<MovieModel>& movies (mGlobals.mMovieItems);
	for (auto it = movies.begin(); it < movies.end(); ++it){
		VideoThumbnail* vt = new VideoThumbnail(mGlobals,(*it));
		mVideoHolder->addChild(*vt);
		vt->setPosition(offset);
		offset.x += vt->getWidth() + 10.0f;
		mThumbnails.push_back(vt);
		vt->setTapCallback([this](ds::ui::Sprite* sp, const ci::Vec3f& pos){ handleThumbnailTap(sp);});

	}
}

void VideoPlayerView::toggleVideoPlayer(){
	if(!mPlayerActive){
		activate();
	} else {
		deactivate();
	}
}

void VideoPlayerView::activate(){
	mPlayerActive = true;
	mGlobals.mEngine.getNotifier().notify(VideoModeStarted());
	mEngine.getTweenline().apply(*mVideoHolder, ANIM_OPACITY(), 1.0f, 0.35f);

}

void VideoPlayerView::deactivate(){
	mPlayerActive = false;
	if(mLaunchButton) mLaunchButton->setState(ImageButton::STATE_NORMAL);
	mGlobals.mEngine.getNotifier().notify(VideoModeEnded());
	mEngine.getTweenline().apply(*mVideoHolder, ANIM_OPACITY(), 0.0f, 0.35f);
}

void VideoPlayerView::handleThumbnailTap( ds::ui::Sprite* sp ){

}

void mcafee::VideoPlayerView::handleVideoButtonTap(){
	toggleVideoPlayer();

}

void mcafee::VideoPlayerView::onAppEvent( const ds::Event& in_e){
	if(in_e.mWhat == ThreatSearchStarted::WHAT() || in_e.mWhat == ShowThreat::WHAT()){
		deactivate();
	}
}

void mcafee::VideoPlayerView::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

	if(mPlayerActive){
		mLaunchButton->setState(ImageButton::STATE_HIGHLIGHT);
	}
}



}