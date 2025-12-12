# cub3D
A ray-casting game: an advanced graphical project where we create a simplified 3D game, whose goal is to learn a rendering technique called ray casting.

## Quick Start

### Prerequisites (Ubuntu/Debian)
Install required X11 and BSD libraries:
```bash
sudo apt-get update
sudo apt-get install -y libx11-dev libxext-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libbsd-dev
```

### Build and Run
```bash
# Clone the repository
git clone https://github.com/kaierhyeh/42-Cursus.git
cd 42-Cursus/cub3D

# Build the project
make

# Run with test map
./cub3D maps/test.cub
```

### Controls
- **W / A / S / D**: Move forward / left / backward / right
- **← / →**: Rotate camera left / right
- **Mouse Movement**: Look around
- **Space / Left Click**: Interact with doors
- **ESC**: Exit game

## Key Concepts
1. Parsing Maps, Wall texture paths, and initializing images.
2. Use a recursive function (floodfill) to check if a Map is valid that the player will never go outside of bound.
3. Building a vector library for vector calculations (optional)
4. What is Raycasting and how it helps to make 3D rendering efficient?
5. What is DDA algorithm? Why it helps to optimize rendering?
6. Rendering images in a resized fashion (Wall texture rendering)
7. Create multiple images and put in in the same window (Mini map, Sprite)
8. Create a script of frames and generate animation effects (Animation)

## Resources
1. [`Guide`](https://harm-smits.github.io/42docs/projects/cub3d) <br>
2. [`Reference`](https://github.com/pasqualerossi/Cub3D) <br>
3. [`Guide from Tsunghao`](https://github.com/Tsunghao-C/Common-Course/tree/main/cub3d) <br>
4. [`Reference to Jean`](https://github.com/Haliris/cub3d/tree/main) <br>
5. [`Maximum effort`](https://github.com/ael-bekk/Cub3d-Advanced-Raycasting) <br>
6. [`Tutorial of building a ray casting game`](https://lodev.org/cgtutor/raycasting.html) <br>
7. [`DDA algorithm`](https://youtu.be/NbSee-XM7WA?si=taWsY2doGi90ieGD) <br>
8. [`Evaluation sheet`](https://www.42evals.com/sheets/66ba244998d302d110c31b6a) <br>
9. `Demo` [Google Drive](https://drive.google.com/file/d/18nyvWhlfFrl5MYFPbCmYqgHLxpVqhpPM/view?usp=sharing) <br>
