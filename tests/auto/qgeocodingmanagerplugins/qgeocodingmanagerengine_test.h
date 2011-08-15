/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGEOCODINGMANAGERENGINE_TEST_H
#define QGEOCODINGMANAGERENGINE_TEST_H

#include <qgeoserviceprovider.h>
#include <qgeocodingmanagerengine.h>
#include <QLocale>
#include <qlandmarkmanager.h>
#include <qgeoaddress.h>
#include <qgeolocation.h>
#include <qgeocodereply.h>


QT_USE_NAMESPACE


class GeocodeReplyTest :public QGeocodeReply
{
    Q_OBJECT
public:
    GeocodeReplyTest(QObject *parent=0):QGeocodeReply (parent) {}

    void  callAddLocation ( const QGeoLocation & location ) {addLocation(location);}
    void  callSetError ( Error error, const QString & errorString ) {setError(error, errorString);}
    void  callSetFinished ( bool finished ) {setFinished(finished);}
    void  callSetLimit ( int limit ) {setLimit(limit);}
    void  callSetOffset ( int offset ) {setOffset(offset);}
    void  callSetLocations ( const QList<QGeoLocation> & locations ) {setLocations(locations);}
    void  callSetViewport ( QGeoBoundingArea * viewport ) {setViewport(viewport);}

};

class QGeocodingManagerEngineTest: public QGeocodingManagerEngine

{
Q_OBJECT
public:
    QGeocodingManagerEngineTest(const QMap<QString, QVariant> &parameters,
        QGeoServiceProvider::Error *error, QString *errorString) :
        QGeocodingManagerEngine(parameters)
    {
        Q_UNUSED(error)
        Q_UNUSED(errorString)
        setSupportsGeocoding(true);
        setSupportsReverseGeocoding(true);
        setLocale(QLocale(QLocale::German, QLocale::Germany));
    }

    QGeocodeReply*  geocode ( const QString & searchString, int limit, int offset, QGeoBoundingArea * bounds )
    {
        GeocodeReplyTest *geocodereply = new GeocodeReplyTest();
        geocodereply->callSetLimit(limit);
        geocodereply->callSetOffset(offset);
        geocodereply->callSetViewport(bounds);
        geocodereply->callSetError(QGeocodeReply::NoError,searchString);
        geocodereply->callSetFinished(true);
        emit(this->finished(geocodereply));

        return static_cast<QGeocodeReply*>(geocodereply);
    }

    QGeocodeReply*  geocode ( const QGeoAddress & address, QGeoBoundingArea * bounds )
    {
        GeocodeReplyTest *geocodereply = new GeocodeReplyTest();
        geocodereply->callSetViewport(bounds);
        geocodereply->callSetError(QGeocodeReply::NoError,address.city());
        geocodereply->callSetFinished(true);
        emit(this->finished(geocodereply));

        return static_cast<QGeocodeReply*>(geocodereply);
    }

    QGeocodeReply*  reverseGeocode ( const QGeoCoordinate & coordinate, QGeoBoundingArea * bounds )
    {
        GeocodeReplyTest *geocodereply = new GeocodeReplyTest();
        geocodereply->callSetViewport(bounds);
        geocodereply->callSetError(QGeocodeReply::NoError,coordinate.toString());
        geocodereply->callSetFinished(true);
        emit(this->finished(geocodereply));
        return static_cast<QGeocodeReply*>(geocodereply);
    }
};

#endif
