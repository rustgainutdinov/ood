//
// Created by rustam.gainutdinov on 05.12.2021.
//

#ifndef OOD_CSTREAMEDITORCLIENT_H
#define OOD_CSTREAMEDITORCLIENT_H


#include <iostream>
#include <memory>

class IDocument;

class CStreamEditorClient
{
public:
    static std::unique_ptr<IDocument> MakeDocumentFromStream(std::istream &stream);

private:
    static void DoCommand(IDocument &document, const std::string &command);

    static std::optional<size_t> GetPositionByString(const std::string &positionStr);
};


#endif //OOD_CSTREAMEDITORCLIENT_H
