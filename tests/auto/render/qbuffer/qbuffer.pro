TEMPLATE = app

TARGET = tst_qbuffer

QT += core-private 3dcore 3dcore-private 3drenderer 3drenderer-private testlib

CONFIG += testcase

SOURCES += tst_qbuffer.cpp

include(../commons/commons.pri)
