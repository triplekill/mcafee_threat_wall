#pragma once
#ifndef UI_CLOCK_CLOCK_VIEW
#define UI_CLOCK_CLOCK_VIEW

#include <ds/app/event_client.h>
#include <ds/ui/sprite/text.h>
#include <ds/ui/sprite/sprite.h>
#include <ds/ui/sprite/image.h>

namespace mcafee {
	class Globals;

	class ClockView : public ds::ui::Sprite
	{
	public:
		ClockView(Globals&);

	private:
		void					onAppEvent(const ds::Event&);
		virtual void			updateServer(const ds::UpdateParams&);

		typedef ds::ui::Sprite	inherited;
		Globals&				mGlobals;
		ds::EventClient			mEventClient;

		bool					m24HourClock;

		ds::ui::Image*			mBackground;
		ds::ui::Image*			mAm;
		ds::ui::Image*			mPm;
		ds::ui::Text*			mHours;
		ds::ui::Text*			mMins;

		float					mHoursWidth;
		float					mMinOffset;
		float					mMinWidth;
		float					mTimeYOffset;
	};

} // namespace mcafee

#endif
