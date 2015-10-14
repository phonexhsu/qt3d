/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "testpostmanarbiter.h"
#include <Qt3DCore/private/qnode_p.h>

QT_BEGIN_NAMESPACE

TestPostman::TestPostman(TestArbiter *arbiter)
    : m_arbiter(arbiter)
{}

void TestPostman::setScene(Qt3DCore::QScene *)
{}

void TestPostman::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &)
{}

void TestPostman::notifyBackend(const Qt3DCore::QSceneChangePtr &e)
{
    m_arbiter->sceneChangeEventWithLock(e);
}

TestArbiter::TestArbiter(Qt3DCore::QNode *node)
    : m_postman(new TestPostman(this))
    , m_node(node)
{
    assignArbiter(m_node);
}

TestArbiter::~TestArbiter()
{
    Qt3DCore::QNodePrivate::get(m_node)->setArbiter(Q_NULLPTR);
}

void TestArbiter::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e)
{
    events.push_back(e);
}

void TestArbiter::sceneChangeEventWithLock(const Qt3DCore::QSceneChangePtr &e)
{
    events.push_back(e);
}

void TestArbiter::sceneChangeEventWithLock(const Qt3DCore::QSceneChangeList &e)
{
    events += QVector<Qt3DCore::QSceneChangePtr>::fromStdVector(e);
}

Qt3DCore::QAbstractPostman *TestArbiter::postman() const
{
    return m_postman;
}

void TestArbiter::assignArbiter(Qt3DCore::QNode *node)
{
    Qt3DCore::QNodePrivate::get(node)->setArbiter(this);
    Q_FOREACH (Qt3DCore::QNode *n, node->childrenNodes())
        assignArbiter(n);
}

QT_END_NAMESPACE
