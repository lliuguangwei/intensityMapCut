#include <iostream>
#include <string>
#include <iterator>
#include <vector>

// opencv
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

// pcl
#include <pcl/io/pcd_io.h> //PCL的PCD格式文件的输入输出头文件
#include <pcl/io/ply_io.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/point_types.h> //PCL对各种格式的点的支持头文件

using namespace pcl;
using namespace pcl::io;
using namespace std;
using namespace cv;

    // string name = std::to_string((int)min_x) + std::to_string((int)min_y);
int main(int argc, char* argv[]){
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_all(new pcl::PointCloud<pcl::PointXYZI>);
	for(int i = 8; i < 11; ++i){
		for(int j = 5; j < 8; ++j){
			pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);
			string pointPath;
			if(i < 10){
				pointPath = "/media/lgw/1E25997C69162698/lgwei/intensityMap/2018-05-14-11-01-44-1cm/pcd/p0100" + std::to_string(i) + "_n0079" + std::to_string(j) + ".txt.pcd";
			}else{
				pointPath = "/media/lgw/1E25997C69162698/lgwei/intensityMap/2018-05-14-11-01-44-1cm/pcd/p010" + std::to_string(i) + "_n0079" + std::to_string(j) + ".txt.pcd";
			}
			if(pcl::io::loadPCDFile<pcl::PointXYZI>(pointPath, *cloud) == -1){
				cout << pointPath << endl;
				continue;
			}
			*cloud_all += *cloud;
		}
	}

	// pcl::io::savePCDFile ("mergePCD.pcd", *cloud_all); //将点云保存到PCD文件中
	pcl::io::savePCDFileBinary ("mergePCD.pcd", *cloud_all); //将点云保存到PCD文件中
	// pcl::io::savePCDFileASCII ("mergePCD.pcd", *cloud_all); 

	return 0;
}