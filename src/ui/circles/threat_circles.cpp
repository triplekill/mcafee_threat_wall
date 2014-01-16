#include "threat_circles.h"
#include <ds/app/environment.h>
#include <ds/ui/sprite/image.h>
#include "app/globals.h"
#include "ds/debug/logger.h"

namespace mcafee {
ThreatCircles::ThreatCircles(Globals& g)
	: Sprite(g.mEngine)
	, mGlobals(g)
	, mCurPosition(0)
	, mPlaying(false)
{
	std::string baseName = "ring_1 ";
	std::stringstream fileName;
	for(int i = 5; i < 47; i++){
		fileName.str("");
		fileName << baseName;
		if(i < 10){
			fileName << "0";
		}

		fileName << i << ".png";
		std::string   fn = ds::Environment::getAppFolder("data/images/rings", fileName.str());
		ds::ui::Image* imgy = new ds::ui::Image(g.mEngine, fn);
		mImages.push_back(imgy);
		addChild(*imgy);
		imgy->enable(false);
		imgy->show();
		imgy->setPosition(-imgy->getWidth()/2.0f, -imgy->getHeight()/2.0f);
	}

	hide();
	
}

void ThreatCircles::play(){
	mCurPosition = 0;
	mPlaying = true;
	mPrevPlayTime = Poco::Timestamp().epochMicroseconds();
	show();

	for (auto it = mImages.begin(); it < mImages.end(); ++it){
		(*it)->hide();
	}

	mImages[0]->show();
}

void ThreatCircles::updateServer( const ds::UpdateParams& p){
	inherited::updateServer(p);

	if(mPlaying){
		Poco::Timestamp::TimeVal now = Poco::Timestamp().epochMicroseconds();
		if((float)(now - mPrevPlayTime) / 1000000.0f > 1/60.0f){
			mPrevPlayTime = now;
			mCurPosition++;

			for (auto it = mImages.begin(); it < mImages.end(); ++it){
				(*it)->hide();
			}

			if(mCurPosition > mImages.size() -1){
				mPlaying = false;
			} else {
				mImages[mCurPosition]->show();
			}
		}
		
	} else {
		hide();
	}
}

} // namespace jci