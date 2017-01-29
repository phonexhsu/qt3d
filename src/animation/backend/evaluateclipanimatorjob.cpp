/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
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

#include "evaluateclipanimatorjob_p.h"
#include <Qt3DAnimation/private/handler_p.h>
#include <Qt3DAnimation/private/managers_p.h>
#include <Qt3DAnimation/private/animationlogging_p.h>
#include <Qt3DAnimation/private/animationutils_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DAnimation {
namespace Animation {

EvaluateClipAnimatorJob::EvaluateClipAnimatorJob()
    : Qt3DCore::QAspectJob()
{
}

void EvaluateClipAnimatorJob::run()
{
    Q_ASSERT(m_handler);

    const qint64 globalTime = m_handler->simulationTime();
    //qDebug() << Q_FUNC_INFO << "t_global =" << globalTime;

    ClipAnimator *clipAnimator = m_handler->clipAnimatorManager()->data(m_clipAnimatorHandle);
    Q_ASSERT(clipAnimator);

    // Evaluate the fcurves
    AnimationClip *clip = m_handler->animationClipManager()->lookupResource(clipAnimator->clipId());
    Q_ASSERT(clip);
    bool finalFrame = false;
    int currentLoop = 0;
    const QVector<float> channelResults = AnimationUtils::evaluateAtGlobalTime(clip,
                                                                               globalTime,
                                                                               clipAnimator->startTime(),
                                                                               clipAnimator->loops(),
                                                                               currentLoop,
                                                                               finalFrame);

    if (finalFrame)
        clipAnimator->setRunning(false);

    clipAnimator->setCurrentLoop(currentLoop);

    // Prepare property changes (if finalFrame it also prepares the change for the running property for the frontend)
    const QVector<Qt3DCore::QSceneChangePtr> changes = AnimationUtils::preparePropertyChanges(clipAnimator->peerId(),
                                                                                              clipAnimator->mappingData(),
                                                                                              channelResults,
                                                                                              finalFrame);

    // Send the property changes
    clipAnimator->sendPropertyChanges(changes);

}

} // namespace Animation
} // namespace Qt3DAnimation

QT_END_NAMESPACE
