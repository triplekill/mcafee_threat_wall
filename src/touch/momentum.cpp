#include "touch/momentum.h"

#include <ds/ui/sprite/sprite.h>

namespace ds {

/**
 * \class ds::Momentum
 */
Momentum::Momentum(ds::ui::Sprite& target)
		: inherited(target.getEngine())
		, mSprite(target)
		, mActive(false)
		, mDeactivateThreshold(0.00001f)
		, mMass(10.0f)
		, mFriction(0.6f)
		, mNumSmoothFrames(3) {
	mLastTime = Poco::Timestamp().epochMicroseconds();
}

void Momentum::update(const ds::UpdateParams&) {
	Poco::Timestamp::TimeVal thisTime = Poco::Timestamp().epochMicroseconds();

	double		diff = (double)(thisTime - mLastTime) / 1000000.0f;
	mLastTime = thisTime;

	if (mActive) {
		bool leftwards = mVelocity.x < 0;
		mVelocity.x = abs(mVelocity.x);

		if(mVelocity.x == 0){
			if(mVelocity.y > 0){
				mDir = M_PI / 2;
			} else {
				mDir = M_PI * 3 / 2;
			}
		} else if(mVelocity.y == 0){
			if(mVelocity.x > 0){
				mDir = 0;
			} else {
				mDir = - M_PI;
			}
		} else {
			mDir = atan((double)(mVelocity.y / mVelocity.x));
		}
		mVel = sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y);
		double force = (1 - diff * mMass * mFriction);
		mVel *= force;

		if(mVel < mDeactivateThreshold){
			deactivate();
		}

		mVelocity.x = static_cast<float>(mVel * cos(mDir));
		mVelocity.y = static_cast<float>(mVel * sin(mDir));

		if (leftwards) mVelocity.x *= -1;

		ci::Vec3f		curr_pos(mSprite.getPosition());
		curr_pos.x += mVelocity.x;
		curr_pos.y += mVelocity.y;
		mSprite.setPosition(curr_pos);
	} 

	const float		absWidth = mSprite.getWidth() * mSprite.getScale().x;
	const float		absHeigh = mSprite.getHeight() * mSprite.getScale().y;
	ci::Vec2f		curPos = mSprite.getPosition().xy();
	curPos.x += absWidth/2.0f - mSprite.getCenter().x * absWidth;
	curPos.y += absHeigh/2.0f - mSprite.getCenter().y * absHeigh;

	ci::Vec2f		delta = ci::Vec2f(curPos.x - mLastPosition.x, curPos.y - mLastPosition.y);
	mLastPosition = curPos;
	mPositionHistory.push_back(delta);
	if (mPositionHistory.size() > mNumSmoothFrames) {
		mPositionHistory.erase(mPositionHistory.begin());
	}
}

void Momentum::activate() {
	mVelocity.set(0.0f,0.0f);
	if (mPositionHistory.empty()) return;

	mActive = true;

	int			histSize(static_cast<int>(mPositionHistory.size()));
	ci::Vec2f	pos;
	for (int i = 0; i < histSize; i++) {
		pos = mPositionHistory[i];
		mVelocity.x += pos.x;
		mVelocity.y += pos.y;
	}

	mVelocity.x = mVelocity.x / static_cast<float>(histSize);
	mVelocity.y = mVelocity.y / static_cast<float>(histSize);
}

void Momentum::deactivate() {
	mActive = false;
}

} // namespace ds
