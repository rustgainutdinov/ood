//
// Created by rustam.gainutdinov on 05.12.2021.
//

#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/CImage.h>
#include <lw5/editor/command/CUndoableCommandExecutor.h>
#include <lw5/editor/command/ICommand.h>
#include <lw5/editor/documentItem/CDocumentItem.h>
#include <lw5/editor/documentItem/IDocumentItem.h>
#include "memory"
#include "lw5/editor/command/documentItem/CDocumentItemListWithCommandExecutor.h"
#include "lw5/editor/CDocument.h"
#include "CStreamEditorClient.h"
#include <sstream>
#include <vector>

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

unique_ptr<IDocument> CStreamEditorClient::MakeDocumentFromStream(std::istream &stream)
{
    auto document = make_unique<CDocument>();
    string s;
    while (getline(stream, s))
    {
        DoCommand(*document, s);
    }
    return document;
}

void CStreamEditorClient::DoCommand(IDocument &document, const std::string &commandStr)
{
    vector<string> commandComponents = SplitByChar(commandStr, ' ');
    if (commandComponents.empty())
    {
        return;
    }
    string commandName = commandComponents[0];
    if (commandName == "InsertParagraph")
    {
        document.InsertParagraph(commandComponents[2], GetPositionByString(commandComponents[1]));
        return;
    }
    if (commandName == "InsertImage")
    {
        document.InsertImage(commandComponents[4], stoi(commandComponents[2]), stoi(commandComponents[3]),
                             GetPositionByString(commandComponents[1]));
        return;
    }
    if (commandName == "SetTitle")
    {
        document.SetTitle(commandComponents[1]);
        return;
    }
    if (commandName == "ResizeImage")
    {
        document.GetItem(stoi(commandComponents[1])).GetImage().value()->Resize(stoi(commandComponents[2]),
                                                                                stoi(commandComponents[3]));
        return;
    }
    if (commandName == "ReplaceText")
    {
        document.GetItem(stoi(commandComponents[1])).GetParagraph().value()->SetText(commandComponents[2]);
        return;
    }
    if (commandName == "DeleteItem")
    {
        document.DeleteItem(stoi(commandComponents[1]));
        return;
    }
    if (commandName == "Undo")
    {
        if (document.CanUndo())
        {
            document.Undo();
        }
        return;
    }
    if (commandName == "Redo")
    {
        if (document.CanRedo())
        {
            document.Redo();
        }
        return;
    }
    if (commandName == "List")
    {
        cout << "Title: " + document.GetTitle() << endl;
        for (int i = 0; i < document.GetItemsCount(); i++)
        {
            IDocumentItem &item = document.GetItem(i);
            if (item.GetImage() != nullopt)
            {
                auto image = item.GetImage().value();
                cout << "Image: " + to_string(image->GetWidth()) + " " + to_string(image->GetHeight()) + " " +
                        image->GetPath() << endl;
            }
            if (item.GetParagraph() != nullopt)
            {
                auto paragraph = item.GetParagraph().value();
                cout << "Paragraph: " + paragraph->GetText() << endl;
            }
        }
        return;
    }
    cout << "Unknown command" << endl;
}

std::optional<size_t> CStreamEditorClient::GetPositionByString(const string &positionStr)
{
    if (positionStr == "end")
    {
        return nullopt;
    }
    return stoi(positionStr);
}
