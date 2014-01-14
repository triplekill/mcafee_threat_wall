#pragma once
#ifndef JCI_CFG_CFGNINEPATCH_H_
#define JCI_CFG_CFGNINEPATCH_H_

#include <string>
#include <unordered_map>
#include <cinder/Color.h>
#include <cinder/Vector.h>

namespace ds {
namespace ui {
class NinePatch;
class Sprite;
class SpriteEngine;
}

namespace cfg {
class Settings;
} // namespace cfg
} // namespace ds

namespace jci {
namespace cfg {

/**
 * \class ds::cfg::NinePatch
 * Experimental configuration for a nine patch.
 */
class NinePatch {
public:
	static const enum Type	{ EMPTY, ARC_DROP_SHADOW };

	NinePatch();
	NinePatch(const Type);

	// Create a new text sprite from this cfg. The throw reference throws the error if anything goes wrong.
	ds::ui::NinePatch*		create(ds::ui::SpriteEngine&, ds::ui::Sprite* parent = nullptr) const;
	ds::ui::NinePatch&		createOrThrow(ds::ui::SpriteEngine&, ds::ui::Sprite* parent = nullptr, const char* error = nullptr) const;

	void					configure(ds::ui::NinePatch&) const;

	float					getRadius() const;

	Type					mType;
	std::unordered_map<std::string, float>
							mFloat;
	std::unordered_map<std::string, ci::ColorA>
							mColor;
};

} // namespace cfg
} // namespace jci

#endif // JCI_CFG_CFGNINEPATCH_H_