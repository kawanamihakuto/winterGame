#include "IntervalChecker.h"

IntervalChecker::IntervalChecker(int n):
	timer_(0),
	interval_(n)
{
}

bool IntervalChecker::Check()
{
	if (--timer_ <= 0)
	{
		return true;
	}

	return false;
}

void IntervalChecker::ResetTimer()
{
	timer_ = interval_;
}
