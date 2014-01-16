#pragma once
#ifndef UI_THREAT_SEARCH_THREAT_SEARCH_VIEW
#define UI_THREAT_SEARCH_THREAT_SEARCH_VIEW

#include <ds/app/event_client.h>
#include <ds/ui/sprite/text.h>
#include <ds/ui/sprite/sprite.h>

namespace mcafee {
	class Globals;
	class ImageButton;

	class ThreatSearchView : public ds::ui::Sprite
	{
	public:
		ThreatSearchView(Globals&);

	private:
		void					onAppEvent(const ds::Event&);
		virtual void			updateServer(const ds::UpdateParams&);
		void					handleButtonTap();
		void					toggleThreatSearch();
		void					activate();
		void					deactivate();

		typedef ds::ui::Sprite	inherited;
		Globals&				mGlobals;
		ds::EventClient			mEventClient;

		bool					mSearchActive;

		ImageButton*			mLaunchButton;
		ds::ui::Text&			mTitle;
	};

} // namespace mcafee

#endif
