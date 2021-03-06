/***************************************************************************\
*  Pixel::Booster, a simple pixel art image editor.                         *
*  Copyright (C) 2015  Ricardo Bustamante de Queiroz (ricardo@busta.com.br) *
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

#ifndef GLOBAL_OPTIONS_H
#define GLOBAL_OPTIONS_H

#include <QColor>
#include <QRect>
#include <QSize>

class QSettings;

enum TOOL_ENUM : int {
  TOOL_PENCIL = 1,
  TOOL_FLOOD_FILL = 2,
  TOOL_LINE = 3,
  TOOL_RECTANGLE = 4,
  TOOL_ELLIPSE = 5,
  TOOL_SELECTION = 6,
  TOOL_ZOOM = 7
};

/*!
 * \brief The GlobalOptions class
 */
class GlobalOptions {
public:
  GlobalOptions();

  QSize cursor_size() const;
  void set_cursor_size(const QSize &size);

  QSize grid_size() const;
  void set_grid_size(const QSize &size);

  QRect tile_selection() const;
  void set_tile_selection(const QRect &tile_selection);
  void UpdateCursorShift();
  void CleanCursorShift();
  void MoveSelection(const QPoint &top_left);

  QSize new_image_size() const;
  void set_new_image_size(const QSize &size);

  bool transparency_enabled() const;
  void set_transparency_enabled(bool transparency);

  int zoom() const;
  void set_zoom(int zoom);

  QColor main_color() const;
  void set_main_color(const QColor &color);

  QColor alt_color() const;
  void set_alt_color(const QColor &color);

  void set_new_image_color(const QColor &color);
  QColor new_image_color() const;

  void set_tool(const TOOL_ENUM tool);
  TOOL_ENUM tool() const;

  void set_language(const QString &language);
  QString language() const;

  bool show_grid() const;
  void set_show_grid(bool show);

  bool show_pixel_grid() const;
  void set_show_pixel_grid(bool show);

  QRect PosToGrid(const QPoint &pos) const;

  void SaveState(QSettings *settings) const;
  void LoadState(QSettings *settings);

private:
  QSize cursor_size_;
  QSize grid_size_;
  QRect tile_selection_;
  bool horizontal_shift_;
  bool vertical_shift_;
  QSize new_image_size_;
  bool transparency_enabled_;
  int zoom_;
  QColor main_color_;
  QColor alt_color_;
  TOOL_ENUM tool_;
  QString language_;
  QColor new_image_color_;
  bool show_pixel_grid_;
  bool show_grid_;
};

#endif // GLOBAL_OPTIONS_H
