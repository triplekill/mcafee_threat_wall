#pragma once
#ifndef TICKER_MODEL
#define TICKER_MODEL

#include <sstream>


namespace mcafee {

	class TickerModel {
	public:

		TickerModel(){};
		const int					getDbId() const { return mId; }
		const int&					getYear() const { return mYear;}
		const int&					getMonth() const { return mMonth;} 
		const int&					getDay() const { return mDay;} 
		const std::wstring&			getHeadline() const { return mHeadline;} 
		const std::wstring			getFullDate() const {
			std::wstringstream wss;
			if(mMonth == 1 ) wss << L"January";
			if(mMonth == 2 ) wss << L"February";
			if(mMonth == 3 ) wss << L"March";
			if(mMonth == 4 ) wss << L"April";
			if(mMonth == 5 ) wss << L"May";
			if(mMonth == 6 ) wss << L"June";
			if(mMonth == 7 ) wss << L"July";
			if(mMonth == 8 ) wss << L"August";
			if(mMonth == 9 ) wss << L"September";
			if(mMonth == 10) wss << L"October";
			if(mMonth == 11) wss << L"November";
			if(mMonth == 12) wss << L"December";

			wss << L" " << mDay << L", " << mYear;
			return wss.str();
		} 


	private:
		friend class				NewsQuery;

		int							mId;
		int							mYear;
		int							mMonth;
		int							mDay;
		std::wstring				mHeadline;
	};

} // namespace mcafee

#endif 