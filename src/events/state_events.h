#pragma once
#ifndef EVENTS_STATE_EVENTS
#define EVENTS_STATE_EVENTS

#include <ds/app/event.h>

namespace mcafee {

	class VideoModeStarted : public ds::Event {
	public:
		static int				WHAT();
		VideoModeStarted();
	};

	class VideoModeEnded : public ds::Event {
	public:
		static int				WHAT();
		VideoModeEnded();
	};

	class ThreatSearchStarted : public ds::Event {
	public:
		static int				WHAT();
		ThreatSearchStarted();
	};

	class ThreatSearchEnded : public ds::Event {
	public:
		static int				WHAT();
		ThreatSearchEnded();
	};
} // namespace mcafee

#endif 
