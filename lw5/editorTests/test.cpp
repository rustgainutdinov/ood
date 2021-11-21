#include <gtest/gtest.h>
#include <lw5/editor/CDocument.h>
#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/CImage.h>
#include "memory"

using namespace std;

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
    document->DeleteItem(2);
    ASSERT_THROW(document->GetItem(2), invalid_argument);
    ASSERT_EQ(document->GetItemsCount(), 2);
    ASSERT_EQ(document->GetItem(0).GetParagraph()->GetText(), "text 1");
    ASSERT_EQ(document->GetItem(1).GetParagraph()->GetText(), "text 3");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
