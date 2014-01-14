#pragma once
#ifndef mcafee_QUERY_QUERYHANDLER_H_
#define mcafee_QUERY_QUERYHANDLER_H_

#include <ds/app/event.h>
#include <ds/cfg/settings.h>
#include <ds/thread/serial_runnable.h>
#include "query/media_query.h"
#include "query/news_query.h"

// NOTE: Placing this include at the top gets a conflict
// with cinder. Need to look into that.
#include <ds/network/node_watcher.h>

namespace ds {
class EventNotifier;
}

namespace mcafee {

/**
 * \class mcafee::QueryHandler
 * \brief Handle app events that deal with querying for data.
 */
class QueryHandler {
public:
	QueryHandler(ds::ui::SpriteEngine&, std::vector<MovieModel>& movies, std::vector<TickerModel>& news);

private:
	void								onNodeMessage(const ds::NodeWatcher::Message&);
	void								onAppEvent(const ds::Event&);
	void								onAppRequest(ds::Event&);

	void								onMediaQuery(MediaQuery&);
	void								onNewsQuery(NewsQuery&);

	ds::NodeWatcher						mNodeWatcher;

	ds::EventNotifier&					mNotifier;

	std::vector<MovieModel>&			mMovieList;
	std::vector<TickerModel>&			mNewsList;

	ds::SerialRunnable<MediaQuery>		mMediaQuery;
	ds::SerialRunnable<NewsQuery>		mNewsQuery;

};

} // namespace mcafee

#endif // mcafee_QUERY_QUERYHANDLER_H_