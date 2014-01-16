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
	const std::string&			getMovie() const { return mMovie;} 
	const std::string&			getThumbnail() const { return mThumbnail;} 

private:
	friend class				MediaQuery;

	int							mId;
	std::wstring				mTitle;
	std::string					mMovie;
	std::string					mThumbnail;
};

} // namespace mcafee

#endif 