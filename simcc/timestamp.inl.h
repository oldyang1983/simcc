#pragma once

#include "gettimeofday.h"

namespace simcc {
inline Timestamp::Timestamp()
    : ns_(0) {}

inline Timestamp::Timestamp(int64_t nanoseconds)
    : ns_(nanoseconds) {}

inline bool Timestamp::IsEpoch() const {
    return ns_ == 0;
}

inline Timestamp::Timestamp(const struct timeval& t)
    : ns_(int64_t(t.tv_sec) * Duration::kSecond + t.tv_usec * Duration::kMicrosecond) {}

inline Timestamp Timestamp::Now() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t ns = int64_t(tv.tv_sec) * Duration::kSecond + int64_t(tv.tv_usec) * Duration::kMicrosecond;
    return Timestamp(ns);
}

inline void Timestamp::Add(Duration d) {
    ns_ += d.Nanoseconds();
}

inline void Timestamp::To(struct timeval* t) const {
    t->tv_sec = (long)(ns_ / Duration::kSecond);
    t->tv_usec = (long)(ns_ % Duration::kSecond) / (long)Duration::kMicrosecond;
}

inline struct timeval Timestamp::TimeVal() const {
    struct timeval t;
    To(&t);
    return t;
}

inline int64_t Timestamp::Unix() const {
    return ns_ / Duration::kSecond;
}

inline int64_t Timestamp::UnixNano() const {
    return ns_;
}

inline bool Timestamp::operator<(const Timestamp& rhs) const {
    return ns_ < rhs.ns_;
}

inline bool Timestamp::operator==(const Timestamp& rhs) const {
    return ns_ == rhs.ns_;
}

inline Timestamp Timestamp::operator+=(const Duration& rhs) {
    ns_ += rhs.Nanoseconds();
    return *this;
}

inline Timestamp Timestamp::operator+(const Duration& rhs) const {
    Timestamp temp(*this);
    temp += rhs;
    return temp;
}

inline Timestamp Timestamp::operator-=(const Duration& rhs) {
    ns_ -= rhs.Nanoseconds();
    return *this;
}

inline Timestamp Timestamp::operator-(const Duration& rhs) const {
    Timestamp temp(*this);
    temp -= rhs;
    return temp;
}

inline Duration Timestamp::operator-(const Timestamp& rhs) const {
    int64_t ns = ns_ - rhs.ns_;
    return Duration(ns);
}
} // namespace simcc

