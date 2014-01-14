#include "math/circle.h"

namespace ds {
namespace math {

namespace {
const float		_PI = 3.14159265359f;
const float		DEGREE2RADIAN = 0.0174532925f;
}

/**
 * \class ds::Circle
 */
Circle::Circle(const ci::Vec2f& center, const float radius)
		: mCenter(center)
		, mRadius(radius) {
}

float Circle::getCircumference() const {
	return _PI * (mRadius*2.0f);
}

float Circle::getCircumference(const ds::RangeF& r) const {
	const float	rd = (r.mMax - r.mMin) / 360.0f;
	return getCircumference() * rd;
}

ci::Vec2f Circle::getPoint(float degree) const {
	while (degree < 0.0f) degree += 360.0f;
	while (degree > 360.0f) degree -= 360.0f;
	return ci::Vec2f(	mCenter.x + (mRadius * cos(degree*DEGREE2RADIAN)),
						mCenter.y + (mRadius * sin(degree*DEGREE2RADIAN)) );
}

} // namespace math
} // namespace ds