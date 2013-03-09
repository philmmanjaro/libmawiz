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

#ifndef MAWIZPAGE_H
#define MAWIZPAGE_H

#include <QWidget>

class MaWizPage : public QWidget
{
    Q_OBJECT
public:
    explicit MaWizPage(QString title = "", QString helpURL = "", bool enableGoBack = true, QWidget *parent = 0);
    virtual ~MaWizPage() {}
    
    virtual bool ready();
    virtual void activated();

    void setEnableGoBack(bool enableGoBack);
    bool getGoBack();

    void setTitle(QString title);
    QString getTitle();

    void setHelpURL(QString helpURL);
    QString getHelpURL();
    
signals:
    void checkReady();

private:
    QString title, helpURL;
    bool enableGoBack;

};

#endif // MAWIZPAGE_H
