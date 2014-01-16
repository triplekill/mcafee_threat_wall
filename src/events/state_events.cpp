#include "events/state_events.h"

namespace mcafee {

	static ds::EventRegistry    VIDEO_MODE_STARTED_EVENT("VideoModeStartedEvent");

	int VideoModeStarted::WHAT() {
		return VIDEO_MODE_STARTED_EVENT.mWhat;
	}

	VideoModeStarted::VideoModeStarted()
		: ds::Event(VIDEO_MODE_STARTED_EVENT.mWhat){
	}


	static ds::EventRegistry    VIDEO_MODE_ENDED_EVENT("VideoModeEndedEvent");

	int VideoModeEnded::WHAT() {
		return VIDEO_MODE_ENDED_EVENT.mWhat;
	}

	VideoModeEnded::VideoModeEnded()
		: ds::Event(VIDEO_MODE_ENDED_EVENT.mWhat){
	}


	static ds::EventRegistry    THREAT_SEARCH_STARTED("ThreatSearchStarted");

	int ThreatSearchStarted::WHAT() {
		return THREAT_SEARCH_STARTED.mWhat;
	}

	ThreatSearchStarted::ThreatSearchStarted()
		: ds::Event(THREAT_SEARCH_STARTED.mWhat){
	}


	static ds::EventRegistry    THREAT_SEARCH_ENDED("ThreatSearchEnded");

	int ThreatSearchEnded::WHAT() {
		return THREAT_SEARCH_ENDED.mWhat;
	}

	ThreatSearchEnded::ThreatSearchEnded()
		: ds::Event(THREAT_SEARCH_ENDED.mWhat){
	}

} // namespace mcafee
