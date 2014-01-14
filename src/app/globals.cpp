#include "globals.h"

#include <Poco/String.h>
#include <ds/app/environment.h>
#include <ds/app/event_notifier.h>
#include <ds/cfg/settings.h>
#include <ds/debug/logger.h>
#include <ds/ui/sprite/sprite.h>
#include <ds/ui/sprite/sprite_engine.h>
#include <ds/util/string_util.h>
#include "events/media_events.h"

namespace mcafee {

namespace {
const std::string				EMPTY_SZ;
const std::wstring				EMPTY_SZW;
}

/**
 * \class mcafee::Globals
 */
Globals::Globals(	ds::ui::SpriteEngine& e, std::vector<TickerModel>& ni)
		: mEngine(e)
		, mNewsItems(ni)
{
}

}