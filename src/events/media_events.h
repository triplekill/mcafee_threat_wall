#pragma once
#ifndef EVENTS_MEDIAEVENTS_H_
#define EVENTS_MEDIAEVENTS_H_

#include <cinder/Vector.h>
#include <ds/app/event.h>
#include "model/movie_model.h"

namespace mcafee {

class ShowMovie : public ds::Event {
public:
	static int				WHAT();
	ShowMovie(const MovieModel& mm);

	const MovieModel&		mMovie;
};
} // namespace mcafee

#endif // EVENTS_MEDIAEVENTS_H_
