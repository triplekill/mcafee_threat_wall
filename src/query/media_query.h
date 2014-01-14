#pragma once
#ifndef mcafee_QUERY_MEDIAQUERY_H_
#define mcafee_QUERY_MEDIAQUERY_H_

#include <functional>
#include <Poco/Runnable.h>
#include <ds/query/query_result.h>
#include "model/movie_model.h"

namespace mcafee {

class MediaQuery : public Poco::Runnable {
public:
	MediaQuery();

	virtual void				run();

	std::vector<MovieModel>		mOutput;

private:
	void						query();
};

} // namespace mcafee

#endif