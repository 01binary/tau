# Tau Cannon

Tau Cannon Replica from Half Life: https://www.01binary.us/projects/tau-cannon

# Building

The on-board targeting computer uses OpenCV to perform pose detection.

[Building OpenCV on Raspbery Pi 4](https://learnopencv.com/build-and-install-opencv-4-for-raspberry-pi/)

```
cd src
cmake .
make
```

This will output the executable called `tau` which can be set to run at startup.
