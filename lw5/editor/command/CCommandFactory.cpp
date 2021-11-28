//
// Created by rustam.gainutdinov on 21.11.2021.
//

#include "CCommandFactory.h"
#include "vector"
#include "lw5/editor/command/commands/CInsertParagraphCommand.h"
#include <sstream>

using namespace std;

vector<string> SplitByChar(const string &str, char ch)
{
    stringstream stringStream(str);
    vector<string> arr;
    string segment;
    while (getline(stringStream, segment, ch))
    {
        arr.push_back(segment);
    }
    return arr;
}

std::unique_ptr<ICommand> CCommandFactory::CreateCommand(std::string descriptionStr)
{
    vector<string> description = SplitByChar(descriptionStr, ' ');
    string name = description[0];
    if (name == "InsertParagraph")
    {
        string text = description[2];
        auto positionStr = description[1];
        std::optional<size_t> position;
        if (positionStr == "end")
        {
            position = nullopt;
        } else
        {
            position = stoi(positionStr);
        }
        return make_unique<CInsertParagraphCommand>(m_document, text, position);
    }
    throw invalid_argument("Invalid command description");
}

CCommandFactory::CCommandFactory(std::shared_ptr<IDocument> document) : m_document(move(document))
{

}
