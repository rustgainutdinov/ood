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
        CInputFileStream in("/home/rustamgainutdinov/CLionProjects/ood/lw3/streams/files/a.png");
        auto outFile = make_unique<COutputFileStream>(
                "/home/rustamgainutdinov/CLionProjects/ood/lw3/streams/files/b.png");
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
                "/home/rustamgainutdinov/CLionProjects/ood/lw3/streams/files/b.png");
        auto inDecompressor = make_unique<CStreamDecompressor>(move(inFile));

        auto inDecryption = make_unique<CDecryptionStream>(move(inDecompressor), 7);
        auto outFile = make_unique<COutputFileStream>(
                "/home/rustamgainutdinov/CLionProjects/ood/lw3/streams/files/c.png");
        vector<char> buffer(1000, 0);
        while (!inDecryption->IsEOF())
        {
            streamsize size = inDecryption->ReadBlock(buffer.data(), 1000);
            outFile->WriteBlock(buffer.data(), size);
        }
    }

    return 0;
}