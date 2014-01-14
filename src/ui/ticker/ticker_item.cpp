#include "ticker_item.h"
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/sprite_engine.h>

#include "app/globals.h"

namespace mcafee {


TickerItem::TickerItem( Globals& g, const std::wstring& date, const std::wstring& headline )
	: inherited(g.mEngine)
	, mGlobals(g)
	, mHeadline(g.mEngine.getEngineCfg().getText("ticker:headline").createOrThrow(g.mEngine, this))
	, mDate(g.mEngine.getEngineCfg().getText("ticker:date").createOrThrow(g.mEngine, this))
{
	std::wstring upperDate = date;
	std::transform(upperDate.begin(), upperDate.end(), upperDate.begin(), toupper);
	mDate.setText(upperDate);

	std::wstring upperHead = headline;
	std::transform(upperHead.begin(), upperHead.end(), upperHead.begin(), toupper);
	mHeadline.setText(upperHead);
	mHeadline.setPosition(mDate.getWidth() + 10.0f, 0.0f);
}

void TickerItem::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

}

float TickerItem::getItemWidth(){
	return mHeadline.getWidth() + mHeadline.getPosition().x + 20.0f;
}

}
