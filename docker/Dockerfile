FROM osrf/ros:kinetic-desktop-full

ENV NVIDIA_VISIBLE_DEVICES \
    ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES \
    ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics

RUN apt-get update && apt-get install -y apt-utils build-essential psmisc vim-gtk

RUN rm /bin/sh && ln -s /bin/bash /bin/sh

RUN apt-get update && apt-get install -q -y ros-kinetic-catkin python-catkin-tools

RUN apt-get update && apt-get install -q -y ros-kinetic-octomap-ros ros-kinetic-octomap-mapping


RUN apt-get install -q -y ros-kinetic-joy
 

#   ros-kinetic-octomap ros-kinetic-octomap-mapping && \
#   ros-kinetic-octomap-msgs ros-kinetic-octomap-ros && \
#   ros-kinetic-octomap-rviz-plugins ros-kinetic-octomap-server
 
 
# Install git lfs. Necessary in order to properly clone 
RUN echo 'deb http://http.debian.net/debian wheezy-backports main' > /etc/apt/sources.list.d/wheezy-backports-main.list
RUN curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | bash
RUN apt-get install -q -y git-lfs
RUN git lfs install

ENV ROTORS_WS=/RotorS_workspace

RUN source /opt/ros/melodic/setup.bash && \
    mkdir -p $ROTORS_WS/src && \
    cd $ROTORS_WS/src && \
    catkin_init_workspace && \
    git clone https://github.com/Marslanali/cpp-rotors-simulations.git && \    
    cd $ROTORS_WS && \
    catkin_make && \
    catkin_make install

EXPOSE 11345

COPY ./rotors_sim_entrypoint.sh /

ENTRYPOINT ["/rotors_sim_entrypoint.sh"]

CMD ["bash"]


