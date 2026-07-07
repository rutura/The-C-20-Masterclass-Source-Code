module;

export module Point;

export class Point {
public:
    Point(int x, int y) : x_(x), y_(y) {}
    int x() const { return x_; }
    int y() const { return y_; }
private:
    int x_;
    int y_;
};