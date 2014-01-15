#pragma once
#ifndef MODEL_COUNTRY_TIME_H_
#define MODEL_COUNTRY_TIME_H_

#include <ds/util/bit_mask.h>

#include <cinder/Vector.h>

namespace mcafee {

	class CountryTime {
	public:

		CountryTime(){};
		const std::wstring&			getCountryCode() const { return mCountryCode;}
		const std::wstring&			getImagePath() const { return mImagePath;} 
		const std::wstring&			getCountryName() const { return mCountryName;} 
		const ci::Vec3f&			getPosition() const { return mPosition; }
		const ci::Vec3f&			getVirusPosition() const { return mVirusPosition; }
		const ci::Vec3f&			getVirusPositionTwo() const { return mVirusPositionTwo; }
		const ci::Vec3f&			getVirusPositionThree() const { return mVirusPositionThree; }

	private:
		friend class				MapView;

		std::wstring				mCountryCode;
		std::wstring				mImagePath;
		std::wstring				mCountryName;
		ci::Vec3f					mPosition;
		ci::Vec3f					mVirusPosition;
		ci::Vec3f					mVirusPositionTwo;
		ci::Vec3f					mVirusPositionThree;
	};

} // namespace mcafee

#endif 