//
// Created by KoTz on 13/11/2026.
//

#ifndef QTWIDGETSTOOLKIT_BADGE_H
#define QTWIDGETSTOOLKIT_BADGE_H

#include <QEvent>
#include <QLabel>
#include <QPushButton>

namespace QtToolkit
{
namespace Badge
{
enum Position
{
    CENTER = 0,
    TOP_LEFT,
    TOP,
    TOP_RIGHT,
    LEFT,
    RIGHT,
    BOTTOM_LEFT,
    BOTTOM,
    BOTTOM_RIGHT
};
struct BADGE_PRODPY {
  QString BACKGROUND_COLOR = "#2e9e44";
  QString COLOR_TEXT_BADGE = "#FFFFFF";
  Position BADGE_POSITION = TOP_RIGHT;
  int  FONT_SIZE = 11;            // em px
  QString BORDER_RADIUS = "10px";
  QString FONTE_WEIGHT = "bold";

};

QLabel* attach(QPushButton* button,int count,BADGE_PRODPY OBJ);
QLabel* attach
(
     QPushButton* button,
     int count = 0,
     const QString BACKGROUND_COLOR = "#2e9e44"
  ,  const QString COLOR_TEXT_BADGE = "#FFFFFF",
     Position BADGE_POSITION = TOP_RIGHT
  ,  QString FONT_WEIGHT = "bold"
  ,  int FONT_SIZE = 11
  ,  QString BORDER_RADIUS = "10px"
  );

void setCount(QLabel* badge, int count);
}  // namespace Badge
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_BADGE_H
