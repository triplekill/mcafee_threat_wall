#include "query/query_handler.h"

#include <ds/app/event_notifier.h>
#include <ds/debug/logger.h>
#include <ds/debug/debug_defines.h>
#include <ds/ui/sprite/sprite_engine.h>

namespace mcafee {

/**
 * \class mcafee::QueryHandler
 */
QueryHandler::QueryHandler(ds::ui::SpriteEngine& se, std::vector<MovieModel>& ml, std::vector<TickerModel>& nl)
		: mNodeWatcher(se)
		, mMovieList(ml)
		, mNewsList(nl)
		, mNotifier(se.getNotifier())
		, mMediaQuery(se)
		, mNewsQuery(se)
{
	mNodeWatcher.add([this](const ds::NodeWatcher::Message& msg){this->onNodeMessage(msg);});

	// Initialize data
 	//mMediaQuery.setReplyHandler([this](MediaQuery& q){mMovieList.swap(q.mOutput);});
	mMediaQuery.setReplyHandler([this](MediaQuery& q){this->onMediaQuery(q);});
	mMediaQuery.start(nullptr, true);

	mNewsQuery.setReplyHandler([this](NewsQuery& q){this->onNewsQuery(q);});
	mNewsQuery.start(nullptr, true);

	mNotifier.addListener(this, [this](const ds::Event* m){ if (m) this->onAppEvent(*m); });
	mNotifier.addRequestListener(this, [this](ds::Event& e){ this->onAppRequest(e); });
}

void QueryHandler::onAppEvent(const ds::Event& in_e) {
}

void QueryHandler::onAppRequest(ds::Event& in_e) {
	//if (in_e.mWhat == PartnerProductPathSearchRequest::WHAT()) {
	//	PartnerProductPathSearchRequest&	e((PartnerProductPathSearchRequest&)in_e);
	//	mPartnerProductPathSearch.run(e.mPartnerId, e.mResult);
	//}
}

void QueryHandler::onNodeMessage(const ds::NodeWatcher::Message& msg) {
	// Too many tables to care about...
	mMediaQuery.start(nullptr);
}

void QueryHandler::onMediaQuery(MediaQuery& q) {
	mMovieList.swap(q.mOutput);
	
  //mNotifier.notify(&MediaGalleryChanged(mMedia));
}

void QueryHandler::onNewsQuery( NewsQuery& q){
	mNewsList.swap(q.mOutput);
}


} // namespace mcafee