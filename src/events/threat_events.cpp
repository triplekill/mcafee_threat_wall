#include "events/threat_events.h"

namespace mcafee {

static ds::EventRegistry    SHOW_THREAT_EVENT("ShowMovieEvent");

int ShowThreat::WHAT() {
	return SHOW_THREAT_EVENT.mWhat;
}

ShowThreat::ShowThreat(const LatestThreatModel& mm)
		: ds::Event(SHOW_THREAT_EVENT.mWhat)
		, mThreat(mm){
}


} // namespace mcafee
