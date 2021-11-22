class CDesigner;

class CPainter;

class CClient
{
public:
    ~CClient();

    CClient(CDesigner &designer, CPainter &painter);

    void GetPicture();

private:
    CDesigner &m_designer;
    CPainter &m_painter;
};