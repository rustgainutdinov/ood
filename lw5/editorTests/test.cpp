#include <gtest/gtest.h>
#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/CImage.h>
#include <lw5/editor/command/CUndoableCommandExecutor.h>
#include <lw5/editor/command/ICommand.h>
#include <lw5/editor/documentItem/CDocumentItemList.h>
#include <lw5/editor/documentItem/CDocumentItem.h>
#include <lw5/editor/command/commands/CAddDocumentItemToListCommand.h>
#include <lw5/editor/command/commands/CDeleteDocumentItemFromListCommand.h>
#include <lw5/editor/command/content/CImageWithCommandExecutor.h>
#include <utility>
#include "memory"
#include "optional"
#include "lw5/editor/command/documentItem/CDocumentItemListWithCommandExecutor.h"
#include "lw5/editor/CDocument.h"
#include "lw5/editor/command/content/CParagraphWithCommandExecutor.h"

using namespace std;

class TestDocumentItem : public ::testing::Test
{
};

TEST_F(TestDocumentItem, shouldBeCoustructedWithOnlyOneParameter)
{
    auto paragraph = make_shared<CParagraph>("text");
    auto image = make_shared<CImage>("path", 100, 100);
    make_unique<CDocumentItem>(paragraph);
    make_unique<CDocumentItem>(nullopt, image);
    ASSERT_THROW(make_unique<CDocumentItem>(), invalid_argument);
    ASSERT_THROW(make_unique<CDocumentItem>(paragraph, image), invalid_argument);
}


class TestDocumentItemList : public ::testing::Test
{
};

TEST_F(TestDocumentItemList, shouldAddItemsToPositionAndToEnd)
{
    auto list = make_unique<CDocumentItemList>();
    auto item1 = make_unique<CDocumentItem>(nullopt, move(make_shared<CImage>("path 1", 1, 2)));
    auto item2 = make_unique<CDocumentItem>(nullopt, move(make_shared<CImage>("path 2", 1, 2)));
    auto item3 = make_unique<CDocumentItem>(nullopt, move(make_shared<CImage>("path 3", 1, 2)));
    ASSERT_EQ(list->GetSize(), 0);
    list->Add(move(item1));
    list->Add(move(item2), 1);
    list->Add(move(item3), 0);
    ASSERT_EQ(list->GetSize(), 3);
    ASSERT_EQ(list->Get(0).GetImage().value()->GetPath(), "path 3");
    ASSERT_EQ(list->Get(2).GetImage().value()->GetPath(), "path 2");
    ASSERT_EQ(list->Get(1).GetImage().value()->GetPath(), "path 1");
    list->Get(1).GetImage().value()->Resize(10, 10);
    ASSERT_EQ(list->Get(1).GetImage().value()->GetWidth(), 10);
    ASSERT_EQ(list->Get(1).GetImage().value()->GetHeight(), 10);
}

TEST_F(TestDocumentItemList, shouldAddItemsInExistingPositions)
{
    auto list = make_unique<CDocumentItemList>();
    auto item1 = make_unique<CDocumentItem>(nullopt, move(make_shared<CImage>("path 1", 1, 2)));
    ASSERT_THROW(list->Add(move(item1), 1), invalid_argument);
    list->Add(move(item1), 0);
    ASSERT_THROW(list->Add(move(item1), 2), invalid_argument);
}

TEST_F(TestDocumentItemList, shouldDeleteOnlyExistingItems)
{
    auto list = make_unique<CDocumentItemList>();
    auto item1 = make_unique<CDocumentItem>(nullopt, move(make_shared<CImage>("path 1", 1, 2)));
    auto item2 = make_unique<CDocumentItem>(nullopt, move(make_shared<CImage>("path 2", 1, 2)));
    ASSERT_THROW(list->Delete(0), invalid_argument);
    list->Add(move(item1));
    list->Add(move(item2), 0);
    ASSERT_THROW(list->Delete(2), invalid_argument);
    list->Delete(1);
    list->Delete(0);
}

