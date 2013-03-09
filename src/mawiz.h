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

#ifndef MAWIZ_H
#define MAWIZ_H

#include <QMainWindow>
#include <QString>


class MaWizPage;
class MaWiz_P;


class MaWiz : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MaWiz();
    ~MaWiz();

signals:
    void quitRequested();
    void currentPageChanged(int);

public slots:
    void setButtonQuitText(QString text);
    void setButtonHelpText(QString text);
    void setButtonReturnText(QString text);
    void setButtonBackText(QString text);
    void setButtonForwardText(QString text);

    void setButtonQuitVisible(bool visible);
    void setButtonBackVisible(bool visible);
    void setButtonForwardVisible(bool visible);

    void setButtonQuitEnabled(bool enabled);
    void setButtonBackEnabled(bool enabled);
    void setButtonForwardEnabled(bool enabled);

    void setLabelTitleText(QString text);
    void setHelpTitle(QString title);
    void setWindowMovingEnabled(bool enabled);

    void setProgressBarVisible(bool visible);
    void setProgressBarMaximumValue(int value);
    void setProgressBarValue(int value);
    void setProgressBarText(QString text, bool showProgress = true);

    int addPage(MaWizPage* page);
    void setCurrentPage(int index);
    int currentPageIndex();
    bool isFirstPage();
    bool isLastPage();

    void show();

private:
    MaWiz_P *pData;

    void paintEvent(QPaintEvent * event);
};

#endif // MAWIZ_H
