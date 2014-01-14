#pragma once
#ifndef JCI_CFG_CFGPLACEMATBAR_H_
#define JCI_CFG_CFGPLACEMATBAR_H_

#include <cinder/Vector.h>
#include <ds/cfg/settings.h>

namespace jci {
namespace cfg {

/**
 * \class jci::cfg::PlacematBar
 */
class PlacematBar {
public:
	PlacematBar();

	// Read from the supplied settings file. Root is the beginning part of the settings key.
	bool				readFrom(const ds::cfg::Settings&, const int sessionId, const std::string& root, const int index);

	int					getSessionId() const;
	const ci::Vec3f&	getPosition() const;
	float				getRotation() const;
	int					getFlags() const;

private:
	int					mSessionId;
	ci::Vec3f			mPosition;
	float				mRotation;
	int					mFlags;
};

} // namespace cfg
} // namespace jci

#endif // JCI_CFG_CFGPLACEMATBAR_H_