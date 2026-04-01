# cub3D 🕹️

A raycasting 3D engine built in C, inspired by the classic Wolfenstein 3D. 
This project uses the **MLX42** graphics library and has been fully **Dockerized** with a **noVNC Web Interface** so it can run seamlessly on any operating system (macOS, Windows, Linux) straight from your web browser, without needing complex X11 display configurations!

---

## 🚀 Getting Started

### Prerequisites
You only need two things installed on your machine:
- [Git](https://git-scm.com/)
- [Docker Engine & Docker Compose](https://docs.docker.com/get-docker/)

### 1. Clone the Repository
```bash
git clone https://github.com/tarikpinarli/cub3D.git
cd cub3D
```

### 2. Start the Docker Environment
Because the MLX42 graphics library requires specific Linux dependencies, we've wrapped the entire development environment in a headless Ubuntu container.
```bash
make docker-up
```
*(This will download the Ubuntu image, install CMake, GCC, and the VNC server. It takes a minute or two the first time).*

### 3. Enter the Container
Drop into the active Linux container terminal:
```bash
make docker-run
```

### 4. Compile the Game
Once inside the `root@container:/app#` terminal, simply run `make` to clone the graphics library and compile the game natively.
```bash
make
```

### 5. Play!
Launch the game by passing one of the map files as an argument:
```bash
./cub3D maps/matrix.cub
```

### 6. View the Game in your Browser 🌐
The game is running inside a virtual display buffer in the container. To actually see and play the game, open your web browser and go to:
> **[http://localhost:8080/vnc.html](http://localhost:8080/vnc.html)**

---

## 🎮 Controls

Click inside the browser window to focus the game, then use:

- **`W` `A` `S` `D`** : Move Up, Left, Down, Right
- **`←` `→`** (Arrow Keys): Rotate Camera Left / Right
- **`ESC`** : Close the game

---

## 🧹 Cleaning Up

While inside the container, you can clean the build files:
```bash
make clean    # Removes object files
make fclean   # Removes object files, the executable, and the MLX42 library
```

When you are done playing, type `exit` to leave the container. 
To shut down the background Docker servers and free up your ports:
```bash
make docker-down
```

---

## 🛠️ Volumes & Troubleshooting

**"Device or resource busy" on Mac?**
We use Docker *Anonymous Volumes* for `/obj` and `/lib/MLX42` to completely bypass macOS's `virtiofs` file-syncing. This prevents Docker from deadlocking when CMake creates thousands of tiny files during compiling. 
If you ever experience weird file sync issues, just run:
```bash
make docker-down
make docker-up
```
This instantly wipes the local anonymous volumes and gives you a completely fresh native Linux filesystem!
