/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012-2014, Willow Garage, Inc.
 *  Copyright (c) 2014-2016, Open Source Robotics Foundation
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Open Source Robotics Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FCL_CONFIG_
#define FCL_CONFIG_

#define FCL_VERSION "0.5.0"
#define FCL_MAJOR_VERSION 0
#define FCL_MINOR_VERSION 5
#define FCL_PATCH_VERSION 0

#define FCL_HAVE_SSE 0
#define FCL_HAVE_OCTOMAP 1
#define FCL_HAVE_TINYXML 0

#define FCL_BUILD_TYPE_DEBUG 0
#define FCL_BUILD_TYPE_RELEASE 1

#if FCL_HAVE_OCTOMAP
  #define OCTOMAP_MAJOR_VERSION 1
  #define OCTOMAP_MINOR_VERSION 8
  #define OCTOMAP_PATCH_VERSION 1

  #define OCTOMAP_VERSION_AT_LEAST(x,y,z) \
    (OCTOMAP_MAJOR_VERSION > x || (OCTOMAP_MAJOR_VERSION >= x && \
    (OCTOMAP_MINOR_VERSION > y || (OCTOMAP_MINOR_VERSION >= y && \
    OCTOMAP_PATCH_VERSION >= z))))

  #define OCTOMAP_VERSION_AT_MOST(x,y,z) \
    (OCTOMAP_MAJOR_VERSION < x || (OCTOMAP_MAJOR_VERSION <= x && \
    (OCTOMAP_MINOR_VERSION < y || (OCTOMAP_MINOR_VERSION <= y && \
    OCTOMAP_PATCH_VERSION <= z))))
#endif // FCL_HAVE_OCTOMAP

#endif
