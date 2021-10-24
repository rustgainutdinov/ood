#include <fstream>
#include <map>
#include <random>
#include <algorithm>

using namespace std;

map<char, char> GenerateEncryptionTable(int key)
{
    std::array<int, 255> randNums{};
    for (int i = 0; i < 256; i++)
    {
        randNums[i] = i;
    }
    mt19937 mt_key(key);
    shuffle(randNums.begin(), randNums.end(), mt_key);
    map<char, char> m;
    for (int i = 0; i < 256; i++)
    {
        m[static_cast<char>(i)] = static_cast<char>(randNums[i]);
    }
    return m;
}

map<char, char> GenerateDecryptionTable(int key)
{
    map<char, char> m = GenerateEncryptionTable(key);
    map<char, char> flipped;
    for (auto & i : m)
        flipped[i.second] = i.first;
    return flipped;
}

class CDecryptionStream : public IInputDataStream
{

public:
    CDecryptionStream(IInputDataStreamPtr &&stream, int key) : m_stream(move(stream))
    {
        decryptionMap = GenerateDecryptionTable(key);
    }

    bool IsEOF() const override
    {
        return m_stream->IsEOF();
    }

    uint8_t ReadByte() override
    {
        return static_cast<uint8_t >(decryptionMap[static_cast<char >(m_stream->ReadByte())]);
    }

    streamsize ReadBlock(void *dstBuffer, streamsize size) override
    {
        streamsize readSize = m_stream->ReadBlock(dstBuffer, size);
        char *chars = static_cast<char *>(dstBuffer);
        for (int i = 0; i < readSize; i++)
        {
            chars[i] = decryptionMap[chars[i]];
        }
        return readSize;
    }

private:
    IInputDataStreamPtr m_stream;
    map<char, char> decryptionMap;
};

class CEncryptionStream : public IOutputDataStream
{

public:
    CEncryptionStream(IOutputDataStreamPtr &&stream, int key) : m_stream(move(stream))
    {
        encryptionMap = GenerateEncryptionTable(key);
    }

    void WriteByte(uint8_t data) override
    {
        m_stream->WriteByte(static_cast<uint8_t >(encryptionMap[static_cast<char >(data)]));
    }

    void WriteBlock(const void *srcData, std::streamsize size) override
    {
        char *chars = static_cast<char *>(const_cast<void *>(srcData));
        for (int i = 0; i < size; i++)
        {
            chars[i] = encryptionMap[chars[i]];
        }
        m_stream->WriteBlock(chars, size);
    }

private:
    IOutputDataStreamPtr m_stream;
    map<char, char> encryptionMap;
};