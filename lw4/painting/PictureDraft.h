#include <utility>
#include <vector>

using namespace std;

//TODO: для чего нужен IPictureDraft
class IPictureDraft
{
public:
    virtual size_t GetShapeCount() = 0;

    virtual unique_ptr<CShape> GetShape(int index) = 0;

    virtual void AddShape(unique_ptr<CShape> shape) = 0;
};

class CPictureDraft : IPictureDraft
{
public:
    size_t GetShapeCount() override
    {
        return m_shapes.size();
    }

    //TODO: удаляет фигуру, исправить
    unique_ptr<CShape> GetShape(int index) override
    {
        return move(m_shapes[index]);
    }

    void AddShape(unique_ptr<CShape> shape) override
    {
        return m_shapes.push_back(move(shape));
    }

private:
    vector<unique_ptr<CShape>> m_shapes{};
};