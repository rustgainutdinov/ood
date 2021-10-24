#include "DataStream.h"

#include <fstream>
#include <iostream>

using namespace std;

class CInputFileStream : public IInputDataStream
{

public:
    explicit CInputFileStream(const string &fileName)
    {
        m_fs.open(fileName, ios::in | ios::binary);
    }

    bool IsEOF() const override
    {
        return m_fs.eof();
    }

    uint8_t ReadByte() override
    {
        char byte;
        m_fs.read(&byte, sizeof(uint8_t));
        return static_cast<uint8_t>(byte);
    }

    streamsize ReadBlock(void *dstBuffer, streamsize size) override
    {
        if (m_fs.eof())
        {
            return 0;
        }
        m_fs.read(static_cast<char *>(dstBuffer), size);
        return m_fs.gcount();
    }

    ~CInputFileStream() override
    {
        m_fs.close();
    }

private:
    fstream m_fs;
};

class COutputFileStream : public IOutputDataStream
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