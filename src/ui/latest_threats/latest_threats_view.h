#pragma once
#ifndef UI_LATEST_THREATS_LATEST_THREATS_VIEW
#define UI_LATEST_THREATS_LATEST_THREATS_VIEW

#include <ds/app/event_client.h>
#include <ds/ui/sprite/sprite.h>
#include <ds/ui/sprite/image.h>

namespace mcafee {
class Globals;
class CountryView;
class ThreatItem;
class ImageButton;

class LatestThreatsView : public ds::ui::Sprite
{
public:
	LatestThreatsView(Globals&);

private:
	void					onAppEvent(const ds::Event&);
	virtual void			updateServer(const ds::UpdateParams&);
	void					displayLatestThreats();

	void					handleThreatTap(ds::ui::Sprite* spritey, const ci::Vec3f& pos);
	void					highlightThreat(ThreatItem* ti);

	void					nextThreat();
	void					prevThreat();


	typedef ds::ui::Sprite	inherited;
	Globals&					mGlobals;
	ds::EventClient				mEventClient;

	float						mYOffset;
	std::vector<ThreatItem*>	mThreatItems;
	ThreatItem*					mCurrentThreat;

	ImageButton*				mNextArrow;
	ImageButton*				mPrevArrow;

};

} // namespace mcafee

#endif
