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

#include "mawizpage.h"

MaWizPage::MaWizPage(QString title, QString helpURL, bool enableGoBack, QWidget *parent) :
    QWidget(parent),
    title(title),
    helpURL(helpURL.trimmed()),
    enableGoBack(enableGoBack)
{
}



bool MaWizPage::ready() {
    return true;
}



void MaWizPage::activated() {
}



void MaWizPage::setEnableGoBack(bool enableGoBack) {
    this->enableGoBack = enableGoBack;
}



bool MaWizPage::getGoBack() {
    return enableGoBack;
}



void MaWizPage::setTitle(QString title) {
    this->title = title;
}



QString MaWizPage::getTitle() {
    return title;
}



void MaWizPage::setHelpURL(QString helpURL) {
    this->helpURL = helpURL.trimmed();
}



QString MaWizPage::getHelpURL() {
    return helpURL;
}
