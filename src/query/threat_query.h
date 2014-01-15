#pragma once
#ifndef MCAFEE_QUERY_THREAT_QUERY
#define MCAFEE_QUERY_THREAT_QUERY

#include <functional>
#include <Poco/Runnable.h>
#include <ds/query/query_result.h>
#include "model/threat_data_model.h"
#include "model/latest_threat_model.h"

namespace mcafee {

	class ThreatQuery : public Poco::Runnable {
	public:
		ThreatQuery();

		virtual void				run();

		std::vector<LatestThreatModel>		mLatestThreats;

	private:
		void						query();
	};

} // namespace mcafee

#endif