class TestUndoableCommandExecutor : public ::testing::Test
{
};

class MockCommand : public ICommand
{
public:
    explicit MockCommand(string name, string &mutableStr) : m_name(move(name)), m_mutableStr(mutableStr)
    {}

    void Execute() override
    {
        m_mutableStr = m_name + "executed";
    }

    void CancelExecution() override
    {
        m_mutableStr = m_name + "unexecuted";
    }

private:
    string m_name;
    string &m_mutableStr;
};

TEST_F(TestUndoableCommandExecutor, shouldUndoCommands)
{
    auto executor = make_unique<CUndoableCommandExecutor>();
    string mutableStr;
    auto command1 = make_unique<MockCommand>("command1", mutableStr);
    auto command2 = make_unique<MockCommand>("command2", mutableStr);
    executor->Add(move(command1));
    ASSERT_EQ(mutableStr, "command1executed");
    executor->Add(move(command2));
    ASSERT_EQ(mutableStr, "command2executed");
    executor->Undo();
    ASSERT_EQ(mutableStr, "command2unexecuted");
    executor->Undo();
    ASSERT_EQ(mutableStr, "command1unexecuted");
}

TEST_F(TestUndoableCommandExecutor, shouldRedoCommands)
{
    auto executor = make_unique<CUndoableCommandExecutor>();
    string mutableStr;
    auto command1 = make_unique<MockCommand>("command1", mutableStr);
    auto command2 = make_unique<MockCommand>("command2", mutableStr);
    executor->Add(move(command1));
    ASSERT_EQ(mutableStr, "command1executed");
    executor->Add(move(command2));
    ASSERT_EQ(mutableStr, "command2executed");
    executor->Undo();
    ASSERT_EQ(mutableStr, "command2unexecuted");
    executor->Undo();
    ASSERT_EQ(mutableStr, "command1unexecuted");
    executor->Redo();
    ASSERT_EQ(mutableStr, "command1executed");
    executor->Redo();
    ASSERT_EQ(mutableStr, "command2executed");
}

TEST_F(TestUndoableCommandExecutor, shouldClearCommandListIfGoneOnAnotherBranch)
{
    auto executor = make_unique<CUndoableCommandExecutor>();
    string mutableStr;
    auto command1 = make_unique<MockCommand>("command1", mutableStr);
    auto command2 = make_unique<MockCommand>("command2", mutableStr);
    auto command3 = make_unique<MockCommand>("command3", mutableStr);
    executor->Add(move(command1));
    executor->Add(move(command2));
    executor->Undo();
    executor->Add(move(command3));
    executor->Undo();
    ASSERT_EQ(mutableStr, "command3unexecuted");
    executor->Undo();
    ASSERT_EQ(mutableStr, "command1unexecuted");
}

class TestImageResource : public ::testing::Test
{
};

TEST_F(TestImageResource, shouldDeleteResourceIfMarkedAsDeletedAndNotInUse)
{
    auto image = make_shared<CImage>("path 1", 1, 2);
    ASSERT_EQ(image->IsResourceExist(), true);
    image->Capture();
    image->Release();

    image->Capture();
    image->MarkAsDeleted();
    image->Capture();
    image->Release();
    image->MarkAsNotDeleted();
    image->Release();

    image->Capture();
    image->Capture();
    image->MarkAsDeleted();
    image->Release();
    ASSERT_EQ(image->IsResourceExist(), true);
    image->Release();
    ASSERT_EQ(image->IsResourceExist(), false);
}

class TestImageResourceCommands : public ::testing::Test
{
};

class CTestDocumentItem : public CDocumentItem
{
public:
    explicit CTestDocumentItem(optional<shared_ptr<CParagraph>> paragraph = nullopt,
                               optional<shared_ptr<IImageResource>> image = nullopt) : CDocumentItem(move(paragraph),
                                                                                                     move(image))
    {
    }

