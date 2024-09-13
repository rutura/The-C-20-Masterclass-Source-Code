export module point;

namespace more_on_modules_02{

    export class Point {
    public:
        Point(int x, int y) : m_x(x), m_y(y) {}
        int x() const { return m_x; }
        int y() const { return m_y; }
    private:
        int m_x;
        int m_y;
    };
}