# ADD_EXECUTABLE( mergePCD mergePCD.cpp )

# 增加PCL库的依赖
# FIND_PACKAGE( PCL REQUIRED COMPONENTS common io visualization filters )
FIND_PACKAGE( PCL REQUIRED )
# list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4") # use this in Ubuntu 16.04

# 增加opencv的依赖
FIND_PACKAGE( OpenCV REQUIRED )

# 添加头文件和库文件
ADD_DEFINITIONS( ${PCL_DEFINITIONS} )
INCLUDE_DIRECTORIES( ${PCL_INCLUDE_DIRS}  )
LINK_LIBRARIES( ${PCL_LIBRARY_DIRS} )

ADD_EXECUTABLE( intensityMapCut intensityMapCut.cpp )
TARGET_LINK_LIBRARIES( intensityMapCut 
    ${OpenCV_LIBS} 
    ${PCL_LIBRARIES} )
