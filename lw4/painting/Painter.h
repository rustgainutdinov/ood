class IPictureDraftInfo;

class ICanvas;

class CPainter
{
public:
    static void DrawPicture(const IPictureDraftInfo &draft, ICanvas &canvas);

    ~CPainter();
};