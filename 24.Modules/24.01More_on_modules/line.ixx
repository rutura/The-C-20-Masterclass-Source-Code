module;

export module line;

export import point;

namespace more_on_modules_02{

    export class Line {
    public:
        Line(Point start, Point end) : m_start(start), m_end(end) {}
        Point start() const { return m_start; }
        Point end() const { return m_end; }
    private:
        Point m_start;
        Point m_end;
    };
}