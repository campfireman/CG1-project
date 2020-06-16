QT       += core gui opengl widgets

TEMPLATE = app

TARGET = CgViewer

QMAKE_CXXFLAGS += -std=c++17

CONFIG += c++17

SOURCES += main.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgSceneControl.cpp \
    CgEvents/CgKeyEvent.cpp \
    CgSceneGraph/CgExampleTriangle.cpp \
    CgSceneGraph/CgCube.cpp \
    CgSceneGraph/CgPolyline.cpp \
    CgSceneGraph/CgSolidOfRevolution.cpp \
    CgSceneGraph/CgLoadedObj.cpp \
    CgSceneGraph/CgScenegraph.cpp \
    CgSceneGraph/CgScenegraphNode.cpp \
    CgSceneGraph/CgAppearance.cpp \
    CgSceneGraph/CgNodeCursor.cpp \
    CgQtViewer/CgQtGlBufferObject.cpp \
    CgQtViewer/CgTrackball.cpp \
    CgEvents/CgWindowResizeEvent.cpp \
    CgEvents/CgLoadObjFileEvent.cpp \
    CgEvents/CgColorChangeEvent.cpp \
    CgEvents/CgCheckboxChangedEvent.cpp \
    CgEvents/CgSelectionChangedEvent.cpp \
    CgEvents/CgButtonPressedEvent.cpp \
    CgEvents/CgSORChangedEvent.cpp \
    CgUtils/ObjLoader.cpp \
    CgUtils/Utils.cpp \
    CgEvents/CgTrackballEvent.cpp

HEADERS += \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgSceneControl.h \
    CgEvents/CgKeyEvent.h \
    CgBase/CgBaseRenderer.h \
    CgBase/CgBaseRenderableObject.h \
    CgSceneGraph/CgExampleTriangle.h \
    CgSceneGraph/CgCube.h \
    CgSceneGraph/CgPolyline.h \
    CgSceneGraph/CgSolidOfRevolution.h \
    CgSceneGraph/CgLoadedObj.h \
    CgSceneGraph/CgScenegraph.h \
    CgSceneGraph/CgScenegraphNode.h \
    CgSceneGraph/CgNodeCursor.h \
    CgSceneGraph/CgAppearance.h \
    CgBase/CgBasePointCloud.h \
    CgBase/CgBaseTriangleMesh.h \
    CgBase/CgBasePolygonMesh.h \
    CgBase/CgBasePolyline.h \
    CgBase/CgBaseSceneControl.h \
    CgQtViewer/CgQtGlBufferObject.h \
    CgQtViewer/CgTrackball.h \
    CgEvents/CgWindowResizeEvent.h \
    CgEvents/CgLoadObjFileEvent.h \
    CgEvents/CgColorChangeEvent.h \
    CgEvents/CgButtonPressedEvent.h \
    CgEvents/CgCheckboxChangedEvent.h \
    CgEvents/CgSelectionChangedEvent.h \
    CgEvents/CgSORChangedEvent.h \
    CgUtils/ObjLoader.h \
    CgUtils/Utils.h \
    CgBase/CgBaseImage.h \
    CgEvents/CgTrackballEvent.h

