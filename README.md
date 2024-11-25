# FdF
# 🗺️ FdF - Wireframe Representation in 3D

**FdF** is a 3D wireframe visualizer written in C using the **MiniLibX** library. The goal of the project is to represent a 2D map in a 3D perspective using isometric projection.

![FdF preview](https://github.com/vlrlmn/FdF/blob/main/FdF/images/ZXCVsizechange-ezgif.com-video-to-gif-converter.gif)
---

## 🚀 Project Highlights

- **3D Wireframe Rendering:** Converts 2D maps into interactive 3D visualizations.
- **Isometric Projection:** Applies mathematical transformations to display a 3D perspective.
- **Customizable View:** Includes zoom, rotation, and color adjustment for better visualization.
- **MiniLibX Integration:** Utilizes the lightweight graphical library for rendering.

---

## 📋 Features

- **Render 3D maps from 2D data:**  
  Input: A `.fdf` file with map coordinates.  
  Output: A 3D wireframe displayed in an interactive window.

- **Interactive Controls:**  
  - Zoom in/out  
  - Rotate along X, Y, and Z axes  
  - Adjust projection and colors  

- **Error Handling:**  
  Gracefully manages invalid file formats or incorrect input.

---

## 🛠️ Tech Stack

- **Language:** C
- **Library:** MiniLibX (for graphics and event handling)
- **Tools:** GCC, Makefile, top memory management

---

## 🖥️ How to Run

Clone the repository:
   ```bash
   git clone https://github.com/vlrlmn/FdF.git
   cd FdF
   ```
Compile the project
```bash
  make
```
Run the program
```bash
  ./fdf maps/42.fdf
```
# 🗺️ Map example

Here's a simple .fdf map:
```
0  0  0  0  0
0  5  5  5  0
0  5  10 5  0
0  5  5  5  0
0  0  0  0  0
```
The program will render this as a 3D wireframe with elevation.

## 🎮 Controls
| Key          | Action                                   |
|--------------|-----------------------------------------|
| Arrow Keys   | Move the map                            |
| `Z` / `X`    | Zoom in/out                             |
| `S` / `A`    | Rotate on Y axis                        |
| `B` / `N`    | Rotate on X axis                        |
| `C` / `V`    | Adjust height along the Z axis (convex/concave) |
| `ESC` / `Q`  | Exit the program                        |

# 🖼️ Demo

### Arrow moves
![arrow moves](https://github.com/vlrlmn/FdF/blob/main/FdF/images/arrowmoves-ezgif.com-video-to-gif-converter.gif)

### X-axis rotation
![Xrotations](https://github.com/vlrlmn/FdF/blob/main/FdF/images/BNrotations-ezgif.com-video-to-gif-converter.gif)

### Y-axis rotation
![Yrotations](https://github.com/vlrlmn/FdF/blob/main/FdF/images/ASrotations-ezgif.com-video-to-gif-converter.gif)

### Zoom in/out and change the height of Z-index
![zoom](https://github.com/vlrlmn/FdF/blob/main/FdF/images/ZXCVsizechange-ezgif.com-video-to-gif-converter.gif)
