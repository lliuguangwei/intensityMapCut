#include <iostream>
#include <string>
#include <iterator>
#include <vector>

// pcl
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/PCLPointCloud2.h>

using namespace pcl;
using namespace pcl::io;
using namespace std;

int  main(int argc, char* argv[]) {

    string pcdPath = string(argv[1]);
    string plyPath = string(argv[2]);
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_all(new pcl::PointCloud<pcl::PointXYZI>);
    pcl::io::loadPCDFile<pcl::PointXYZI>(pcdPath, *cloud_all);
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_sub(new pcl::PointCloud<pcl::PointXYZI>);
    pcl::io::loadPLYFile<pcl::PointXYZI>(plyPath, *cloud_sub);
    cout << "load PointCloud ok!" << endl;
   
    double x_min = DBL_MAX;
    double y_min = DBL_MAX;
    double x_max = -DBL_MAX;
    double y_max = -DBL_MAX;

    for (int i = 0; i < cloud_all->size(); i++) {
        pcl::PointXYZI &point = cloud_all->points[i];
        if (x_min > point.x) x_min = point.x;
        if (x_max < point.x) x_max = point.x;
        if (y_min > point.y) y_min = point.y;
        if (y_max < point.y) y_max = point.y;
    }

    double round_scale = 100;
    x_max = round(x_max * round_scale) / round_scale;
    x_min = round(x_min * round_scale) / round_scale;
    y_max = round(y_max * round_scale) / round_scale;
    y_min = round(y_min * round_scale) / round_scale;

    // expand
    double grid_size_ = 0.1;
    x_max += 3 * grid_size_ / 2;
    x_min -= 3 * grid_size_ / 2;
    y_max += 3 * grid_size_ / 2;
    y_min -= 3 * grid_size_ / 2;

    double size_x = ceil((x_max - x_min) / grid_size_);
    double size_y = ceil((y_max - y_min) / grid_size_);

    // init marker
    std::vector<std::vector<int> > map_sub;
    for (int i = 0; i < size_y; ++i) {
        map_sub.push_back(std::vector<int>(size_x, NULL));
    }
    for(int i = 0; i < cloud_sub->size(); ++i){
        pcl::PointXYZI &point = cloud_sub->points[i];
        unsigned long target_x = floor((point.x - x_min) / grid_size_);
        unsigned long target_y = floor((point.y - y_min) / grid_size_);
        if (target_x > size_x || target_y > size_y) {
            std::cout << target_x << " " << target_y << std::endl;
        }
        map_sub[target_y][target_x] = 1;
    }

    pcl::PointCloud<pcl::PointXYZI> cloud_new; // (new pcl::PointCloud<pcl::PointXYZI>);
    std::vector<std::vector<int> > map_all;
    for (int i = 0; i < size_y; ++i) {
        map_all.push_back(std::vector<int>(size_x, NULL));
    }
    for(int i = 0; i < cloud_all->size(); ++i){
        pcl::PointXYZI &point = cloud_all->points[i];
        unsigned long target_x = floor((point.x - x_min) / grid_size_);
        unsigned long target_y = floor((point.y - y_min) / grid_size_);
        if (target_x > size_x || target_y > size_y) {
            std::cout << target_x << " " << target_y << std::endl;
        }
        // map_sub[target_y][target_x] = 1;
        if (map_sub[target_y][target_x] == 1) {
            cloud_new.push_back(cloud_all->points[i]);
            // map_sub[target_y][target_x] = 1;
        } else {
            std::cout << "Fat ";
        }
    }

    pcl::io::savePCDFileBinary ("cloud_new.pcd", cloud_new);

    return 0;
}
