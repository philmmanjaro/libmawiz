/*
 *  MaWiz - Manjaro Wizard Library
 *  Roland Singer <roland@manjaro.org>
 *
 *  Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAWIZ_P_H
#define MAWIZ_P_H

#include <QObject>
#include <QMainWindow>
#include <QString>
#include <QPainter>
#include <QImage>
#include <QStyle>
#include <QDesktopWidget>
#include <QList>
#include <QStackedWidget>
#include "movebar.h"
#include "mawizpage.h"


namespace Ui {
class MaWiz;
}


class MaWiz_P : public QObject
{
    Q_OBJECT

public:
    explicit MaWiz_P(QMainWindow *parent);
    ~MaWiz_P();

    Ui::MaWiz *ui;
    MoveBar moveBar;
    QStackedWidget stackedWidget;
    QString helpTitle;

public slots:
    void setNextPage();
    void setPreviousPage();
    void checkCurrentPage();
    void currentPageChanged();
    void buttonReturn_clicked();
    void buttonHelp_clicked();

private:
    QMainWindow *parent;
    int pageHelpIndex, pageStackedWidgetIndex;

};


#endif // MAWIZ_P_H
