#pragma once
#ifndef mcafee_APP_APPDEFS_H
#define mcafee_APP_APPDEFS_H

#include <string>
#include <ds/util/bit_mask.h>

namespace mcafee {
extern const ds::BitMask		APP_LOG;
extern const ds::BitMask		TCP_LOG;

// SETTINGS
extern const std::string&		SETTINGS_LAYOUT;
extern const std::string&		SETTINGS_DEBUG_ONLY;
extern const std::string&		SETTINGS_KEYBOARD;
extern const std::string&		SETTINGS_TEXT;

// FONTS
extern const std::string&		FONT_DS_DIGI;
extern const std::string&		FONT_FRUTIGER_EXTRA_BOLD_CONDENSED; //  FRUTIEBC.TTF
extern const std::string&		FONT_FRUTIGER_BOLD_CONDENSED; //FRUTIGBC.TTF
extern const std::string&		FONT_FRUTIGER_ROMAN; //FRUTIG01.TTF
extern const std::string&		FONT_FRUTIGER_BLACK_CONDENSED; // FONT_FRUTIG02.TTF
extern const std::string&		FONT_FRUTIGER_BLACK; //FONT_FRUTIG03.TTF
extern const std::string&		FONT_FRUTIGER_BLACK_ITALIC; //FONT_FRUTIG04;
extern const std::string&		FONT_FRUTIGER_BOLD_ITALIC; // FONT_FRUTIGBI
extern const std::string&		FONT_FRUTIGER_BOLD; //FONT_FRUTIGEB
extern const std::string&		FONT_FRUTIGER_CONDENSED; //FONT_FRUTIGEC
extern const std::string&		FONT_FRUTIGER_ITALIC; //FONT_FRUTIGEI
extern const std::string&		FONT_FRUTIGER_LIGHT; //FONT_FRUTIGEL
extern const std::string&		FONT_FRUTIGER_ROMAN_55; //FONT_FRUTIGER
extern const std::string&		FONT_FRUTIGER_LIGHT_CONDENSED; //FONT_FRUTIGLC
extern const std::string&		FONT_FRUTIGER_LIGHT_ITALIC; //FONT_FRUTIGLI
extern const std::string&		FONT_FRUTIGER_ULTRA_BLACK; //FONT_FRUTIGUB
 
// PHYSICS
extern const int				PHYSICS_MEDIA_PANEL_CATEGORY;
extern const int				PHYSICS_NODE_PANEL_CATEGORY;
extern const int				PHYSICS_TREE_NODE_CATEGORY;
extern const int				PHYSICS_TREE_LINKED_NODE_CATEGORY;

// Defines
typedef void*					hotspot_route;
namespace HotspotRouteType {
enum Enum {
	City,
	Room,
};
} // HotspotRouteType

// Convenience to get a location-based file name.
// Left is the part before the meta data, right is the part after.
// Example: To get "city.loc_1.png", left="city" right=".png"
// Note: This SHOULD be obsoleted by util/location_resource
std::string						get_location_file(const std::string& left, const std::string& right);
} // namespace mcafee

#endif // mcafee_APP_APPDEFS_H