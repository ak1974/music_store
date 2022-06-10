#pragma once

#include <QString>
#include <QVariant>
#include <QVariantHash>
#include <QSqlQuery>
#include <QSqlError>

static QVariant selectValue(const QString &sql, QString &errText)
{
    QSqlQuery qu(sql);
    if(qu.exec())
    {
        qu.next();
        return qu.value(0);
    }
    else
    {
        errText = qu.lastError().text();
    }
    return QVariant();
}

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
    const QString sqlAllBandNameAndId = " SELECT b_id AS id, band_name AS name, bt.type_name AS info "
                                        " FROM band b, band_type bt WHERE b.bt_id = bt.bt_id ";
    // Все компании и id (company.status=0/1 т.е. продавец/производитель  )
    const QString sqlAllCompanyNameAndId = " SELECT c_id AS id, name AS name, (c.address || '\nphone:' || c.phone) AS info "
                                           " FROM company c WHERE c.status=1 "; // 1-производители
    // Альбомы по компании (c_id)
    const QString sqlAllAlbumNameForCompany = " SELECT am.am_id AS id, am.album_name AS name, c.name AS info, c.status, c.c_id "
           " FROM company c, album_matrix am WHERE c.c_id = am.cmp_id AND c_id = %1 ";

    // Продавец по матрице (am_id)
    const QString sqlSellerByMatrixId = " SELECT c.name AS name FROM album_matrix am, album_release ar, company c "
            " WHERE am.am_id = ar.am_id AND ar.cmp_id = c.c_id AND am.am_id = %1 LIMIT 1 ";

    // Релизы альбома по матрице (am_id)
    const QString sqlReleaseDateByMatrixId = " SELECT date /*,am_id*/ FROM album_release WHERE am_id=%1 ";

    const QString IDTAG = "id";
    const QString DISPLAYTAG = "name";
    const QString INFOTAG = "info";

    // Музыкант - роль в группе
    const QString sqlArtistRoleView = "vi_artist_role";

    // Треки - принадлежность дискам (могут быть без дисков)
    const QString sqlSinglesAlbumView = "vi_singles_albums";
}