    bool IsResourceExist()
    {
        if (m_image != nullopt)
        {
            return m_image.value()->IsResourceExist();
        }
        return false;
    }
};

TEST_F(TestImageResourceCommands, shouldDeleteResourceIfMarkedAsDeletedAndNotInUse)
{
    auto item = make_unique<CTestDocumentItem>(nullopt, move(make_shared<CImage>("path 1", 1, 2)));
    auto list = make_shared<CDocumentItemList>();
    auto command1 = make_unique<CAddDocumentItemToListCommand>(list, move(item), nullopt);
    command1->Execute();
    auto documentItem = reinterpret_cast<CTestDocumentItem &>(list->Get(0));

    ASSERT_EQ(documentItem.IsResourceExist(), true);
    command1.reset();
    ASSERT_EQ(documentItem.IsResourceExist(), true);
    auto command2 = make_unique<CDeleteDocumentItemFromListCommand>(list, 0);
    command2->Execute();
    command2.reset();
    ASSERT_EQ(documentItem.IsResourceExist(), false);
}

class TestImageWithCommandExecutor : public ::testing::Test
{
};

TEST_F(TestImageWithCommandExecutor, shouldBeUndoable)
{
    auto executor = make_unique<CUndoableCommandExecutor>();
    auto baseImage = make_unique<CImage>("path 1", 1, 2);
    auto image = make_unique<CImageWithCommandExecutor>(move(baseImage), *executor);
    image->Resize(3, 4);
    ASSERT_EQ(image->GetWidth(), 3);
    ASSERT_EQ(image->GetHeight(), 4);
    executor->Undo();
    ASSERT_EQ(image->GetWidth(), 1);
    ASSERT_EQ(image->GetHeight(), 2);
    executor->Redo();
    ASSERT_EQ(image->GetWidth(), 3);
    ASSERT_EQ(image->GetHeight(), 4);
}

class TestParagraphWithCommandExecutor : public ::testing::Test
{
};

TEST_F(TestParagraphWithCommandExecutor, shouldBeUndoable)
{
    auto executor = make_unique<CUndoableCommandExecutor>();
    auto baseImage = make_unique<CParagraph>("text1");
    auto image = make_unique<CParagraphWithCommandExecutor>(move(baseImage), *executor);
    image->SetText("text2");
    ASSERT_EQ(image->GetText(), "text2");
    executor->Undo();
    ASSERT_EQ(image->GetText(), "text1");
    executor->Redo();
    ASSERT_EQ(image->GetText(), "text2");
}

class TestDocumentItemListWithCommandExecutor : public ::testing::Test
{
};

TEST_F(TestDocumentItemListWithCommandExecutor, shouldBeUndoable)
{
    auto list = make_shared<CDocumentItemList>();
    auto executor = make_unique<CUndoableCommandExecutor>();
    auto listWithCommandExecutor = make_unique<CDocumentItemListWithCommandExecutor>(list, *executor);
    auto baseImage = make_shared<CImage>("path 1", 1, 2);
    auto item = make_unique<CDocumentItem>(nullopt, move(baseImage));
    listWithCommandExecutor->Add(move(item));
    ASSERT_EQ(listWithCommandExecutor->GetSize(), 1);
    ASSERT_EQ(listWithCommandExecutor->Get(0).GetImage().value()->GetPath(), "path 1");

    auto baseImage2 = make_shared<CImage>("path 2", 1, 2);
    auto item2 = make_unique<CDocumentItem>(nullopt, move(baseImage2));
    listWithCommandExecutor->Add(move(item2));
    ASSERT_EQ(listWithCommandExecutor->GetSize(), 2);
    ASSERT_EQ(listWithCommandExecutor->Get(1).GetImage().value()->GetPath(), "path 2");

    executor->Undo();
    ASSERT_EQ(listWithCommandExecutor->GetSize(), 1);
    executor->Undo();
    ASSERT_EQ(listWithCommandExecutor->GetSize(), 0);
    executor->Redo();
    ASSERT_EQ(listWithCommandExecutor->GetSize(), 1);
    executor->Redo();
    ASSERT_EQ(listWithCommandExecutor->GetSize(), 2);
}

