#pragma once
struct Rect {
    int left, right, top, bottom;

    // Constructor
    Rect(int l = 0, int r = 0, int b = 0, int t = 0)
        : left(l), right(r), bottom(b), top(t) {}

    // Convenience methods
    int width() const { return right - left; }
    int height() const { return top - bottom; }
    int area() const { return width() * height(); }
};