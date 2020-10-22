## RotorS UAV gazebo simulation

This repository houses UAV RotorS simuation for analysis and development purposes. RotorS simulation framework is originallly developed at [Autonomous System Lab](https://hub.docker.com/r/osrf/subt-virtual-testbed), ETH Zurich. Please visit [RotorS here](https://hub.docker.com/r/osrf/subt-virtual-testbed) for main repository. 

### Quick Start

If you don't have ROS workspace yet you can do so by:

```
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/src
$ catkin_init_workspace  # initialize your catkin workspace
$ cd ~/catkin_ws/
$ catkin init
$ cd ~/catkin_ws/src
$ git clone -b RotorS https://github.com/Marslanali/cpp-rotors-simulation.git 
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


## Flexible Collision Library (FCL)
FCL is MoveIt’s default collision checker, their official install instructions can be found here.

```
sudo apt -qq install libccd-dev
```

Clone the repo into your catkin workspace:

```
git clone https://github.com/flexible-collision-library/fcl
cd fcl
```
Pick the correct version depending on the version of MoveIt you use:
```
git checkout fcl-0.5   # for kinetic
git checkout master    # for melodic+
```

Next manually add a package.xml as used in the ROS release wrapper:
```
wget https://raw.githubusercontent.com/ros-gbp/fcl-release/debian/jade/fcl/package.xml
```

```
mkdir build
cd build
cmake ..
make
sudo make all
```
## Open Motion Planning Library

```
sudo apt-get -y install ros-kinetic-ompl*

```


## Error

```
/usr/bin/ld: cannot find -loctomap
/usr/bin/ld: cannot find -loctomath
collect2: error: ld returned 1 exit status
make[2]: *** [/home/arslan/catkin_ws/devel/.private/path_planning/lib/path_planning/old_path_planning] Error 1
make[1]: *** [CMakeFiles/old_path_planning.dir/all] Error 2
make[1]: *** Waiting for unfinished jobs....
/usr/bin/ld: cannot find -loctomap
/usr/bin/ld: cannot find -loctomath
collect2: error: ld returned 1 exit status
make[2]: *** [/home/arslan/catkin_ws/devel/.private/path_planning/lib/path_planning/path_planning_node] Error 1
make[1]: *** [CMakeFiles/path_planning_node.dir/all] Error 2
make: *** [all] Error 2

```

## Solution

```
sudo apt install liboctomap-dev

```
