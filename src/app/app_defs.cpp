#include "app_defs.h"

#include <ds/debug/logger.h>

namespace mcafee {
namespace {
	// SETTINGS
	const std::string		SETTINGS_LAYOUT_("layout");
	const std::string		SETTINGS_DEBUG_ONLY_("d-o");
	const std::string		SETTINGS_KEYBOARD_("key");
	const std::string		SETTINGS_TEXT_("text");

	// FONTS
	const std::string		_FONT_DS_DIGI("ds-digi");
	const std::string		_FONT_FRUTIGER_EXTRA_BOLD_CONDENSED("frutiger-extra-bold-condensed");
	const std::string		_FONT_FRUTIGER_BOLD_CONDENSED("frutiger-bold-condensed");
	const std::string		_FONT_FRUTIGER_ROMAN("frutiger-roman");
	const std::string		_FONT_FRUTIGER_BLACK_CONDENSED("frutiger-black-condensed");
	const std::string		_FONT_FRUTIGER_BLACK_ITALIC("frutiger-black-italic");
	const std::string		_FONT_FRUTIGER_BLACK("frutiger-black");
	const std::string		_FONT_FRUTIGER_BOLD("frutiger-bold");
	const std::string		_FONT_FRUTIGER_BOLD_ITALIC("frutiger-bold-italic");
	const std::string		_FONT_FRUTIGER_CONDENSED("frutiger-condensed");
	const std::string		_FONT_FRUTIGER_ITALIC("frutiger-italic");
	const std::string		_FONT_FRUTIGER_LIGHT("frutiger-light");
	const std::string		_FONT_FRUTIGER_ROMAN_55("frutiger-roman-55");
	const std::string		_FONT_FRUTIGER_LIGHT_CONDENSED("frutiger-light-condensed");
	const std::string		_FONT_FRUTIGER_LIGHT_ITALIC("frutiger-light-italic");
	const std::string		_FONT_FRUTIGER_ULTRA_BLACK("frutiger-ultra-black");
}

const ds::BitMask			APP_LOG = ds::Logger::newModule("app");
const ds::BitMask			TCP_LOG = ds::Logger::newModule("tcp");

// SETTINGS
const std::string&			SETTINGS_LAYOUT = SETTINGS_LAYOUT_;
const std::string&			SETTINGS_DEBUG_ONLY = SETTINGS_DEBUG_ONLY_;
const std::string&			SETTINGS_KEYBOARD = SETTINGS_KEYBOARD_;
const std::string&			SETTINGS_TEXT = SETTINGS_TEXT_;

// FONTS
const std::string&			FONT_DS_DIGI = _FONT_DS_DIGI;
const std::string&			FONT_FRUTIGER_EXTRA_BOLD_CONDENSED = _FONT_FRUTIGER_EXTRA_BOLD_CONDENSED;
const std::string&			FONT_FRUTIGER_BOLD_CONDENSED = _FONT_FRUTIGER_BOLD_CONDENSED;
const std::string&			FONT_FRUTIGER_ROMAN = _FONT_FRUTIGER_ROMAN;
const std::string&			FONT_FRUTIGER_BLACK_CONDENSED = _FONT_FRUTIGER_BLACK_CONDENSED;
const std::string&			FONT_FRUTIGER_BLACK = _FONT_FRUTIGER_BLACK;
const std::string&			FONT_FRUTIGER_BLACK_ITALIC = _FONT_FRUTIGER_BLACK_ITALIC;
const std::string&			FONT_FRUTIGER_BOLD_ITALIC = _FONT_FRUTIGER_BOLD_ITALIC;
const std::string&			FONT_FRUTIGER_BOLD = _FONT_FRUTIGER_BOLD;
const std::string&			FONT_FRUTIGER_CONDENSED = _FONT_FRUTIGER_CONDENSED;
const std::string&			FONT_FRUTIGER_ITALIC = _FONT_FRUTIGER_ITALIC;
const std::string&			FONT_FRUTIGER_LIGHT = _FONT_FRUTIGER_LIGHT;
const std::string&			FONT_FRUTIGER_ROMAN_55 = _FONT_FRUTIGER_ROMAN_55;
const std::string&			FONT_FRUTIGER_LIGHT_CONDENSED = _FONT_FRUTIGER_LIGHT_CONDENSED;
const std::string&			FONT_FRUTIGER_LIGHT_ITALIC = _FONT_FRUTIGER_LIGHT_ITALIC;
const std::string&			FONT_FRUTIGER_ULTRA_BLACK = _FONT_FRUTIGER_ULTRA_BLACK;


const int					PHYSICS_MEDIA_PANEL_CATEGORY = (1<<1);
const int					PHYSICS_NODE_PANEL_CATEGORY = (1<<2);
const int					PHYSICS_TREE_NODE_CATEGORY = (1<<3);
const int					PHYSICS_TREE_LINKED_NODE_CATEGORY = (1<<4);

std::string					get_location_file(const std::string& left, const std::string& right) {
	std::stringstream		buf;
//	buf << left << ".loc_" << get_location() << right;
	return buf.str();
}
} // namespace mcafee