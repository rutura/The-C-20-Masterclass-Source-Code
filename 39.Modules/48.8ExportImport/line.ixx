module;

export module Line;

export import Point;

export class Line {
public:
    Line(Point start, Point end) : start_(start), end_(end) {}
    Point start() const { return start_; }
    Point end() const { return end_; }
private:
    Point start_;
    Point end_;
};