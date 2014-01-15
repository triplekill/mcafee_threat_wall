#include "ticker_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "model/ticker_model.h"
#include "ui/ticker/ticker_item.h"

namespace mcafee {
TickerView::TickerView( Globals& g)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mEventClient(g.mEngine.getNotifier(),	[this](const ds::Event* e) { if (e) this->onAppEvent(*e); })
{
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));
	float backgroundHeight = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("ticker:background:height",0, 20.0f);
	float backgroundOffset = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("ticker:background:y_offset",0, 0.0f);
	float lineWidth = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("ticker:line:width",0, 1.0f);


	ds::ui::Sprite*			mBackground;
	ds::ui::Sprite*			mTopLine;
	ds::ui::Sprite*			mBotLine;

	mBackground = new ds::ui::Sprite(mEngine);
	addChild(*mBackground);
	mBackground->enable(false);
	mBackground->disableMultiTouch();
	mBackground->setTransparent(false);
	mBackground->setColor(0.0f, 0.0f, 0.0f);
	mBackground->setSize(mEngine.getWorldWidth(), backgroundHeight);
	mBackground->setPosition(0.0f, backgroundOffset);

	mBotLine = new ds::ui::Sprite(mEngine);
	addChild(*mBotLine);
	mBotLine->enable(false);
	mBotLine->disableMultiTouch();
	mBotLine->setTransparent(false);
	mBotLine->setColor(mcAfeeRed);
	mBotLine->setSize(mEngine.getWorldWidth(), lineWidth);
	mBotLine->setPosition(0.0f, backgroundOffset + backgroundHeight);

	mTopLine = new ds::ui::Sprite(mEngine);
	addChild(*mTopLine);
	mTopLine->enable(false);
	mTopLine->disableMultiTouch();
	mTopLine->setTransparent(false);
	mTopLine->setColor(mcAfeeRed);
	mTopLine->setSize(mEngine.getWorldWidth(), lineWidth);
	mTopLine->setPosition(0.0f, backgroundOffset);

	float xp(0.0f);
	for (auto it = mGlobals.mNewsItems.begin(); it < mGlobals.mNewsItems.end(); ++it){
		TickerItem* ti = new TickerItem(mGlobals, (*it).getFullDate(), (*it).getHeadline());
		this->addChild(*ti);
		ti->setPosition(xp, 0.0f);
		xp += ti->getItemWidth();
		mItems.push_back(ti);
	}

	setPosition(0.0f, mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("ticker:y_pos", 0, 0.5f) * mEngine.getWorldHeight(), 0.0f);

	mSpeed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getFloat("ticker:speed", 0, 60.0f);

}

void mcafee::TickerView::onAppEvent( const ds::Event& e){

}

void mcafee::TickerView::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);
	float dp = p.getDeltaTime() * mSpeed;
	std::vector<TickerItem*> finishedItems;
	float xp = 0.0f;
	for (auto it = mItems.begin(); it < mItems.end(); ++it){
		(*it)->move(-mSpeed, 0.0f);
		xp = (*it)->getPosition().x + (*it)->getItemWidth();
		if(xp < 0.0f){
			finishedItems.push_back((*it));
		}
	}

	for (auto it = finishedItems.begin(); it < finishedItems.end(); ++it){
		for (auto tit = mItems.begin(); tit < mItems.end(); ++tit){
			if((*it) == (*tit)){
				mItems.erase(tit);
				mItems.push_back((*it));
				break;
			}
		}

		(*it)->setPosition(xp, 0.0f);
		xp += (*it)->getItemWidth();
	}
	
}

}