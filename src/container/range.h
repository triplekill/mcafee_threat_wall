#pragma once
#ifndef mcafee_CONTAINER_RANGE_H_
#define mcafee_CONTAINER_RANGE_H_

namespace ds {

/* DS::RANGE
 * A between value ranges.
 ******************************************************************/
template <class T>
class Range
{
public:
	T					mMin, mMax;

public:
    Range();
	Range(const Range<T>&);
	Range(const T& min, const T& max);

	Range<T>&			operator=(const Range<T>&);
	bool				operator==(const Range<T>&) const;
	bool				operator!=(const Range<T>&) const;

	void				set(const T&, const T&);

	T					getCenter() const;

	bool				contains(const T& v) const;
	// True if incoming min is >= my min and incoming max <= my max
	bool				contains(const Range<T>&) const;

	T					translateTo(T v, const Range<T>&) const;

	T					clip(const T& v) const;

	// Limit myself to the value.  Use this by setting min/max
	// to extremes (100000,-100000 or so) and then limiting each
	// value being processed, to find the final range.
	void				limitTo(const T& v);

	// Make T conform to my range by wrapping values that are outside
	// (for example, if my range is 0 - 360, and T is -10, the result
	// will be 350).  This assumes mMax > mMin.
	T					wrap(T) const;

    // Answer a scaled value (0-1) representing where t is withing my range
    double              percent(const T) const;

	// If the value is outside my range, do nothing.  If it's inside,
	// then subtract the smallest area.  I.e., if I'm 10 - 100 and the
	// value is 20, my new range is 20 - 100.  If the value is 85,
	// my new range is 10 - 85;
	void				shave(const T&);

private:
	T					clipForward(const T& v) const;
	T					clipBackward(const T& v) const;
};

/* DS::RANGE implementation
 ******************************************************************/
template <class T>
Range<T>::Range()
{
}

template <class T>
Range<T>::Range(const Range<T>& o)
	: mMin(o.mMin)
	, mMax(o.mMax)
{
}

template <class T>
Range<T>::Range(const T& Min, const T& Max)
	: mMin(Min)
	, mMax(Max)
{
}

template <class T>
Range<T>& Range<T>::operator=(const Range<T>& o)
{
	if (this != &o) {
		mMin = o.mMin;
		mMax = o.mMax;
	}
	return *this;
}

template <class T>
bool Range<T>::operator==(const Range<T>& o) const
{
	return mMin == o.mMin && mMax == o.mMax;
}

template <class T>
bool Range<T>::operator!=(const Range<T>& o) const
{
	return mMin != o.mMin || mMax != o.mMax;
}

template <class T>
void Range<T>::set(const T& _min, const T& _max)
{
	mMin = _min;
	mMax = _max;
}

template <class T>
T Range<T>::getCenter() const
{
	return (mMin + mMax) / 2;
}

template <class T>
bool Range<T>::contains(const T& v) const
{
	return v >= mMin && v <= mMax;
}

template <class T>
bool Range<T>::contains(const Range<T>& o) const
{
	return o.mMin >= mMin && o.mMax <= mMax;
}

template <class T>
T Range<T>::translateTo(T v, const Range<T>& rf) const
{
	if (mMin == mMax || rf.mMin == rf.mMax) {
		return rf.mMin;
	}
	// Translate from source to scaled (0 - 1)
	v = (v - mMin) / (mMax - mMin);
	// Translate from scaled to dest
	v = rf.mMin + (v * (rf.mMax - rf.mMin));
	// Clip
	return rf.clip(v);
}

template <class T>
T Range<T>::clip(const T& v) const
{
	if (mMin < mMax) return clipForward(v);
	else if (mMin > mMax) return clipBackward(v);
	return mMin;
}

template <class T>
void Range<T>::limitTo(const T& v)
{
	if (v < mMin) mMin = v;
	if (v > mMax) mMax = v;
}

template <class T>
T Range<T>::wrap(T v) const
{
	if (v < mMin) {
		const T		range = mMax - mMin;
		while (v < mMin) v += range;
	} else if (v > mMax) {
		const T		range = mMax - mMin;
		while (v > mMax) v -= range;
	}
	return v;
}

template <class T>
double Range<T>::percent(const T v) const
{
    if (v <= mMin) return 0.0;
    else if (v >= mMax) return 1.0;

    return static_cast<double>(v-mMin) / static_cast<double>(mMax-mMin);
}

template <class T>
void Range<T>::shave(const T& v)
{
	if (v <= mMin) return;
	if (v >= mMax) return;

	const T			half = (mMin + mMax) / 2;
	if (v <= half) mMin = v;
	else mMax = v;
}

template <class T>
T Range<T>::clipForward(const T& v) const
{
	return (v <= mMin ? mMin : (v >= mMax ? mMax : v));
}

template <class T>
T Range<T>::clipBackward(const T& v) const
{
	return (v <= mMax ? mMax : (v >= mMin ? mMin : v));
}

/* DS::RANGE defaults
 ******************************************************************/
typedef Range<double>			RangeD;
typedef Range<float>			RangeF;
typedef Range<int>				RangeI;

extern const RangeD				RANGED_ZERO;		// 0 to 0
extern const RangeD				RANGED_UNI;			// 0 to 1
extern const RangeD				RANGED_UNI_INV;		// 1 to 0
extern const RangeD				RANGED_BI;			// -1 to 1
extern const RangeD				RANGED_BI_INV;		// 1 to -1

extern const RangeF				RANGEF_ZERO;		// 0 to 0
extern const RangeF				RANGEF_UNI;			// 0 to 1
extern const RangeF				RANGEF_UNI_INV;		// 1 to 0
extern const RangeF				RANGEF_BI;			// -1 to 1
extern const RangeF				RANGEF_BI_INV;		// 1 to -1

extern const RangeI				RANGEI_ZERO;		// 0 to 0

} // namespace ds

#endif // mcafee_CONTAINER_RANGE_H_
