#pragma once
#ifndef UI_MAP_MAP_VIEW
#define UI_MAP_MAP_VIEW

#include <ds/app/event_client.h>
#include <ds/ui/sprite/sprite.h>
#include "model/country_time.h"

namespace mcafee {
class Globals;
class CountryView;

class MapView : public ds::ui::Sprite
{
public:
	MapView(Globals&);

private:
	void					onAppEvent(const ds::Event&);
	virtual void			updateServer(const ds::UpdateParams&);
	void					loadCountries();


	typedef ds::ui::Sprite	inherited;
	Globals&				mGlobals;
	ds::EventClient			mEventClient;

	ds::ui::Sprite*							mCountryHolder;
	std::vector<CountryView*>				mCountries;
	std::map<std::wstring, CountryView*>	mCountryLookup;

};

} // namespace mcafee

#endif
