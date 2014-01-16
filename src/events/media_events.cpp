#include "events/media_events.h"

namespace mcafee {

static ds::EventRegistry    SHOW_MOVIE_EVENT("ShowMovieEvent");

int ShowMovie::WHAT() {
	return SHOW_MOVIE_EVENT.mWhat;
}

ShowMovie::ShowMovie(const MovieModel& mm)
		: ds::Event(SHOW_MOVIE_EVENT.mWhat)
		, mMovie(mm){
}


} // namespace mcafee
