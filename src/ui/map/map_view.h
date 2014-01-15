#pragma once
#ifndef UI_MAP_MAP_VIEW
#define UI_MAP_MAP_VIEW

#include <ds/app/event_client.h>
#include <ds/ui/sprite/sprite.h>

namespace mcafee {
class Globals;

/**
 * \class mcafee::TableView
 * \brief The root superclass for the table.
 */
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
	float					mSpeed;

};

} // namespace mcafee

#endif // UI_TABLE_TABLEVIEW_H_
