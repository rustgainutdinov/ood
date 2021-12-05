#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/CImage.h>
#include <lw5/editor/documentItem/CDocumentItem.h>
#include "lw5/editor/CDocument.h"
#include "CStreamEditorClient.h"

using namespace std;

int main()
{
    auto streamEditorClient = CStreamEditorClient();
    CStreamEditorClient::MakeDocumentFromStream(cin);
    return 0;
}