class TestDocument : public ::testing::Test
{
};

TEST_F(TestDocument, shouldBeAbleToModifyTitle)
{
    auto document = make_unique<CDocument>();
    document->SetTitle("some");
    ASSERT_EQ(document->GetTitle(), "some");
    document->SetTitle("some 1");
    ASSERT_EQ(document->GetTitle(), "some 1");
}

TEST_F(TestDocument, shouldInsertContent)
{
    auto document = make_unique<CDocument>();
    document->InsertParagraph("text 1");
    document->InsertParagraph("text 2");
    ASSERT_EQ(document->GetItemsCount(), 2);
    ASSERT_THROW(document->GetItem(3), invalid_argument);
}

TEST_F(TestDocument, shouldInsertContentToDesirtedPosition)
{
    auto document = make_unique<CDocument>();
    document->InsertParagraph("text 1");
    document->InsertParagraph("text 2", 0);
    document->InsertImage("path 3", 100, 100, 1);
    document->InsertParagraph("text 4", 3);
    ASSERT_EQ(document->GetItemsCount(), 4);
    ASSERT_EQ(document->GetItem(0).GetParagraph().value()->GetText(), "text 2");
    ASSERT_EQ(document->GetItem(1).GetImage().value()->GetPath(), "path 3");
    ASSERT_EQ(document->GetItem(2).GetParagraph().value()->GetText(), "text 1");
    ASSERT_EQ(document->GetItem(3).GetParagraph().value()->GetText(), "text 4");
}

TEST_F(TestDocument, shouldBeUndoable)
{
    auto document = make_unique<CDocument>();
    document->InsertImage("path", 2, 2);
    ASSERT_EQ(document->GetItemsCount(), 1);
    document->InsertImage("path 2", 2, 2);
    ASSERT_EQ(document->GetItemsCount(), 2);
    document->Undo();
    ASSERT_EQ(document->GetItemsCount(), 1);
    document->Redo();
    ASSERT_EQ(document->GetItemsCount(), 2);
    document->Undo();
    document->Undo();
    ASSERT_EQ(document->GetItemsCount(), 0);
    document->Redo();
    document->Redo();
    ASSERT_EQ(document->GetItemsCount(), 2);
}

TEST_F(TestDocument, shouldBeUndoableOnlyIfPossibly)
{
    auto document = make_unique<CDocument>();
    document->InsertParagraph("text 0");
    document->InsertImage("path 1", 100, 100);
    ASSERT_EQ(document->CanRedo(), false);
    ASSERT_EQ(document->CanUndo(), true);
    document->Undo();
    document->Undo();
    ASSERT_EQ(document->CanUndo(), false);
    ASSERT_THROW(document->Undo(), invalid_argument);
    ASSERT_EQ(document->CanRedo(), true);
    document->Redo();
    document->Redo();
    ASSERT_EQ(document->CanRedo(), false);
    ASSERT_THROW(document->Redo(), invalid_argument);
    ASSERT_EQ(document->CanUndo(), true);
}

TEST_F(TestDocument, shouldBeAbleToChangeUndoBranches)
{
    auto document = make_unique<CDocument>();
    document->InsertParagraph("text 0");
    document->InsertImage("path 1", 10, 10);
    document->GetItem(1).GetImage().value()->Resize(20, 20);
    document->Undo();
    document->GetItem(1).GetImage().value()->Resize(30, 30);
    document->Undo();
    document->Redo();
    ASSERT_EQ(document->GetItem(1).GetImage().value()->GetWidth(), 30);
    ASSERT_EQ(document->GetItem(1).GetImage().value()->GetHeight(), 30);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
