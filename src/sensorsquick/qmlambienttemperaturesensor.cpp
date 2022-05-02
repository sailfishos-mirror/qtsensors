/****************************************************************************
**
** Copyright (C) 2016 Research In Motion
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
#include "qmlambienttemperaturesensor_p.h"
#include <QtSensors/QAmbientTemperatureSensor>

/*!
    \qmltype AmbientTemperatureSensor
    \instantiates QmlAmbientTemperatureSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.1
    \inherits Sensor
    \brief The AmbientTemperatureSensor element reports on the ambient temperature.

    The AmbientTemperatureSensor element reports on the ambient temperature.

    This element wraps the QAmbientTemperatureSensor class. Please see the documentation for
    QAmbientTemperatureSensor for details.

    \sa AmbientTemperatureReading
*/

QmlAmbientTemperatureSensor::QmlAmbientTemperatureSensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QAmbientTemperatureSensor(this))
{
}

QmlAmbientTemperatureSensor::~QmlAmbientTemperatureSensor()
{
}

QmlSensorReading *QmlAmbientTemperatureSensor::createReading() const
{
    return new QmlAmbientTemperatureReading(m_sensor);
}

QSensor *QmlAmbientTemperatureSensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype AmbientTemperatureReading
    \instantiates QmlAmbientTemperatureReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.1
    \inherits SensorReading
    \brief The AmbientTemperatureReading element holds the most recent temperature reading.

    The AmbientTemperatureReading element holds the most recent temperature reading.

    This element wraps the QAmbientTemperatureReading class. Please see the documentation for
    QAmbientTemperatureReading for details.

    This element cannot be directly created.
*/

QmlAmbientTemperatureReading::QmlAmbientTemperatureReading(QAmbientTemperatureSensor *sensor)
    : m_sensor(sensor)
    , m_temperature(0)
{
}

QmlAmbientTemperatureReading::~QmlAmbientTemperatureReading()
{
}

/*!
    \qmlproperty qreal AmbientTemperatureReading::temperature
    This property holds the ambient temperature in degree Celsius.

    Please see QAmbientTemperatureReading::temperature for information about this property.
*/

qreal QmlAmbientTemperatureReading::temperature() const
{
    return m_temperature;
}

QBindable<qreal> QmlAmbientTemperatureReading::bindableTemperature() const
{
    return &m_temperature;
}

QSensorReading *QmlAmbientTemperatureReading::reading() const
{
    return m_sensor->reading();
}

void QmlAmbientTemperatureReading::readingUpdate()
{
    m_temperature = m_sensor->reading()->temperature();
}
