class IPictureDraftInfo;

class ICanvas;

class CPainter
{
public:
    static void DrawPicture(IPictureDraftInfo &draft, ICanvas &canvas);

    ~CPainter();
};