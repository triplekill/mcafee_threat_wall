#include "query/media_query.h"

#include <map>
#include <sstream>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/query/query_client.h>
#include <ds/data/resource.h>

namespace mcafee {
/**
 * \class mcafee::MediaQuery
 */
MediaQuery::MediaQuery() {
}

void MediaQuery::run() {
	mOutput.clear();
	try {
		query();
	} catch (std::exception const&) {
	}
}

void MediaQuery::query() {
	const ds::Resource::Id			cms(ds::Resource::Id::CMS_TYPE, 0);
	std::stringstream				buf;
	ds::query::Result				r;
	buf << "SELECT id,title,thumb,movie FROM movies";
	if (!ds::query::Client::query(cms.getDatabasePath(), buf.str(), r, ds::query::Client::INCLUDE_COLUMN_NAMES_F)) {
		DS_LOG_WARNING("MediaQuery::queryType() error querying movies");
	}
	if (r.rowsAreEmpty()) return;

	// Add the media
	ds::query::Result::RowIterator	it(r);
	while (it.hasValue()) {
		MovieModel m;
		m.mId =it.getInt(0);
		m.mTitle = it.getWString(1);
		m.mThumbnail = it.getWString(2);
		m.mMovie = it.getWString(3);
		mOutput.push_back(m);
		++it;
	}
}

} // namespace mcafee