<div align="center">
  <img src="img/logo.png" alt="QtToolkit" width="418">

  ![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus)
  ![Qt](https://img.shields.io/badge/Qt-41CD52?style=flat&logo=qt)
  ![License](https://img.shields.io/badge/license-MIT-green)

  Reusable Qt Widgets components (splitter, blur effect, window dragging/maximizing, animations) extracted from personal projects.

  ⚠️ **Work in progress** — API may change, not all components are fully tested yet.
</div>

---

## Components

| Component | Description |
|---|---|
| `Splitter::setupSplitter` | Turns two existing widgets into a draggable-divider layout |
| `Blur::render` | Captures and blurs a widget's content, useful for modal backdrops |
| `Window::Dragger` | Makes a frameless window draggable via a title bar area |
| `Window::Maximizer` | Animated window maximize/restore for frameless windows |
| `ProgessBar::SegmentedProgressBar` | Segmented progress bar with animated color transitions |
| `Animation::fadeSlideIn` | Fade + slide-in entrance animation |
| `geometry::centeredPosition` | Computes a centered position for a child widget inside a parent |

## Usage

No build system dependency — copy the header/source files you need directly into your project.

```cpp
#include "QtWidgetsToolkit.h"

// Splitter
QtToolkit::Splitter::setupSplitter(ui->parent, ui->frame_18, ui->stackedWidget_2);

// Blur
QLabel *blurred = QtToolkit::Blur::render(this, 20.0);

// Frameless window drag + maximize
QtToolkit::Window::Dragger::attach(ui->titleBar);
QtToolkit::Window::Maximizer maximizer;
maximizer.toggle(this);
```

## Known limitations

- `Window::Dragger` and `ProgessBar::SegmentedProgressBar` currently use a shared 
  (singleton-style) instance internally — only one active instance is supported 
  per application at this time.
