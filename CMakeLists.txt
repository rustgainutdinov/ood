cmake_minimum_required(VERSION 3.17)
project(ood)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(lw1)
include_directories(lw4)

# lw1
add_executable(SimUDuck lw1/SimUDuck/SimUDuck.cpp)
add_executable(SimUDuckFunc lw1/SimUDuckFunc/SimUDuckFunc.cpp)

# lw2
add_executable(WeatherStation lw2/WeatherStation/main.cpp)
add_executable(SetErase examples/set_erase.cpp)
add_executable(WeatherStationTests lw2/WeatherStation/test.cpp)
target_link_libraries(WeatherStationTests gtest_main)
add_test(NAME WeatherStationTests COMMAND WeatherStationTests)

# lw3
include_directories("${PROJECT_SOURCE_DIR}/lw3/")
add_executable(Coffee lw3/coffee/main.cpp lw5/editor/content/IImage.h lw5/editor/content/IParagraph.h)
add_executable(Streams lw3/streams/main.cpp)
add_executable(StreamsTests lw3/streams/test.cpp)
target_link_libraries(StreamsTests gtest_main)
add_test(NAME StreamsTests COMMAND StreamsTests)


include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project'm_executor compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#OPENCV
FetchContent_Declare(
        opencv
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        GIT_TAG 4.4.0
)
FetchContent_GetProperties(opencv)
if (NOT opencv_POPULATED)
    FetchContent_Populate(opencv)
endif ()
FetchContent_MakeAvailable(opencv)

# Find on pc
set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(OpenCV REQUIRED)

#add_executable(Painting lw4/painting/main.cpp lw4/painting/Designer.cpp lw4/painting/shape/Shape.cpp lw4/painting/ShapeFactory.cpp lw4/painting/shape/Rectangle.cpp lw4/painting/shape/Ellipse.cpp lw4/painting/Painter.cpp lw4/painting/PictureDraft.cpp lw4/painting/Client.cpp lw4/painting/ImageCanvas.cpp lw4/painting/ImageCanvas.h)
#target_link_libraries(Painting ${OpenCV_LIBS})
#add_executable(PaintingTests lw4/painting/test.cpp lw4/painting/Designer.cpp lw4/painting/shape/Shape.cpp lw4/painting/ShapeFactory.cpp lw4/painting/shape/Rectangle.cpp lw4/painting/shape/Ellipse.cpp lw4/painting/Painter.cpp lw4/painting/PictureDraft.cpp lw4/painting/Client.cpp lw4/painting/ImageCanvas.cpp lw4/painting/ImageCanvas.h)
#target_link_libraries(PaintingTests gtest_main)
#target_link_libraries(PaintingTests ${OpenCV_LIBS})
#add_test(NAME PaintingTests COMMAND PaintingTests)

