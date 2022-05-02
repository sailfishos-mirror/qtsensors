/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include <QtSensors/QSensor>

#include "qturnoversensorgesturerecognizer.h"
#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

// turnover and put down i.e. facedown

QTurnoverSensorGestureRecognizer::QTurnoverSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
    isClose(0)
  , isFaceDown(0), active(0)
{
}

QTurnoverSensorGestureRecognizer::~QTurnoverSensorGestureRecognizer()
{
}

void QTurnoverSensorGestureRecognizer::create()
{
}

bool QTurnoverSensorGestureRecognizer::start()
{
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Proximity)) {
        if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Orientation)) {
            active = true;
            connect(QtSensorGestureSensorHandler::instance(),SIGNAL(proximityReadingChanged(QProximityReading*)),
                    this,SLOT(proximityChanged(QProximityReading*)));

            connect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading*)),
                    this,SLOT(orientationReadingChanged(QOrientationReading*)));
        } else {
            QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Proximity);
            active = false;
        }
    } else {
        active = false;
    }
    return active;
}

bool QTurnoverSensorGestureRecognizer::stop()
{
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Proximity);
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Orientation);

    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(proximityReadingChanged(QProximityReading*)),
            this,SLOT(proximityChanged(QProximityReading*)));
    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading*)),
            this,SLOT(orientationReadingChanged(QOrientationReading*)));

    active = false;

    return active;
}

bool QTurnoverSensorGestureRecognizer::isActive()
{
    return active;
}

QString QTurnoverSensorGestureRecognizer::id() const
{
    return QString("QtSensors.turnover");
}

void QTurnoverSensorGestureRecognizer::proximityChanged(QProximityReading *reading)
{
    isClose = reading->close();
    if (isClose)
        isRecognized();
}

void QTurnoverSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    switch (reading->orientation()) {
       case  QOrientationReading::FaceDown:
    {
        isFaceDown = true;
        isRecognized();
    }
        break;
    default:
        isFaceDown = false;
        break;
    };
}

void QTurnoverSensorGestureRecognizer::isRecognized()
{
    if (isClose && isFaceDown) {
        Q_EMIT turnover();
        Q_EMIT detected("turnover");
    }
}
QT_END_NAMESPACE

