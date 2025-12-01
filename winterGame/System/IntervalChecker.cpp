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
		timer_ = interval_;
		return true;
	}

	return false;
}
