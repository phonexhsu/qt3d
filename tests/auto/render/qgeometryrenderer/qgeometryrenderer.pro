TEMPLATE = app

TARGET = tst_qgeometryrenderer

QT += core-private 3dcore 3dcore-private 3drenderer 3drenderer-private testlib

CONFIG += testcase

SOURCES += tst_qgeometryrenderer.cpp

include(../commons/commons.pri)
