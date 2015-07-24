# Created: 12/10/2014 4:12:26 PM
# Author: Ketil Wright
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.0)
# single variable which determines output executable name
set(ProjectName FnPlot)
# map OS -> compiler definitions
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-DDarwin)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
    #TODO: bring the path to Qt in more generally\
    message("Using qt at " $ENV{QTDIR})
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QTDIR})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DLinux)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DWin32)
else()
    message("Unknown host")    
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtWidgets library
# find_package(Qt5Core)
find_package(Qt5Widgets)

# list of source files
set(ProjectSources 
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    libGenerator.cpp
    dataset.cpp
    qcustomplot.cpp)

set(ProjectIncludes 
    dataset.h
    mainwindow.h
    dlLoader.hpp 
    libGenerator.hpp
    qcustomplot.h)

include_directories(${Qt5Widgets_INCLUDES})
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# output an executable from the specified sources
add_executable(${ProjectName} ${ProjectSources} ${ProjectIncludes})
# link to project libraries
#target_link_libraries(${ProjectName} myLib)
target_link_libraries(${ProjectName} ${CMAKE_DL_LIBS})

qt5_use_modules(${ProjectName} Widgets PrintSupport)
# Work in progress -> Installation
# install(TARGETS ${ProjectName} RUNTIME DESTINATION bin )
# include(CPack)
