#pragma once

#include <QString>
#include <QVariant>
#include <QVariantHash>

namespace SQLHELPER {

    static QVariantHash sqlResultToAttrValueHash(const QVariantList &sqlResultList, const QString &ColumnForKey, const QString &ColumnForValue)
    {
        QVariantHash res;
        foreach (auto v, sqlResultList) {
            QString tag = v.toHash().value(ColumnForKey).toString();
            res[tag] = v.toHash().value(ColumnForValue);
        }
        return res;
    }

    // Все имена групп и id
    const QString sqlAllBandNameAndId = "SELECT b_id AS id, band_name AS name FROM band";
}



