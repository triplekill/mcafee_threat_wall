#include "image_button.h"
#include <ds/app/environment.h>
#include <ds/ui/sprite/image.h>
#include "app/globals.h"
#include "ds/debug/logger.h"

namespace mcafee {
	ImageButton::ImageButton(Globals& g, const std::string &normalImage, const std::string &highImage, const float touchPadding)
		: Sprite(g.mEngine)
		, mGlobals(g)
		, mState(-1)
	{
		std::string   fn = ds::Environment::getAppFolder("data/images", normalImage);
		mNormalImage = new ds::ui::Image(g.mEngine, fn);
		mNormalImage->enable(false);
		mNormalImage->setPosition(touchPadding, touchPadding);
		mNormalImage->show();
		addChild(*mNormalImage);
		setSize(mNormalImage->getWidth() + touchPadding * 2.0f, mNormalImage->getHeight() + touchPadding * 2.0f);

		fn = ds::Environment::getAppFolder("data/images", highImage);
		mHighImage = new ds::ui::Image(g.mEngine, fn);
		mHighImage->enable(false);
		mHighImage->setPosition(touchPadding, touchPadding);
		mHighImage->show();
		addChild(*mHighImage);

		enable(true);
		enableMultiTouch(ds::ui::MULTITOUCH_INFO_ONLY);

		//setColor(0, 1, 0);
		//setTransparent(false);

		setProcessTouchCallback([this](ds::ui::Sprite *sprite, const ds::ui::TouchInfo &touchInfo)
		{
			this->handleTouch(touchInfo);
		});

		setState(STATE_NORMAL);
	}

	void ImageButton::setClickCallback( const std::function<void(ImageButton*)> &func )
	{
		mClickCallback = func;
	}

	void ImageButton::handleTouch( const ds::ui::TouchInfo &ti ){
		if (ti.mPhase == ds::ui::TouchInfo::Added) {
			setState(STATE_HIGHLIGHT);
		} else if (ti.mPhase == ds::ui::TouchInfo::Moved) {
			if (touchInside(ti.mCurrentGlobalPoint)) {
				setState(STATE_HIGHLIGHT);
			} else {
				setState(STATE_NORMAL);
			}
		} else if (ti.mPhase == ds::ui::TouchInfo::Removed) {
			setState(STATE_NORMAL);

			if (mClickCallback && touchInside(ti.mCurrentGlobalPoint)){
				mClickCallback(this);
			}
		}
	}

	bool ImageButton::touchInside( const ci::Vec3f &point ){
		ci::Vec3f localPoint = globalToLocal(point);
		if (localPoint.x >= 0.0f && localPoint.x <= getWidth() && localPoint.y >= 0 && localPoint.y <= getHeight())
			return true;
		return false;
	}

	void ImageButton::setState( const int state ){
		if(state == mState) return;

		float imageButtonTransitionTime = 0.15f; // need a setting for this

		mState = state;
		// TODO(SH) For some reason, the commented out parts show errors for both this app and the DTV app.
		// Will figure this out so that the transition between states looks smoother.
		if(mState == STATE_NORMAL){
			mNormalImage->setOpacity(1.0f);
			mHighImage->setOpacity(0.0f);
			//mGlobals.mEngine.getTweenline().apply(*mNormalImage, ANIM_OPACITY(), 1.0f, imageButtonTransitionTime);
			//mGlobals.mEngine.getTweenline().apply(*mHighImage, ANIM_OPACITY(), 0.0f, imageButtonTransitionTime);
		} else if(mState == STATE_HIGHLIGHT){
			mNormalImage->setOpacity(0.0f);
			mHighImage->setOpacity(1.0f);
			//mGlobals.mEngine.getTweenline().apply(*mNormalImage, ANIM_OPACITY(), 0.0f, imageButtonTransitionTime);
			//mGlobals.mEngine.getTweenline().apply(*mHighImage, ANIM_OPACITY(), 1.0f, imageButtonTransitionTime);
		} else {
			DS_LOG_ERROR("Error in button state");
		}
	}
} // namespace mcafee