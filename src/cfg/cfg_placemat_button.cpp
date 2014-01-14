#include "cfg/cfg_placemat_button.h"

namespace jci {
namespace cfg {

/**
 * \class ds::cfg::PlacematButton
 */
PlacematButton::PlacematButton() {
}

PlacematButton::PlacematButton(const std::string& image, const std::wstring& label)
		: mImageFileName(image)
		, mLabel(label) {
}

} // namespace cfg
} // namespace jci
