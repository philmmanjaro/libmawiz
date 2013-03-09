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

#include "movebar.h"

MoveBar::MoveBar(QMainWindow *parent) :
    QWidget(parent)
{
    this->parent = parent;
    moving = false;
    enabled = true;
    setMouseTracking(false);
}



void MoveBar::setMovingEnabled(bool enabled) {
    this->enabled = enabled;
}



void MoveBar::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    if((event->button() == Qt::LeftButton)) {
        moving = true;
        offset = event->pos();
    }
}



void MoveBar::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    if(moving && enabled)
        parent->move(event->globalPos() - offset);
}



void MoveBar::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
        moving = false;
}

