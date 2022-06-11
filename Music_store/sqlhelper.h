#pragma once

#include <QString>
#include <QVariant>
#include <QVariantHash>
#include <QSqlQuery>
#include <QSqlError>
#include <QCompleter>
#include <QTableWidget>

enum { UserIdRole = Qt::UserRole+1 };

namespace SQLHELPER
{
    const QString errMessage = "Query:\n %1 \ncan't be executed.\nProblem: %2";

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

    // Треки - принадлежность матрице (am_id)
    const QString sqlSinglesByMatrixId = " SELECT name, am_id, s_id FROM vi_singles_albums WHERE am_id=%1";

}

QVariant selectValue(const QString &sql, QString &errText)
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


void fillComboBox(QComboBox *cbox_, const QString &sql_, bool addCompleter = true)
{
    if( !cbox_ || sql_.simplified().isEmpty()) return;

    cbox_->clear();
    QStringList complLst;
    QSqlQuery qu(sql_,QSqlDatabase::database());

    if( qu.exec() )
    {
        while (qu.next())
        {
            int idTable  = qu.value(SQLHELPER::IDTAG).toInt();
            QString name = qu.value(SQLHELPER::DISPLAYTAG).toString();
            QString info = qu.value(SQLHELPER::INFOTAG).toString();
//            CDEBUG << idTable << name << info;
            cbox_->addItem(name,info);
            cbox_->setItemData(cbox_->count()-1, idTable, UserIdRole );
            complLst << name;
        }
    }
    else
    {
        throw SQLHELPER::errMessage.arg(sql_).arg( qu.lastError().text() );
    }

    if( !addCompleter ) return;

    QCompleter* cmpl = new QCompleter(complLst,cbox_);
    cmpl->setCaseSensitivity(Qt::CaseInsensitive);
    cmpl->setCompletionMode(QCompleter::PopupCompletion);
    //cmpl->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    cbox_->setCompleter(cmpl);
}

void fillTableWidgetFromDB(QTableWidget &tw, const QString &sql_)
{
    tw.clear();
    tw.setRowCount(0);
    QSqlQuery qu(sql_, QSqlDatabase::database());

    if(qu.exec())
    {
        tw.setColumnCount(qu.record().count());
        QStringList header;

        for(int col=0; col<qu.record().count(); ++col)
            header << qu.record().fieldName(col);

        tw.setHorizontalHeaderLabels(header);

        while(qu.next())
        {
            const int row = tw.rowCount();
            tw.insertRow(row);

            for(int col=0; col<qu.record().count(); ++col)
                tw.setItem(row, col, new QTableWidgetItem(qu.value(col).toString()) );
        }
    }
    else
    {
        throw SQLHELPER::errMessage.arg(sql_).arg( qu.lastError().text() );
    }
}


