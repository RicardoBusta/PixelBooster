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

#include "global_options.h"

#include <QSettings>

#include "utils/debug.h"
#include "pb_math.h"

const QString kStateCursorSize = "CursorSize";
const QSize kStateCursorSizeDefault = QSize(32, 32);
const QString kStateGridSize = "GridSize";
const QSize kStateGridSizeDefault = QSize(32, 32);
const QString kStateNewImageSize = "NewImageSize";
const QSize kStateNewImageSizeDefault = QSize(256, 256);
const QString kStateTransparency = "TransparencyEnabled";
const bool kStateTransparencyDefault = false;
const QString kStateZoomLevel = "ZoomLevel";
const int kStateZoomLevelDefault = 1;
const QString kStateTool = "Tool";
const int kStateToolDefault = TOOL_PENCIL;
const QString kStateColorMain = "MainColor";
const QColor kStateColorMainDefault = QColor(Qt::white).name();
const QString kStateColorAlt = "AltColor";
const QColor kStateColorAltDefault = QColor(Qt::black).name();
const QString kStateLanguage = "Language";
const QString kStateLanguageDefault = "en_us";
const QString kStateNewImageColor = "NewImageColor";
const QColor kStateNewImageColorDefault = QColor(Qt::white).name();
const QString kStateShowGrid = "ShowGrid";
const bool kStateShowGridDefault = false;
const QString kStateShowPixelGrid = "ShowPixelGrid";
const bool kStateShowPixelGridDefault = false;

GlobalOptions::GlobalOptions() : horizontal_shift_(false),
                                 vertical_shift_(false),
                                 zoom_(1) {
}

QSize GlobalOptions::cursor_size() const {
  return cursor_size_;
}

void GlobalOptions::set_cursor_size(const QSize &size) {
  cursor_size_ = size;
}

QSize GlobalOptions::grid_size() const {
  return grid_size_;
}

void GlobalOptions::set_grid_size(const QSize &size) {
  grid_size_ = size;
}

QRect GlobalOptions::tile_selection() const {
  return tile_selection_;
}

void GlobalOptions::set_tile_selection(const QRect &selection) {
  tile_selection_ = selection;
}

void GlobalOptions::UpdateCursorShift() {
  horizontal_shift_ = ((tile_selection_.width() / cursor_size().width()) % 2 == 0);
  vertical_shift_ = ((tile_selection_.height() / cursor_size().height()) % 2 == 0);
}

void GlobalOptions::CleanCursorShift() {
  horizontal_shift_ = false;
  vertical_shift_ = false;
}

void GlobalOptions::MoveSelection(const QPoint &center) {
  tile_selection_.moveCenter(center);
}

QRect GlobalOptions::PosToGrid(const QPoint &pos) const {
  int x = (horizontal_shift_ ? cursor_size_.width() / 2 : 0);
  int y = (vertical_shift_ ? cursor_size_.height() / 2 : 0);
  QPoint top_left = QPoint(
      ((pos.x() + x) / cursor_size_.width()) * cursor_size_.width() - x,
      ((pos.y() + y) / cursor_size_.height()) * cursor_size_.height() - y);

  return QRect(top_left, cursor_size_);
}

QSize GlobalOptions::new_image_size() const {
  return new_image_size_;
}

void GlobalOptions::set_new_image_size(const QSize &size) {
  new_image_size_ = size;
}

bool GlobalOptions::transparency_enabled() const {
  return transparency_enabled_;
}

void GlobalOptions::set_transparency_enabled(bool transparency) {
  transparency_enabled_ = transparency;
}

int GlobalOptions::zoom() const {
  return zoom_;
}

void GlobalOptions::set_zoom(int zoom) {
  zoom_ = clamp(zoom, 1, 32);
}

QColor GlobalOptions::main_color() const {
  return main_color_;
}

void GlobalOptions::set_main_color(const QColor &color) {
  main_color_ = color;
}

QColor GlobalOptions::alt_color() const {
  return alt_color_;
}

void GlobalOptions::set_alt_color(const QColor &color) {
  alt_color_ = color;
}

void GlobalOptions::set_new_image_color(const QColor &color) {
  new_image_color_ = color;
}

QColor GlobalOptions::new_image_color() const {
  return new_image_color_;
}

void GlobalOptions::SaveState(QSettings *settings) const {
  settings->setValue(kStateCursorSize, cursor_size_);
  settings->setValue(kStateGridSize, grid_size_);
  settings->setValue(kStateNewImageSize, new_image_size_);
  settings->setValue(kStateTransparency, transparency_enabled_);
  settings->setValue(kStateZoomLevel, zoom_);
  settings->setValue(kStateTool, tool_);
  settings->setValue(kStateColorMain, main_color_.name());
  settings->setValue(kStateColorAlt, alt_color_.name());
  settings->setValue(kStateLanguage, language_);
  settings->setValue(kStateNewImageColor, new_image_color_);
  settings->setValue(kStateShowGrid, show_grid_);
  settings->setValue(kStateShowPixelGrid, show_pixel_grid_);
}

#define SETTINGS_VALUE(var) (settings->value(var, var##Default))

void GlobalOptions::LoadState(QSettings *settings) {
  cursor_size_ = SETTINGS_VALUE(kStateCursorSize).toSize();
  grid_size_ = SETTINGS_VALUE(kStateGridSize).toSize();
  tile_selection_.setSize(cursor_size_);
  tile_selection_.setTopLeft(QPoint(0, 0));
  new_image_size_ = SETTINGS_VALUE(kStateNewImageSize).toSize();
  transparency_enabled_ = SETTINGS_VALUE(kStateTransparency).toBool();
  set_zoom(SETTINGS_VALUE(kStateZoomLevel).toInt());
  set_tool((TOOL_ENUM)SETTINGS_VALUE(kStateTool).toInt());
  main_color_ = QColor(SETTINGS_VALUE(kStateColorMain).toString());
  alt_color_ = QColor(SETTINGS_VALUE(kStateColorAlt).toString());
  language_ = SETTINGS_VALUE(kStateLanguage).toString();
  new_image_color_ = SETTINGS_VALUE(kStateNewImageColor).toString();
  show_grid_ = SETTINGS_VALUE(kStateShowGrid).toBool();
  show_pixel_grid_ = SETTINGS_VALUE(kStateShowPixelGrid).toBool();
}

#undef SETTINGS_VALUE

void GlobalOptions::set_tool(const TOOL_ENUM tool) {
  tool_ = tool;
}

TOOL_ENUM GlobalOptions::tool() const {
  return tool_;
}

void GlobalOptions::set_language(const QString &language) {
  language_ = language;
}

QString GlobalOptions::language() const {
  return language_;
}

bool GlobalOptions::show_grid() const {
  return show_grid_;
}

void GlobalOptions::set_show_grid(bool show) {
  show_grid_ = show;
}

bool GlobalOptions::show_pixel_grid() const {
  return show_pixel_grid_;
}

void GlobalOptions::set_show_pixel_grid(bool show) {
  show_pixel_grid_ = show;
}
