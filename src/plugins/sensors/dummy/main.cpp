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

#include "dummyaccelerometer.h"
#include "dummylightsensor.h"
#include <qsensorplugin.h>
#include <qsensorbackend.h>
#include <qsensormanager.h>
#include <QFile>
#include <QDebug>

class dummySensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)
public:
    void registerSensors() override
    {
        QSensorManager::registerBackend(QAccelerometer::sensorType, dummyaccelerometer::id, this);
        QSensorManager::registerBackend(QAmbientLightSensor::sensorType, dummylightsensor::id, this);
    }

    QSensorBackend *createBackend(QSensor *sensor) override
    {
        if (sensor->identifier() == dummyaccelerometer::id) {
            return new dummyaccelerometer(sensor);
        }

        if (sensor->identifier() == dummylightsensor::id) {
            return new dummylightsensor(sensor);
        }

        return 0;
    }
};

#include "main.moc"

