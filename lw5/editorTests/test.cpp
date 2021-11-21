#include <gtest/gtest.h>
#include <lw5/editor/CDocument.h>
#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/CImage.h>
#include <lw5/editor/command/CUndoableCommandExecutor.h>
#include <lw5/editor/command/ICommand.h>
#include <lw5/editor/command/CCommandFactory.h>

#include <utility>
#include "memory"

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
    ASSERT_EQ(document->GetItem(0).GetParagraph()->GetText(), "text 2");
    ASSERT_EQ(document->GetItem(1).GetImage()->GetPath(), "path 3");
    ASSERT_EQ(document->GetItem(2).GetParagraph()->GetText(), "text 1");
    ASSERT_EQ(document->GetItem(3).GetParagraph()->GetText(), "text 4");
}

TEST_F(TestDocument, shouldDeleteDocumentItem)
{
    auto document = make_unique<CDocument>();
    document->InsertParagraph("text 1");
    document->InsertImage("path 2", 100, 100);
    document->InsertParagraph("text 3");
    document->InsertParagraph("text 4");
    ASSERT_EQ(document->GetItemsCount(), 4);
    document->DeleteItem(1);
    document->DeleteItem();
    ASSERT_THROW(document->GetItem(2), invalid_argument);
    ASSERT_EQ(document->GetItemsCount(), 2);
    ASSERT_EQ(document->GetItem(0).GetParagraph()->GetText(), "text 1");
    ASSERT_EQ(document->GetItem(1).GetParagraph()->GetText(), "text 3");
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
    auto command1 = make_shared<MockCommand>("command1", mutableStr);
    auto command2 = make_shared<MockCommand>("command2", mutableStr);
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
    auto command1 = make_shared<MockCommand>("command1", mutableStr);
    auto command2 = make_shared<MockCommand>("command2", mutableStr);
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
    auto command1 = make_shared<MockCommand>("command1", mutableStr);
    auto command2 = make_shared<MockCommand>("command2", mutableStr);
    auto command3 = make_shared<MockCommand>("command3", mutableStr);
    executor->Add(move(command1));
    executor->Add(move(command2));
    executor->Undo();
    executor->Add(command3);
    executor->Undo();
    ASSERT_EQ(mutableStr, "command3unexecuted");
    executor->Undo();
    ASSERT_EQ(mutableStr, "command1unexecuted");
}

class TestCommandFactory : public ::testing::Test
{
};

TEST_F(TestCommandFactory, shouldCreateInsertParagraphCommand)
{
    auto document = make_shared<CDocument>();
    auto commandFactory = make_unique<CCommandFactory>(document);
    auto executor = make_unique<CUndoableCommandExecutor>();
    auto command = commandFactory->CreateCommand("InsertParagraph end some1");
    executor->Add(move(command));
    ASSERT_EQ(document->GetItemsCount(), 1);
    ASSERT_EQ(document->GetItem(0).GetParagraph()->GetText(), "some1");
    command = commandFactory->CreateCommand("InsertParagraph 0 some2");
    executor->Add(move(command));
    ASSERT_EQ(document->GetItemsCount(), 2);
    ASSERT_EQ(document->GetItem(0).GetParagraph()->GetText(), "some2");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
