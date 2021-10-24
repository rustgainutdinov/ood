#include <fstream>
#include <map>
#include <random>
#include <algorithm>

using namespace std;

class CStreamDecompressor : public IInputDataStream
{

public:
    explicit CStreamDecompressor(IInputDataStreamPtr &&stream) : m_stream(move(stream))
    {
    }

    bool IsEOF() const override
    {
        return m_stream->IsEOF();
    }

    uint8_t ReadByte() override
    {
        char *buffer;
        streamsize readSize = ReadBlock(&buffer, 1);
        if (readSize < 1)
        {
            return 0;
        }
        return buffer[0];
    }

    streamsize ReadBlock(void *dstBuffer, streamsize size) override
    {
        streamsize allReadSymbols = FillByBufferSymbols(dstBuffer, size);
        char *chars = static_cast<char *>(dstBuffer);
        while (true)
        {
            if (allReadSymbols >= size || m_stream->IsEOF())
            {
                return allReadSymbols;
            }
            vector<char> buffer(2, 0);
            streamsize readSize = m_stream->ReadBlock(buffer.data(), 2);
            if (readSize == 0)
            {
                return allReadSymbols;
            }
            if (readSize % 2 != 0)
            {
                throw invalid_argument("file decompression error");
            }
            char symbol = buffer[0];
            int symbolsCount = static_cast<int>(static_cast<unsigned char>(buffer[1]));
            if (allReadSymbols + symbolsCount <= size)
            {
                for (int i = 0; i < symbolsCount; i++)
                {
                    chars[allReadSymbols + i] = symbol;
                }
                allReadSymbols += symbolsCount;
            } else
            {
                for (int i = 0; i < size - allReadSymbols; i++)
                {
                    chars[allReadSymbols + i] = symbol;
                }
                allReadSymbols = size;
                bufferSymbolsCount = symbolsCount - (size - allReadSymbols);
                bufferSymbol = symbol;
            }
        }
    }

private:

    streamsize FillByBufferSymbols(void *dstBuffer, streamsize size)
    {
        if (bufferSymbolsCount == 0)
        {
            return 0;
        }
        char *chars = static_cast<char *>(dstBuffer);
        if (size > bufferSymbolsCount)
        {
            for (int i = 0; i < bufferSymbolsCount; i++)
            {
                chars[i] = bufferSymbol;
            }
            bufferSymbolsCount = 0;
            return bufferSymbolsCount;
        }
        for (int i = 0; i < size; i++)
        {
            chars[i] = bufferSymbol;
        }
        bufferSymbolsCount -= size;
        return size;
    }

    char bufferSymbol{};
    streamsize bufferSymbolsCount = 0;
    IInputDataStreamPtr m_stream;
};

class CStreamCompressor : public IOutputDataStream
{

public:
    explicit CStreamCompressor(IOutputDataStreamPtr &&stream) : m_stream(move(stream))
    {
    }

    void WriteByte(uint8_t data) override
    {
        WriteRepeatedSymbol(data, 1);
    }

    void WriteBlock(const void *srcData, std::streamsize size) override
    {
        auto *chars = static_cast<uint8_t *>(const_cast<void *>(srcData));
        uint8_t prevSymbol;
        streamsize repeatedSymbolsCount = 0;
        for (int i = 0; i < size; i++)
        {
            uint8_t currSymbol = chars[i];
            if (i == 0)
            {
                prevSymbol = currSymbol;
                repeatedSymbolsCount = 1;
                continue;
            }
            if (prevSymbol == currSymbol || repeatedSymbolsCount >= 255)
            {
                repeatedSymbolsCount++;
                continue;
            }
            WriteRepeatedSymbol(prevSymbol, repeatedSymbolsCount);
            prevSymbol = currSymbol;
            repeatedSymbolsCount = 1;
        }
        WriteRepeatedSymbol(prevSymbol, repeatedSymbolsCount);
    }

private:
    void WriteRepeatedSymbol(uint8_t symbol, streamsize repeatedSymbolsCount)
    {
        m_stream->WriteByte(symbol);
        m_stream->WriteByte((int) repeatedSymbolsCount);
    }

    IOutputDataStreamPtr m_stream;
};