#pragma once
#ifndef MODEL_LATEST_THREAT_MODEL
#define MODEL_LATEST_THREAT_MODEL


#include <cinder/Vector.h>
#include "model/threat_data_model.h"

namespace mcafee {

	// LatestThreatModel
	// The latest top threats. For country specific data, check out ThreatDataModel
	class LatestThreatModel {
	public:

		LatestThreatModel(){};
		const std::wstring&			getName() const { return mName;}
		const int					getThreatId() const { return mThreatId; }

	private:
		friend class				ThreatQuery;

		std::wstring					mName;
		int								mThreatId;
		std::vector<ThreatDataModel>	mThreatData;
	};

} // namespace mcafee

#endif 