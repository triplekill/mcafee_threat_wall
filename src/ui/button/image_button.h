#pragma once
#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H

#include <ds/ui/sprite/sprite.h>

namespace ds {
	namespace ui {
		class Image;
	}
}

namespace mcafee {
	class Globals;

	class ImageButton : public ds::ui::Sprite
	{
	public:
		static const int STATE_NORMAL = 0;
		static const int STATE_HIGHLIGHT = 1;

		ImageButton(Globals& globals, const std::string &normalImage, const std::string &highImage, const float touchPadding );

		void setClickCallback(const std::function<void(ImageButton* button)> &func);

		void setState(const int state);

	private:
		void handleTouch(const ds::ui::TouchInfo &touchInfo);
		bool touchInside(const ci::Vec3f &point);

		ds::ui::Image *mNormalImage;
		ds::ui::Image *mHighImage;
		std::function<void(ImageButton*)> mClickCallback;

		Globals&		mGlobals;
		int				mState;
	};
} // namespace mcafee

#endif // IMAGE_BUTTON_H