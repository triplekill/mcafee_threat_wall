#include "util/time_seconds.h"

namespace ds {
namespace time {

namespace {
const double			RESOLUTION_D = static_cast<double>(Poco::Timestamp::resolution());
}

/**
 * \class ds::time::Seconds
 */
Seconds::Seconds() {
	restart();
}

void Seconds::restart() {
	mStart = Poco::Timestamp().epochMicroseconds();
}

double Seconds::elapsed() {
	Poco::Timestamp::TimeVal	tv = Poco::Timestamp().epochMicroseconds() - mStart;
	return static_cast<double>(tv) / RESOLUTION_D;
}

} // namespace time
} // namespace ds