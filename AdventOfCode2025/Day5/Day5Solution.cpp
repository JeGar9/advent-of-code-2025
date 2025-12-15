#include "Day5Solution.h"

#include <algorithm>
#include <iostream>
#include <ostream>

using namespace std;

namespace Day5 {

    using ull_t = unsigned long long;

    class Interval {
    public:
        ull_t start;
        ull_t end;
        Interval() : Interval(0, 0) {};
        Interval(ull_t start, ull_t end) : start(start), end(end) {}
    };

    class Data {
    public:
        vector<Interval> intervals;
        vector<ull_t> ids;
        void collapseAndOrderIntervals() {
            sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start < b.start;});
            vector<Interval> newIntervals;
            for (int i = 0; i < intervals.size(); ++i) {
                Interval& interval = intervals[i];
                if (i == 0) {
                    newIntervals.emplace_back(interval.start, interval.end);
                } else {
                    Interval& prevInterval = newIntervals[newIntervals.size() - 1];
                    if (prevInterval.end >= interval.start) {
                        if (interval.end > prevInterval.end) {
                            prevInterval.end = interval.end;
                        }
                    } else {
                        newIntervals.emplace_back(interval.start, interval.end);
                    }
                }
            }
            intervals = newIntervals;
        }
    };

    void read_lines(const vector<string>& lines, Data & data) {
        bool readIntervals = false;
        for (const string & s: lines) {
            if (s.empty()) {
                readIntervals = true;
            } else if (readIntervals) {
                data.ids.emplace_back(stoull(s));
            } else {
                size_t delim_pos = s.find('-');
                size_t length = s.length() - delim_pos;
                data.intervals.emplace_back(
                    stoull(s.substr(0, delim_pos)),
                    stoull(s.substr(delim_pos + 1, length))
                );
            }
        }
    }

    string solve1(const vector<string>& input) {
        ull_t sum = 0;
        Data data;
        read_lines(input, data);
        data.collapseAndOrderIntervals();
        for (const ull_t id : data.ids) {
            auto val = lower_bound(
                data.intervals.begin(), data.intervals.end(),
                Interval(id, id), [](auto& a, auto& b) { return a.start < b.start; });
            if (val != data.intervals.end()) {
                auto& interval = *val;
                if (interval.start <= id && id <= interval.end) {
                    sum++;
                }
            }
            if (val != data.intervals.begin()) {
                auto& prev = *(val - 1);
                if (prev.start <= id && id <= prev.end) {
                    sum++;
                }
            }
        }
        return to_string(sum);
    }

    string solve2(const vector<string>& input) {
        ull_t sum = 0;
        Data data;
        read_lines(input, data);
        data.collapseAndOrderIntervals();
        for (const Interval& interval : data.intervals) {
            sum += interval.end - interval.start + 1;
        }
        return to_string(sum);
    }
}