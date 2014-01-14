#include "query/news_query.h"

#include <map>
#include <sstream>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/query/query_client.h>
#include <ds/data/resource.h>

namespace mcafee {

NewsQuery::NewsQuery() {
}

void NewsQuery::run() {
	mOutput.clear();
	try {
		query();
	} catch (std::exception const&) {
	}
}

void NewsQuery::query() {
	const ds::Resource::Id			cms(ds::Resource::Id::CMS_TYPE, 0);
	std::stringstream				buf;
	ds::query::Result				r;
	buf << "SELECT id,year,month,day,text FROM news";
	if (!ds::query::Client::query(cms.getDatabasePath(), buf.str(), r, ds::query::Client::INCLUDE_COLUMN_NAMES_F)) {
		DS_LOG_WARNING("NewsQuery::queryType() error querying news");
	}
	if (r.rowsAreEmpty()) return;

	// Add the media
	ds::query::Result::RowIterator	it(r);
	while (it.hasValue()) {
		TickerModel m;
		m.mId =it.getInt(0);
		m.mYear = it.getInt(1);
		m.mMonth = it.getInt(2);
		m.mDay = it.getInt(3);
		m.mHeadline = it.getWString(4);
		mOutput.push_back(m);
		++it;
	}
}

} // namespace mcafee