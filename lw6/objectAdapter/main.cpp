#include <iostream>
#include <stdexcept>

using namespace std;

namespace graphics_lib
{
    class ICanvas
    {
    public:
        virtual void MoveTo(int x, int y) = 0;

        virtual void LineTo(int x, int y) = 0;

        virtual ~ICanvas() = default;
    };

    class CCanvas : public ICanvas
    {
    public:
        void MoveTo(int x, int y) override
        {
            cout << "MoveTo (" << x << ", " << y << ")" << endl;
        }

        void LineTo(int x, int y) override
        {
            cout << "LineTo (" << x << ", " << y << ")" << endl;
        }
    };
}

namespace shape_drawing_lib
{
    struct Point
    {
        int x;
        int y;
    };

    class ICanvasDrawable
    {
    public:
        virtual void Draw(graphics_lib::ICanvas &canvas) const = 0;

        virtual ~ICanvasDrawable() = default;
    };

    class CTriangle : public ICanvasDrawable
    {
    public:
        CTriangle(const Point &p1, const Point &p2, const Point &p3) : m_p1(p1), m_p2(p2), m_p3(p3)
        {
        }

        void Draw(graphics_lib::ICanvas &canvas) const override
        {
            canvas.MoveTo(m_p1.x, m_p1.y);
            canvas.LineTo(m_p2.x, m_p2.y);
            canvas.LineTo(m_p3.x, m_p3.y);
            canvas.LineTo(m_p1.x, m_p1.y);
        }

    private:
        Point m_p1;
        Point m_p2;
        Point m_p3;
    };

    class CRectangle : public ICanvasDrawable
    {
    public:
        CRectangle(const Point &leftTop, int width, int height) : m_leftTop(leftTop), m_width(width), m_height(height)
        {
        }

        void Draw(graphics_lib::ICanvas &canvas) const override
        {
            canvas.MoveTo(m_leftTop.x, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y);
        }

    private:
        Point m_leftTop;
        int m_width;
        int m_height;
    };

    class CCanvasPainter
    {
    public:
        explicit CCanvasPainter(graphics_lib::ICanvas &canvas) : m_canvas(canvas)
        {
        }

        void Draw(const ICanvasDrawable &drawable)
        {
            drawable.Draw(m_canvas);
        }

    private:
        graphics_lib::ICanvas &m_canvas;
    };
}

namespace modern_graphics_lib
{
    class CPoint
    {
    public:
        CPoint(int x, int y) : x(x), y(y)
        {}

        int x;
        int y;
    };

    class CModernGraphicsRenderer
    {
    public:
        CModernGraphicsRenderer(ostream &strm) : m_out(strm)
        {
        }

        ~CModernGraphicsRenderer()
        {
            if (m_drawing)
            {
                EndDraw();
            }
        }

        void BeginDraw()
        {
            if (m_drawing)
            {
                throw logic_error("Drawing has already begun");
            }
            m_out << "<draw>" << endl;
            m_drawing = true;
        }

        void DrawLine(const CPoint &start, const CPoint &end) const
        {
            if (!m_drawing)
            {
                throw logic_error("MoveTo is allowed between BeginDraw()/EndDraw() only");
            }
            char s[100];
            sprintf(s, "  <line fromX=%d fromY=%d toX=%d toY=%d/>", start.x, start.y, end.x, end.y);
            m_out << s << endl;
        }

        void EndDraw()
        {
            if (!m_drawing)
            {
                throw logic_error("Drawing has not been started");
            }
            m_out << "</draw>" << endl;
            m_drawing = false;
        }

    private:
        ostream &m_out;
        bool m_drawing = false;
    };
}

namespace modern_graphics_adapter
{
    class CModernGraphicsRendererObjectAdapter : public graphics_lib::ICanvas
    {
    public:
        explicit CModernGraphicsRendererObjectAdapter(
                modern_graphics_lib::CModernGraphicsRenderer &modernGraphicsRenderer)
                : m_modernGraphicsRenderer(modernGraphicsRenderer)
        {}

        void MoveTo(int x, int y) override
        {
            m_currentPointPosition = modern_graphics_lib::CPoint(x, y);
        }

        void LineTo(int x, int y) override
        {
            auto pointTo = modern_graphics_lib::CPoint(x, y);
            m_modernGraphicsRenderer.DrawLine(m_currentPointPosition, pointTo);
            m_currentPointPosition = pointTo;
        }

    private:
        modern_graphics_lib::CModernGraphicsRenderer &m_modernGraphicsRenderer;
        modern_graphics_lib::CPoint m_currentPointPosition{0, 0};
    };

    class CModernGraphicsRendererClassAdapter
            : public graphics_lib::ICanvas, private modern_graphics_lib::CModernGraphicsRenderer
    {
    public:
        explicit CModernGraphicsRendererClassAdapter(ostream &strm) : CModernGraphicsRenderer(strm)
        {}

        ~CModernGraphicsRendererClassAdapter() override
        {
            if (m_hasDrawingBegun)
            {
                EndDraw();
            }
        }

        void MoveTo(int x, int y) override
        {
            m_currentPointPosition = modern_graphics_lib::CPoint(x, y);
        }

        void LineTo(int x, int y) override
        {
            if (!m_hasDrawingBegun)
            {
                BeginDraw();
                m_hasDrawingBegun = true;
            }
            auto pointTo = modern_graphics_lib::CPoint(x, y);
            DrawLine(m_currentPointPosition, pointTo);
            m_currentPointPosition = pointTo;
        }

    private:
        modern_graphics_lib::CPoint m_currentPointPosition{0, 0};
        bool m_hasDrawingBegun = false;
    };
}


namespace app
{
    void PaintPicture(shape_drawing_lib::CCanvasPainter &painter)
    {
        using namespace shape_drawing_lib;

        CTriangle triangle({10, 15}, {100, 200}, {150, 250});
        CRectangle rectangle({30, 40}, 18, 24);

        painter.Draw(triangle);
        painter.Draw(rectangle);
    }

    void PaintPictureOnCanvas()
    {
        graphics_lib::CCanvas simpleCanvas;
        shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
        PaintPicture(painter);
    }

    void PaintPictureOnModernGraphicsRendererWithObjectAdapter()
    {
        modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
        renderer.BeginDraw();
        modern_graphics_adapter::CModernGraphicsRendererObjectAdapter rendererAdapter(renderer);
        shape_drawing_lib::CCanvasPainter painter(rendererAdapter);
        PaintPicture(painter);
    }

    void PaintPictureOnModernGraphicsRendererWithClassAdapter()
    {
        modern_graphics_adapter::CModernGraphicsRendererClassAdapter rendererAdapter(cout);
        shape_drawing_lib::CCanvasPainter painter(rendererAdapter);
        PaintPicture(painter);
    }
}

int main()
{
    app::PaintPictureOnCanvas();
    app::PaintPictureOnModernGraphicsRendererWithObjectAdapter();
    app::PaintPictureOnModernGraphicsRendererWithClassAdapter();
}