#include <cmath>
#include "sky_rate_limit.h"

FixedWindowRateLimitor::FixedWindowRateLimitor(int64_t rate, int seconds) : rate(rate), currentCount(0), resetLock(false) {
    if (seconds < 1) {
        timeWindow = std::chrono::seconds(1);
    } else {
        timeWindow = std::chrono::seconds(seconds);
    }
}

bool FixedWindowRateLimitor::validate() {
    if (this->rate < 1) {
        return true;
    }

    TimePoint now = TimePoint::clock::now();
    std::chrono::duration<double> span = now - this->startTime;

    bool falseValue = false;
    if (span > this->timeWindow && resetLock.compare_exchange_weak(falseValue, true)) {
        int64_t timeSpan = static_cast<int64_t>(floor(span.count()));
        timeSpan = timeSpan - timeSpan % this->timeWindow.count();

        this->startTime += std::chrono::seconds(timeSpan);
        this->currentCount.store(0);

        resetLock.store(false);
    }

    if (++this->currentCount > this->rate && span < this->timeWindow) {
        return false;
    }

    return true;
}