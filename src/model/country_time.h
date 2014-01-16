#pragma once
#ifndef MODEL_COUNTRY_TIME_H_
#define MODEL_COUNTRY_TIME_H_

namespace mcafee {

	class CountryTime {
	public:

		CountryTime(): mNumVirusPositions(1), mCurVirusPosition(0){};
		const std::wstring&			getCountryCode() const { return mCountryCode;}
		const std::string&			getImagePath() const { return mImagePath;} 
		const std::wstring&			getCountryName() const { return mCountryName;} 
		const ci::Vec3f&			getPosition() const { return mPosition; }
		ci::Vec3f&					getVirusPosition() {
			if(mNumVirusPositions == 1){
				return mVirusPosition;
			} else {
				mCurVirusPosition++;
				if(mCurVirusPosition > mNumVirusPositions - 1){
					mCurVirusPosition = 0;
				}

				if(mCurVirusPosition == 0){
					return mVirusPosition;
				} else if(mCurVirusPosition == 1){
					return mVirusPositionTwo;
				} else {
					return mVirusPositionThree;
				}
			}
		}

	private:
		friend class				MapView;

		std::wstring				mCountryCode;
		std::string					mImagePath;
		std::wstring				mCountryName;
		ci::Vec3f					mPosition;
		int							mNumVirusPositions;
		int							mCurVirusPosition;
		ci::Vec3f					mVirusPosition;
		ci::Vec3f					mVirusPositionTwo;
		ci::Vec3f					mVirusPositionThree;
	};

} // namespace mcafee

#endif 