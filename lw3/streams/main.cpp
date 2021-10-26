#include "FIleStream.h"
#include "StreamEncription.h"
#include "StreamCompression.h"

#include "vector"
#include "iostream"

using namespace std;

int main()
{
//    {
//        map<char, char> m = GenerateEncryptionTable(7);
//        auto it = m.begin();
//        while (it != m.end())
//        {
//            cout << static_cast<int>(it->first) << ": " << static_cast<int>(it->second) << endl;
//            it++;
//        }
//        map<char, char> m2 = GenerateDecryptionTable(7);
//        it = m2.begin();
//        while (it != m2.end())
//        {
//            cout << static_cast<int>(it->first) << ": " << static_cast<int>(it->second) << endl;
//            it++;
//        }
//    }
    {
        CInputFileStream in("/Users/rustamgajnutdinov/Documents/study/ood/lw3/streams/files/a.txt");
        auto outFile = make_unique<COutputFileStream>(
                "/Users/rustamgajnutdinov/Documents/study/ood/lw3/streams/files/b.txt");
        auto outCompressor = make_unique<CStreamCompressor>(move(outFile));

        auto outEncryption = make_unique<CEncryptionStream>(move(outCompressor), 7);
        vector<char> buffer(1000, 0);
        while (!in.IsEOF())
        {
            streamsize size = in.ReadBlock(buffer.data(), 1000);
            outEncryption->WriteBlock(buffer.data(), size);
        }
    }
    {
        auto inFile = make_unique<CInputFileStream>(
                "/Users/rustamgajnutdinov/Documents/study/ood/lw3/streams/files/b.txt");
        auto inDecompressor = make_unique<CStreamDecompressor>(move(inFile));

        auto inDecryption = make_unique<CDecryptionStream>(move(inDecompressor), 7);
        auto outFile = make_unique<COutputFileStream>(
                "/Users/rustamgajnutdinov/Documents/study/ood/lw3/streams/files/c.txt");
        vector<char> buffer(1000, 0);
        while (!inDecryption->IsEOF())
        {
            streamsize size = inDecryption->ReadBlock(buffer.data(), 1000);
            outFile->WriteBlock(buffer.data(), size);
        }
    }

    return 0;
}