add_executable(Editor lw5/editor/main.cpp lw5/editor/IDocument.h lw5/editor/CDocument.h lw5/editor/CDocument.cpp lw5/editor/content/IImage.h lw5/editor/content/IParagraph.h lw5/editor/content/CParagraph.cpp lw5/editor/content/CParagraph.h lw5/editor/content/CImage.cpp lw5/editor/content/CImage.h lw5/editor/documentItem/CDocumentItem.cpp lw5/editor/documentItem/CDocumentItem.h lw5/editor/command/ICommand.h lw5/editor/command/IUndoableCommandExecutor.h lw5/editor/command/CUndoableCommandExecutor.cpp lw5/editor/command/CUndoableCommandExecutor.h lw5/editor/content/IImageResource.h lw5/editor/command/content/CImageWithCommandExecutor.cpp lw5/editor/command/content/CImageWithCommandExecutor.h lw5/editor/command/ICommandExecutor.h lw5/editor/command/commands/CResizeImageCommand.cpp lw5/editor/command/commands/CResizeImageCommand.h lw5/editor/command/commands/CAddDocumentItemToListCommand.cpp lw5/editor/command/commands/CAddDocumentItemToListCommand.h lw5/editor/documentItem/IDocumentItemList.h lw5/editor/documentItem/CDocumentItemList.cpp lw5/editor/documentItem/CDocumentItemList.h lw5/editor/command/commands/CDeleteDocumentItemFromListCommand.cpp lw5/editor/command/commands/CDeleteDocumentItemFromListCommand.h lw5/editor/content/IResource.h lw5/editor/documentItem/IDocumentItem.h lw5/editor/command/documentItem/CDocumentItemListWithCommandExecutor.cpp lw5/editor/command/documentItem/CDocumentItemListWithCommandExecutor.h lw5/editor/CStreamEditorClient.cpp lw5/editor/CStreamEditorClient.h lw5/editor/command/commands/CReplaceTextCommad.cpp lw5/editor/command/commands/CReplaceTextCommad.h lw5/editor/command/content/CParagraphWithCommandExecutor.cpp lw5/editor/command/content/CParagraphWithCommandExecutor.h)
add_executable(EditorTests lw5/editor/IDocument.h lw5/editor/CDocument.h lw5/editor/CDocument.cpp lw5/editorTests/test.cpp lw5/editor/content/IImage.h lw5/editor/content/IParagraph.h lw5/editor/content/CParagraph.cpp lw5/editor/content/CParagraph.h lw5/editor/content/CImage.cpp lw5/editor/content/CImage.h lw5/editor/documentItem/CDocumentItem.cpp lw5/editor/documentItem/CDocumentItem.h lw5/editor/command/ICommand.h lw5/editor/command/IUndoableCommandExecutor.h lw5/editor/command/CUndoableCommandExecutor.cpp lw5/editor/command/CUndoableCommandExecutor.h lw5/editor/content/IImageResource.h lw5/editor/command/content/CImageWithCommandExecutor.cpp lw5/editor/command/content/CImageWithCommandExecutor.h lw5/editor/command/ICommandExecutor.h lw5/editor/command/commands/CResizeImageCommand.cpp lw5/editor/command/commands/CResizeImageCommand.h lw5/editor/command/commands/CAddDocumentItemToListCommand.cpp lw5/editor/command/commands/CAddDocumentItemToListCommand.h lw5/editor/documentItem/IDocumentItemList.h lw5/editor/documentItem/CDocumentItemList.cpp lw5/editor/documentItem/CDocumentItemList.h lw5/editor/command/commands/CDeleteDocumentItemFromListCommand.cpp lw5/editor/command/commands/CDeleteDocumentItemFromListCommand.h lw5/editor/content/IResource.h lw5/editor/documentItem/IDocumentItem.h lw5/editor/command/documentItem/CDocumentItemListWithCommandExecutor.cpp lw5/editor/command/documentItem/CDocumentItemListWithCommandExecutor.h lw5/editor/command/commands/CReplaceTextCommad.cpp lw5/editor/command/commands/CReplaceTextCommad.h lw5/editor/command/content/CParagraphWithCommandExecutor.cpp lw5/editor/command/content/CParagraphWithCommandExecutor.h)
target_link_libraries(EditorTests gtest_main)
add_test(NAME EditorTests COMMAND EditorTests)

add_executable(ObjectAdapter lw6/objectAdapter/main.cpp)
add_executable(ObjectAdapterTests lw6/objectAdapter/main.cpp lw6/objectAdapter/test.cpp)
target_link_libraries(ObjectAdapterTests gtest_main)
add_test(NAME ObjectAdapterTests COMMAND ObjectAdapterTests)

add_executable(Slides lw7/slides/main.cpp lw7/slides/IShape.h lw7/slides/RectFrame.h lw7/slides/Style.h lw7/slides/ICanvas.h lw7/slides/CShape.cpp lw7/slides/CShape.h lw7/slides/IGroup.h lw7/slides/CRectangle.cpp lw7/slides/CRectangle.h lw7/slides/ImageCanvas.cpp lw7/slides/ImageCanvas.h lw7/slides/Point.h lw7/slides/CGroup.cpp lw7/slides/CGroup.h lw7/slides/CSlide.cpp lw7/slides/CSlide.h lw7/slides/CTriangle.cpp lw7/slides/CTriangle.h)
target_link_libraries(Slides ${OpenCV_LIBS})