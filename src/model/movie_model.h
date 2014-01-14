#pragma once
#ifndef MODEL_MEDIA_H_
#define MODEL_MEDIA_H_

#include <ds/util/bit_mask.h>

namespace mcafee {

class MovieModel {
public:

	MovieModel(){};
	const int					getDbId() const { return mId; }
	const std::wstring&			getTitle() const { return mTitle;}
	const std::wstring&			getMovie() const { return mMovie;} 
	const std::wstring&			getThumbnail() const { return mThumbnail;} 

private:
	friend class				MediaQuery;

	int							mId;
	std::wstring				mTitle;
	std::wstring				mMovie;
	std::wstring				mThumbnail;
};

} // namespace mcafee

#endif 