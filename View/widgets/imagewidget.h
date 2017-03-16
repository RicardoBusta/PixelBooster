/***************************************************************************\
*  Pixel::Booster, a simple pixel art image editor.                         *
*  Copyright (C) 2017  Ricardo Bustamante de Queiroz (ricardo@busta.com.br) *
*  Visit the Official Homepage: pixel.busta.com.br                          *
*                                                                           *
*  This program is free software: you can redistribute it and/or modify     *
*  it under the terms of the GNU General Public License as published by     *
*  the Free Software Foundation, either version 3 of the License, or        *
*  (at your option) any later version.                                      *
*                                                                           *
*  This program is distributed in the hope that it will be useful,          *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
*  GNU General Public License for more details.                             *
*                                                                           *
*  You should have received a copy of the GNU General Public License        *
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
\***************************************************************************/

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

#include "logic/imageproject.h"

class ImageWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ImageWidget(QWidget *parent = 0);

  ImageProject project;
private:
  void paintEvent(QPaintEvent *event);

  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);

  QRect selection_;
  bool mouseDown_;
  QPoint anchor_;
  QPoint currentCursorPos_;
  QRect outerSelection_[4];
signals:

public slots:
};

#endif // IMAGEWIDGET_H