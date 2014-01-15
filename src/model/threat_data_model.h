#pragma once
#ifndef MODEL_THREAT_DATA_MODEL
#define MODEL_THREAT_DATA_MODEL


#include <cinder/Vector.h>

namespace mcafee {

// ThreatDataModel
// Holds info for each country for each threat. For the list of latest threats, check out LatestThreatModel
	class ThreatDataModel {
	public:

		ThreatDataModel(){};
		const std::wstring&			getCountry() const { return mCountry;}
		const std::wstring&			getDate() const { return mDate;}
		const int					getNumThreats() const { return mNumThreats; }
		const int					getThreatId() const { return mThreatId; }

	private:
		friend class				ThreatQuery;

		std::wstring				mCountry;
		std::wstring				mDate;
		int							mNumThreats;
		int							mThreatId;
	};

} // namespace mcafee

#endif 