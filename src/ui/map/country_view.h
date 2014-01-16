#pragma once
#ifndef UI_MAP_COUNTRY_VIEW
#define UI_MAP_COUNTRY_VIEW

#include <ds/ui/sprite/sprite.h>
#include "model/country_time.h"

namespace mcafee {
class Globals;

class CountryView : public ds::ui::Sprite
{
public:
	CountryView(Globals&, CountryTime& model);

	void					highlight();
	void					unhighlight();

	CountryTime&			getCountryModel() { return mCountryModel; }

private:


	typedef ds::ui::Sprite	inherited;
	Globals&				mGlobals;
	CountryTime				mCountryModel;


};

} // namespace mcafee

#endif
