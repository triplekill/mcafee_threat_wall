#include "country_view.h"

#include <ds/ui/sprite/sprite_engine.h>
#include <ds/app/engine/engine_cfg.h>
#include <ds/ui/sprite/image.h>
#include <ds/app/environment.h>
#include <ds/debug/logger.h>
#include <ds/query/query_client.h>

#include "app/globals.h"
#include "app/app_defs.h"
#include "model/country_time.h"

namespace mcafee {
CountryView::CountryView( Globals& g, CountryTime& model)
	: inherited(g.mEngine)
	, mGlobals(g)
	, mCountryModel(model)
{
	ci::Color mcAfeeRed = mEngine.getEngineCfg().getSettings(SETTINGS_LAYOUT).getColor("mcafee:red",0, ci::Color(1.0f, 0.0f, 0.0f));

	ds::ui::Image* highlight = new ds::ui::Image(mEngine, ds::Environment::getAppFolder("data/images/", mCountryModel.getImagePath()));
	addChild(*highlight);

	//setOpacity(0.0f);


}

}