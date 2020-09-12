## RotorS UAV gazebo simualtions

This repository houses UAV RotorS simuation for analysis and development purposes. RotorS simulation framework is originallly developed at [Autonomous System Lab](https://hub.docker.com/r/osrf/subt-virtual-testbed), ETH Zurich. Please visit [RotorS here](https://hub.docker.com/r/osrf/subt-virtual-testbed) for main repository. 

### Quick Start (With Docker)

To begin with, let's get the development environment up and running locally. The best way to get the environment along with all of the dependencies is by using `docker`. The latest RotorS release is always hosted on [DockerHub](https://hub.docker.com/r/osrf/subt-virtual-testbed).

- Note! **If you want to build on your local machine without using Docker you can follow [instruction here](https://hub.docker.com/r/osrf/subt-virtual-testbed)** 

If you do not know what `Docker` is, Its highly suggest checking it out. `Docker` can be used to quickly experiment with the simulation without polluting your system with additional packages. See this page to get started. This particular image relies on [nvidia-docker2](https://hub.docker.com/r/osrf/subt-virtual-testbed). For now, an NVidia GPU is required if you want to run the graphics from within the container. If you only care about running the simulation headless (no graphics), then Docker is the only requirement.

Before installing docker, take a look at the [system requirements](https://github.com/osrf/subt/wiki/system_requirements).
The simulator relies on having a hardware-accelerated graphics card in order to do rendering for the user interface as well as simulated sensors.

If you don't already have `docker` installed on your system, then it's best to follow the installation instructions in the [Installation Wiki](https://github.com/osrf/subt/wiki/tutorials/SystemSetupDockerInstall).

It is important to note that you need `docker` and `nvidia-docker` in order to get the simulation environment to work.

As a quick sanity check, you can verify if docker is installed correctly by running:

```
$ docker run hello-world
```

If all goes well, you should see something like the following:
```
Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
```

If this is your first time installing `docker`, you may need to add your user to the `docker` group to run the above command without `sudo` (in this case, `sudo` should not be required).
To add your user to the group: `sudo usermod -a -G docker $USER` (you will need to restart your machine after entering this command in order for changes to take effect)

You can then verify that nvidia-docker is properly configured with the following:
```
docker run --runtime=nvidia --rm nvidia/cuda nvidia-smi
```

Once again, if it is installed correctly, you should see information about your video card, for example:
```
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 390.116                Driver Version: 390.116                   |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  GeForce GTX 106...  Off  | 00000000:01:00.0  On |                  N/A |
|  0%   48C    P0    27W / 200W |    957MiB /  6075MiB |      3%      Default |
+-------------------------------+----------------------+----------------------+

+-----------------------------------------------------------------------------+
| Processes:                                                       GPU Memory |
|  GPU       PID   Type   Process name                             Usage      |
|=============================================================================|
+-----------------------------------------------------------------------------+
```

Note, the CUDA version of the container needs to match what is installed on your host.
If you know that you have CUDA 9.0 installed, or if you get errors when trying to run the `nvidia/cuda:latest` image, try running the following instead:
```
docker run --runtime=nvidia --rm nvidia/cuda:9.0-base nvidia-smi
```

### Quick Start (Without Docker)

To build on your local machine without using Docker you see follow [instruction here](https://hub.docker.com/r/osrf/subt-virtual-testbed). 

If you don't have ROS workspace yet you can do so by:

```
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/src
$ catkin_init_workspace  # initialize your catkin workspace
$ cd ~/catkin_ws/
$ catkin init
$ cd ~/catkin_ws/src
$ git clone -b RotorS git clone https://github.com/Marslanali/cpp-uav-simulations.git 
```

Build your workspace with python_catkin_tools (therefore you need `python_catkin_tools`)

```
$ rosdep install --from-paths src -i
$ catkin build
```

Add sourcing to your .bashrc file

```
$ echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
$ source ~/.bashrc
```


## RotorS gazebo OctoMap simulations

If you don't have ROS workspace yet you can do so by

```
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/src
$ catkin_init_workspace  # initialize your catkin workspace
$ cd ~/catkin_ws/
$ catkin init
$ cd ~/catkin_ws/src
$ git clone -b RotorS-octomap https://github.com/Marslanali/cpp-uav-simulations.git

```

Build your workspace with python_catkin_tools (therefore you need python_catkin_tools)

```
$ rosdep install --from-paths src -i
$ catkin build
```

Add sourcing to your .bashrc file

```
$ echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
$ source ~/.bashrc
```

## Install the OctoMap library:

The OctoMap library is an open source library for generating volumetric 3D environment models from sensor data. This model data can then be used by a drone for navigation and obstacle avoidance.

```
sudo apt-get install ros-kinetic-octomap ros-kinetic-octomap-mapping
rosdep install octomap_mapping
rosmake octomap_mapping
```

Now, open `~/catkin_ws/src/rotors_simulator/rotors_gazebo/CMakeLists.txt` and add the following lines to the bottom of the file

```
find_package(octomap REQUIRED)
include_directories(${OCTOMAP_INCLUDE_DIRS})
link_libraries(${OCTOMAP_LIBRARIES})
```

Open `~/catkin_ws/src/rotors_simulator/rotors_gazebo/package.xml` and add the following lines

```
<build_depend>octomap</build_depend>
<run_depend>octomap</run_depend>
```

Open `rosed octomap_server octomap_tracking_server.launch`

and change the two following lines:

```
<param name="frame_id" type="string" value="map" />
...
<!--remap from="cloud_in" to="/rgbdslam/batch_clouds" /-->
```

to:

```
<param name="frame_id" type="string" value="world" />
...
<remap from="cloud_in" to="/firefly/vi_sensor/camera_depth/depth/points" />
```

## Running the simulation

Run the following three lines in separate terminal windows. This opens up Gazebo, Rviz and an octomap server.

```
roslaunch rotors_gazebo mav_hovering_example_with_vi_sensor.launch  mav_name:=firefly
roslaunch octomap_server octomap_tracking_server.launch
```

In Rviz, change the field `'Fixed Frame'` from `'map'` to `'world'` in the top left of the window. Now click the add button in the bottom left and select `MarkerArray`. Then double click the MarkerArray and change `'Marker Topic'` from `'/free_cells_vis_array'` to `'/occupied_cells_vis_array'`.

Now you should see a part of the floor.

In the Gazebo window, insert a cube in front of the red rotors and you should see it in Rviz.

