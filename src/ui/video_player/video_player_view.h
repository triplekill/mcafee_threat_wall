#pragma once
#ifndef UI_VIDEO_PLAYER_VIDEO_PLAYER_VIEW
#define UI_VIDEO_PLAYER_VIDEO_PLAYER_VIEW

#include <ds/app/event_client.h>
#include <ds/ui/sprite/text.h>
#include <ds/ui/sprite/sprite.h>
#include <ds/ui/sprite/video.h>

#include "model/movie_model.h"

namespace mcafee {
	class Globals;
	class ImageButton;
	class VideoThumbnail;

	class VideoPlayerView : public ds::ui::Sprite
	{
	public:
		VideoPlayerView(Globals&);

	private:
		void						onAppEvent(const ds::Event&);
		virtual void				updateServer(const ds::UpdateParams&);
		void						handleVideoButtonTap();
		void						toggleVideoPlayer();
		void						handleThumbnailTap(ds::ui::Sprite* sp);
		void						activate();
		void						deactivate();

		typedef ds::ui::Sprite	inherited;
		Globals&					mGlobals;
		ds::EventClient				mEventClient;

		bool						mPlayerActive;

		ImageButton*				mLaunchButton;
		ds::ui::Text&				mTitle;

		std::vector<VideoThumbnail*>	mThumbnails;
		
		ds::ui::Sprite*				mVideoHolder;
		ImageButton*				mPlayButton;
		ImageButton*				mPauseButton;
		ds::ui::Sprite*				mScrubBar;
		ds::ui::Sprite*				mScrubBarFull;
		ds::ui::Sprite*				mScrubBarProgress;
		ds::ui::Video*				mVideo;
	};

} // namespace mcafee

#endif
