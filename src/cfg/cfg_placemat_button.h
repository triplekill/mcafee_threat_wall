#pragma once
#ifndef JCI_CFG_CFGPLACEMATBUTTON_H_
#define JCI_CFG_CFGPLACEMATBUTTON_H_

#include <string>

namespace jci {
namespace cfg {

/**
 * \class ds::cfg::PlacematButton
 * Experimental configuration for a placemat button.
 */
class PlacematButton {
public:
	PlacematButton();
	PlacematButton(const std::string& image, const std::wstring& label);

	std::string				mImageFileName;
	std::wstring			mLabel;
};

} // namespace cfg
} // namespace jci

#endif // JCI_CFG_CFGPLACEMATBUTTON_H_