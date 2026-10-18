# DroneView 🚁📹

**DroneView** is a ground station video receiver application built with C++17, Qt, and GStreamer. It provides real-time video stream ingestion, hardware/software decoding, digital zooming, dynamic pipeline configuration, and OpenGL-based video rendering.

---

## 🛠️ Tech Stack

* **Language:** C++17
* **GUI Framework:** Qt 6 / Qt 5 (Widgets, OpenGLWidgets, MultimediaWidgets)
* **Multimedia Framework:** GStreamer 1.0 (`gstreamer-1.0`, `gstreamer-video-1.0`)
* **Build System:** CMake (v3.16+) with support for Ninja and Make generators

---

## ⚙️ Prerequisites & Dependencies

### Ubuntu / Debian
Install the required development packages for Qt and GStreamer:

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    ninja-build \
    qt6-base-dev \
    qt6-multimedia-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-libav \
    pkg-config
```

---

## 🚀 Building & Running

1. Clone the repository:
```bash
git clone https://github.com/gbitsys/DroneView.git
cd DroneView
```

2. Configure and Build:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

3. Run the Application:
```bash
./DroneView
```
