#pragma once
#ifndef UI_TICKER_TICKER_ITEM
#define UI_TICKER_TICKER_ITEM

#include <ds/ui/sprite/image.h>
#include <ds/ui/sprite/text.h>

namespace mcafee {
class Globals;

/**
 * \class mcafee::TickerItem
 * \brief a single item in the ticker
 */
class TickerItem : public ds::ui::Sprite
{
public:
	TickerItem(Globals&, const std::wstring& date, const std::wstring& headline);

	float					getItemWidth();

private:
	virtual void			updateServer(const ds::UpdateParams&);


	typedef ds::ui::Sprite	inherited;
	Globals&				mGlobals;
	ds::ui::Text&			mDate;
	ds::ui::Text&			mHeadline;

};         

} // namespace mcafee

#endif // UI_TICKER_TICKER_ITEM
