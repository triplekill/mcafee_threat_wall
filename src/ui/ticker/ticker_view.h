#pragma once
#ifndef UI_TICKER_TICKER_VIEW
#define UI_TICKER_TICKER_VIEW

#include <ds/app/event_client.h>
#include <ds/ui/sprite/image.h>

namespace mcafee {
class Globals;
class TickerItem;

/**
 * \class mcafee::TableView
 * \brief The root superclass for the table.
 */
class TickerView : public ds::ui::Sprite
{
public:
	TickerView(Globals&);

private:
	void					onAppEvent(const ds::Event&);
	virtual void			updateServer(const ds::UpdateParams&);


	typedef ds::ui::Sprite	inherited;
	Globals&				mGlobals;
	ds::EventClient			mEventClient;
	float					mSpeed;

	ds::ui::Sprite*			mBackground;
	ds::ui::Sprite*			mTopLine;
	ds::ui::Sprite*			mBotLine;

	std::vector<TickerItem*>	mItems;

};

} // namespace mcafee

#endif // UI_TABLE_TABLEVIEW_H_
