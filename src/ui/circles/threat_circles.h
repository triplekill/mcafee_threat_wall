#pragma once
#ifndef CIRCLES_THREAT_CIRCLES
#define CIRCLES_THREAT_CIRCLES

#include <ds/ui/sprite/sprite.h>
#include <Poco/Timestamp.h>

namespace ds {
	namespace ui {
		class Image;
	}
}

namespace mcafee {
	class Globals;

	class ThreatCircles : public ds::ui::Sprite
	{
	public:

		ThreatCircles(Globals& globals );

		void play();
		bool playing(){ return mPlaying; }

	private:
		typedef ds::ui::Sprite		inherited;
		virtual void				updateServer(const ds::UpdateParams&);
		Globals&					mGlobals;
		int							mCurPosition;
		bool						mPlaying;
		std::vector<ds::ui::Image*>	mImages;
		Poco::Timestamp::TimeVal	mPrevPlayTime;
	};
} // namespace mcafee

#endif // CIRCLES_THREAT_CIRCLES