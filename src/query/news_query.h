#pragma once
#ifndef mcafee_QUERY_NEWS_QUERY_H_
#define mcafee_QUERY_NEWS_QUERY_H_

#include <functional>
#include <Poco/Runnable.h>
#include <ds/query/query_result.h>
#include "model/ticker_model.h"

namespace mcafee {

	class NewsQuery : public Poco::Runnable {
	public:
		NewsQuery();

		virtual void				run();

		std::vector<TickerModel>	mOutput;

	private:
		void						query();
	};

} // namespace mcafee

#endif