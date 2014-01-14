#include "cfg/cfg_placemat_bar.h"

#include "ui/table/placemat/placemat_defs.h"

namespace jci {
namespace cfg {

/**
 * \class jci::cfg::PlacematBar
 */
PlacematBar::PlacematBar()
		: mSessionId(-10000)
		, mRotation(0.0f)
		, mFlags(0) {
}

bool PlacematBar::readFrom(const ds::cfg::Settings& s, const int sessionId, const std::string& root, const int index) {
	mSessionId = sessionId;
	try {
		mPosition = s.getPoint(root + ":bar:position", index);
		mRotation = s.getFloat(root + ":bar:rotation", index);
	} catch (std::exception const&) {
		return false;
	}
	mFlags = 0;
	if (s.getBool(root + ":bar:tree_close", index, false)) mFlags |= jci::placemat::INCLUDE_TREE_CLOSE_BUTTON_F;
	return true;
}

int PlacematBar::getSessionId() const {
	return mSessionId;
}

const ci::Vec3f& PlacematBar::getPosition() const {
	return mPosition;
}

float PlacematBar::getRotation() const {
	return mRotation;
}

int PlacematBar::getFlags() const {
	return mFlags;
}

} // namespace cfg
} // namespace jci