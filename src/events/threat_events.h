#pragma once
#ifndef EVENTS_THREAT_EVENTS_
#define EVENTS_THREAT_EVENTS_

#include <cinder/Vector.h>
#include <ds/app/event.h>
#include "model/latest_threat_model.h"

namespace mcafee {
	 
	// Displays a threat on the map with virus circles and stuff
	class ShowThreat : public ds::Event {
	public:
		static int				WHAT();
		ShowThreat(const LatestThreatModel& mm);

		const LatestThreatModel&		mThreat;
	};
} // namespace mcafee

#endif // EVENTS_MEDIAEVENTS_H_
