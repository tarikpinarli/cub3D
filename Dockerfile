FROM ubuntu:22.04

# Avoid tzdata interactive prompts and others
ENV DEBIAN_FRONTEND=noninteractive

# Update system and install packages for C dev, MLX42 requirements, and VNC/noVNC
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libglfw3-dev \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    valgrind \
    xvfb \
    x11vnc \
    openbox \
    novnc \
    websockify \
    mesa-utils \
    libgl1-mesa-dri \
    && rm -rf /var/lib/apt/lists/*

# Set up the working directory inside the container
WORKDIR /app

# Ensure OpenGL rendering reverts to software using Mesa llvmpipe (since there's no GPU)
ENV LIBGL_ALWAYS_SOFTWARE=1
ENV DISPLAY=:0

# Keep the virtual display, VNC, and web portal running in the background for interactive development
CMD bash -c "Xvfb :0 -screen 0 1280x960x24 -listen tcp -ac & \
    sleep 1 && openbox-session & \
    sleep 1 && x11vnc -display :0 -nopw -forever -shared -bg & \
    websockify --web=/usr/share/novnc/ 8080 localhost:5900 & \
    sleep infinity"
