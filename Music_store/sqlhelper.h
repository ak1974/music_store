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
    const QString sqlAllBandNameAndId = " SELECT b_id AS id, band_name AS name, bt.type_name AS info "
                                        " FROM band b, band_type bt WHERE b.bt_id = bt.bt_id ";
    // Все компании и id
    const QString sqlAllCompanyNameAndId = " SELECT c_id AS id, name AS name, (c.address || '\nphone:' || c.phone) AS info "
                                           " FROM company c WHERE c.status = 1 ";
    const QString IDTAG = "id";
    const QString DISPLAYTAG = "name";
    const QString INFOTAG = "info";

    // Музыкант - роль в группе
    const QString sqlArtistRoleView = "vi_artist_role";

    // Треки - принадлежность дискам (могут быть без дисков)
    const QString sqlSinglesAlbumView = "vi_singles_albums";
}



