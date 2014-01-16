#pragma once
#ifndef UI_VIDEO_PLAYER_VIDEO_THUMBNAIL
#define UI_VIDEO_PLAYER_VIDEO_THUMBNAIL

#include <ds/ui/sprite/text.h>
#include <ds/ui/sprite/image.h>
#include <ds/ui/sprite/sprite.h>
#include <ds/ui/sprite/video.h>

#include "model/movie_model.h"

namespace mcafee {
	class Globals;
	class ImageButton;

	class VideoThumbnail : public ds::ui::Sprite
	{
	public:
		VideoThumbnail(Globals&, MovieModel& mm);

		MovieModel&					getMovieModel();
		void						setState(bool isSelected);

	private:

		typedef ds::ui::Sprite	inherited;
		Globals&					mGlobals;

		ds::ui::Sprite*				mSelectedOverlay;
		ds::ui::Text*				mTitle;
		ds::ui::Image*				mThumbnail;

		MovieModel					mMovieModel;
	};

} // namespace mcafee

#endif
