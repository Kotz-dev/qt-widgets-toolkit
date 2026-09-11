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

## Requirements

- CMake >= 3.21
- C++20-capable compiler
- Qt6 (`Core`, `Gui`, `Widgets` components)

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

Produces the static library `QtWidgetStoolkit` (`libQtWidgetStoolkit.a` on Linux/macOS, `QtWidgetStoolkit.lib` on Windows).

## Installation

```bash
cmake --install build --prefix <destination-directory>
```

This installs the headers and the compiled library together with the CMake config files (`QtWidgetStoolkitConfig.cmake`), so the package can be consumed without needing the source `.cpp` files.

## Using it in another project

Point `CMAKE_PREFIX_PATH` at the directory where the library was installed and use `find_package`:

```cmake
find_package(QtWidgetStoolkit REQUIRED)
target_link_libraries(my_app PRIVATE QtWidgetStoolkit::QtWidgetStoolkit)
```

```cpp
#include <QtWidgetStoolkit/QtWidgetStoolkit.h>   // everything at once
// or
#include <QtWidgetStoolkit/Animation.h>          // a single module
```

## Using it via vcpkg

This repository doubles as its own private vcpkg registry (`ports/` + `versions/` at
the repo root). Every time a GitHub Release is published here, the
[`vcpkg-registry-update`](.github/workflows/vcpkg-registry-update.yml) workflow
points the port at the new tag and regenerates the version database automatically
— no manual step on this side.

To consume it from another project, add a `vcpkg-configuration.json` next to your
`vcpkg.json`:

```json
{
  "default-registry": {
    "kind": "builtin",
    "baseline": "<commit-sha-of-the-vcpkg-baseline-you-use>"
  },
  "registries": [
    {
      "kind": "git",
      "repository": "https://github.com/Kotz-dev/qt-widgets-toolkit",
      "baseline": "<commit-sha-on-Master>",
      "packages": ["qtwidgetstoolkit"]
    }
  ]
}
```

Then add `"qtwidgetstoolkit"` to your `vcpkg.json` dependencies. The `baseline`
must be a commit SHA on `Master` (vcpkg pins to a specific commit for
reproducible builds) — bump it whenever you want to pick up a newer release.

For local development against this working copy instead of a tagged release,
use the overlay port in `vcpkg-overlay/` with `--overlay-ports=vcpkg-overlay/ports`.


