#pragma once
#ifndef UI_LATEST_THREATS_THREAT_ITEM
#define UI_LATEST_THREATS_THREAT_ITEM

#include <ds/ui/sprite/sprite.h>
#include <ds/ui/sprite/text.h>
#include "model/latest_threat_model.h"

namespace mcafee {
	class Globals;
	class CountryView;

	class ThreatItem : public ds::ui::Sprite
	{
	public:
		ThreatItem(Globals&, LatestThreatModel& ltm);
		void					highlight();
		void					unhighlight();

		LatestThreatModel&		getModel(){ return mLatestThreatModel; }

	private:
		typedef ds::ui::Sprite	inherited;
		Globals&				mGlobals;
		LatestThreatModel		mLatestThreatModel;

		ds::ui::Text&			mThreatTitle;

	};

} // namespace mcafee

#endif
