#pragma once
#ifndef mcafee_APP_GLOBALS_H
#define mcafee_APP_GLOBALS_H

#include <unordered_map>

#include "model/ticker_model.h"

namespace ds {
namespace ui {
class SpriteEngine;
} // namespace ui
} // namespace ds

namespace mcafee {
class SearchData;

/**
 * \class mcafee::Globals
 * \brief Global data for the app.
 */
class Globals
{
public:
	Globals(ds::ui::SpriteEngine&, std::vector<TickerModel>& ni);

	ds::ui::SpriteEngine&			mEngine;

	std::vector<TickerModel>&		mNewsItems;

private:
	friend class ThreatApp;
};

} // namespace mcafee

#endif // 