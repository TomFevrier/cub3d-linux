# Cub3D

**A [Wolfenstein 3D](https://fr.wikipedia.org/wiki/Wolfenstein_3D) clone, coded in C using the [minilibx](https://github.com/42Paris/minilibx-linux) library. Linux version.**

---

## How to play

#### Install minilibx
- `git clone https://github.com/42Paris/minilibx-linux && cd minilibx-linux`
- `make`
- `sudo cp libmlx.a /usr/local/lib && sudo cp mlx.h /usr/local/include`

#### Compile the game
- `git clone https://github.com/TomFevrier/cub3d-linux && cd cub3d-linux`
- `make` OR `make bonus` to compile the extended version 
- if compilation fails (`cannot find -lbsd`), install libbsd: `sudo apt install libbsd-dev` (Ubuntu/Debian)
- make sure ffplay is installed, if not: `sudo apt install ffmpeg` (Ubuntu/Debian)

#### Run the game
- `./Cub3D levels/[level_name].cub` OR `./Cub3D_bonus levels/[level_name]_bonus.cub`

**Enjoy! You can also create your own maps by creating a valid CUB file ;)**
