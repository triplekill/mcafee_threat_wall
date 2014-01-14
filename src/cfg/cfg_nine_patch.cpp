#include "cfg/cfg_nine_patch.h"

#include <ds/ui/image_source/image_drop_shadow.h>
#include <ds/ui/sprite/nine_patch.h>

template<typename T>
static T get_value(const std::string& key, const std::unordered_map<std::string, T>& map, const T default_value) {
	if (map.empty()) return default_value;
	const auto it = map.find(key);
	if (it != map.end()) return it->second;
	return default_value;
}

namespace jci {
namespace cfg {

namespace {
const std::string	EMPTY_SZ("");
const std::string	RADIUS_SZ("radius");
const std::string	FALLOFF_SZ("falloff");
const std::string	COLOR_SZ("color");
const float			DEFAULT_RADIUS(5.0f);
const char*			CREATE_ERROR = "ds::cfg::NinePatch can't create NinePatch sprite";
}

/**
 * \class ds::cfg::NinePatch
 */
NinePatch::NinePatch()
	: mType(EMPTY)
{
}

NinePatch::NinePatch(const Type t)
	: mType(t)
{
}

ds::ui::NinePatch* NinePatch::create(ds::ui::SpriteEngine& se, ds::ui::Sprite* parent) const
{
	if (mType == EMPTY) return nullptr;
	ds::ui::NinePatch*				s = new ds::ui::NinePatch(se);
	if (!s) return nullptr;
	configure(*s);
	if (parent) parent->addChild(*s);
	return s;
}

ds::ui::NinePatch& NinePatch::createOrThrow(ds::ui::SpriteEngine& se, ds::ui::Sprite* parent, const char* error) const
{
	ds::ui::NinePatch*				s = create(se, parent);
	if (!s) throw std::runtime_error(error ? error : CREATE_ERROR);
	return *s;
}

void NinePatch::configure(ds::ui::NinePatch& s) const
{
	if (mType == ARC_DROP_SHADOW) {
		const float			radius = get_value(RADIUS_SZ, mFloat, DEFAULT_RADIUS),
							falloff = get_value(FALLOFF_SZ, mFloat, 1.0f);
		const ci::ColorA	clr = get_value(COLOR_SZ, mColor, ci::ColorA(1.0f, 1.0f, 1.0f));
		s.setImage(ds::ui::ImageDropShadow(radius, falloff, ci::Vec2f(0.0f, 0.0f), clr));
	}
}

float NinePatch::getRadius() const
{
	return get_value(RADIUS_SZ, mFloat, DEFAULT_RADIUS);
}

} // namespace cfg
} // namespace jci
