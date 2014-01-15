#include "query/threat_query.h"

#include <map>
#include <sstream>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/query/query_client.h>
#include <ds/data/resource.h>

namespace mcafee {
ThreatQuery::ThreatQuery() {
}

void ThreatQuery::run() {
	mLatestThreats.clear();
	try {
		query();
	} catch (std::exception const&) {
	}
}

void ThreatQuery::query() {
	const ds::Resource::Id			cms(ds::Resource::Id::CMS_TYPE, 0);
	std::stringstream				buf;
	ds::query::Result				r;
	ds::query::Result				threatR;
	buf << "SELECT latest_threats.id, latest_threats.name FROM latest_threats ORDER BY id DESC LIMIT 10";
	if (!ds::query::Client::query(cms.getDatabasePath(), buf.str(), r, ds::query::Client::INCLUDE_COLUMN_NAMES_F)) {
		DS_LOG_WARNING("TreatQuery error querying treats");
	}
	if (r.rowsAreEmpty()) return;

	// Add the media
	ds::query::Result::RowIterator	it(r);
	while (it.hasValue()) {
		LatestThreatModel m;
		m.mThreatId =it.getInt(0);
		m.mName = it.getWString(1);

		buf.str("");
		buf << "SELECT country, startDate, infections FROM threat_data WHERE threatID = " << m.mThreatId;
		if(ds::query::Client::query(cms.getDatabasePath(), buf.str(), threatR, ds::query::Client::INCLUDE_COLUMN_NAMES_F) && !threatR.rowsAreEmpty()){
			ds::query::Result::RowIterator threatIt(threatR);
			while(threatIt.hasValue()){
				ThreatDataModel tdm;
				tdm.mCountry = threatIt.getWString(0);
				tdm.mDate = threatIt.getWString(1);
				tdm.mNumThreats = threatIt.getInt(2);
				m.mThreatData.push_back(tdm);
				++threatIt;
			}
		}
		mLatestThreats.push_back(m);
		++it;
	}
}

} // namespace mcafee