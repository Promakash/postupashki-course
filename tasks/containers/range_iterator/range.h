#pragma once

class RangeIt {
};

class Range {
public:
    Range(int start, int end, int step);

    Range(int start, int end);

    Range(int end);

    RangeIt begin();

    RangeIt end();
};