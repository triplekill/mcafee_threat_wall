#pragma once
#ifndef DS_MATH_CIRCLE_H_
#define DS_MATH_CIRCLE_H_

#include <cinder/Vector.h>
#include "container/range.h"

namespace ds {
namespace math {

/**
 * \class ds::math::Circle
 */
class Circle {
public:
	Circle();
	Circle(const ci::Vec2f& center, const float radius);

	float				getCircumference() const;
	// Get the cirumference of the degree range
	float				getCircumference(const ds::RangeF&) const;

	ci::Vec2f			getPoint(float degree) const;

	ci::Vec2f			mCenter;
	float				mRadius;
};

} // namespace math
} // namespace ds

#endif // DS_MATH_CIRCLE_H_
