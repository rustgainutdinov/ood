#include "DataStream.h"

#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

class CInputMemoryStream : public IInputDataStream
{

public:
    explicit CInputMemoryStream(vector<char> chars)
    {
        charsList = std::move(chars);
    }

    bool IsEOF() const override
    {
        return charsList.empty();
    }

    uint8_t ReadByte() override
    {
        char ch = charsList[0];
        charsList.erase(charsList.begin());
        return ch;
    }

    streamsize ReadBlock(void *dstBuffer, streamsize size) override
    {
        charsList.
        streamsize readSize = 0;
        while (!IsEOF() || readSize >= size)
        {

            readSize++;
        }
        return readSize;
    }

private:
    vector<char> charsList;
};

class COutputMemoryStream : public IOutputDataStream
{

public:
    explicit COutputFileStream(const string &fileName)
    {
        m_fs.open(fileName, ios::out | ios::binary);
    }

    void WriteByte(uint8_t data) override
    {
        m_fs.write((char *) &data, sizeof(uint8_t));
    }

    void WriteBlock(const void *srcData, std::streamsize size) override
    {
        m_fs.write(static_cast<const char *>(srcData), size);
    }

    ~COutputFileStream() override
    {
        m_fs.close();
    }

private:
    fstream m_fs;
};