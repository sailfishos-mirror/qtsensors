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

#ifndef QGYROSCOPE_H
#define QGYROSCOPE_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QGyroscopeReadingPrivate;

class Q_SENSORS_EXPORT QGyroscopeReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x)
    Q_PROPERTY(qreal y READ y)
    Q_PROPERTY(qreal z READ z)
    DECLARE_READING(QGyroscopeReading)
public:
    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal z() const;
    void setZ(qreal z);
};

class Q_SENSORS_EXPORT QGyroscopeFilter : public QSensorFilter
{
public:
    virtual bool filter(QGyroscopeReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QGyroscope : public QSensor
{
    Q_OBJECT
public:
    explicit QGyroscope(QObject *parent = nullptr);
    virtual ~QGyroscope();
    QGyroscopeReading *reading() const;
    static char const * const sensorType;

private:
    Q_DISABLE_COPY(QGyroscope)
};

QT_END_NAMESPACE

#endif

