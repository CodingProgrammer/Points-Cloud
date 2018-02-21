#include <iostream>    
#include <pcl/io/pcd_io.h>    
#include <pcl/point_types.h>    
#include <pcl/filters/voxel_grid.h>    
#include <pcl/io/io.h>    
#include <pcl/visualization/cloud_viewer.h>    
  
  
int user_data;  
void  
viewerOneOff(pcl::visualization::PCLVisualizer& viewer)  
{  
    viewer.setBackgroundColor(1.0, 0.5, 1.0);  
    pcl::PointXYZ o;  
    o.x = 1.0;  
    o.y = 0;  
    o.z = 0;  
    //viewer.addSphere(o, 0.25, "sphere", 0);  
    std::cout << "i only run once" << std::endl;  
  
}  
  
void  
viewerPsycho(pcl::visualization::PCLVisualizer& viewer)  
{  
    static unsigned count = 0;  
    std::stringstream ss;  
    ss << "Once per viewer loop: " << count++;  
    viewer.removeShape("text", 0);  
    viewer.addText(ss.str(), 200, 300, "text", 0);  
    //FIXME: possible race condition here:    
    user_data++;  
}  
int  
main(int argc, char** argv)  
{  
  
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);  
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);  
    // �����������    
    pcl::io::loadPCDFile("rabbit.pcd", *cloud);  
  
    // �����˲�������    
    pcl::VoxelGrid<pcl::PointXYZ> sor;  
    sor.setInputCloud(cloud);  
    sor.setLeafSize(0.01f, 0.01f, 0.01f);  
    sor.filter(*cloud_filtered);  
    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height  
        << " data points (" << pcl::getFieldsList(*cloud_filtered) << ").";  
  
  
    pcl::visualization::CloudViewer viewer("Cloud Viewer");  
    //showCloud������ͬ���ģ��ڴ˴��ȴ�ֱ����Ⱦ��ʾΪֹ    
    viewer.showCloud(cloud_filtered);  
    //��ע�ắ���ڿ��ӻ�ʱֻ����һ��    
    viewer.runOnVisualizationThreadOnce(viewerOneOff);  
    //��ע�ắ������Ⱦ���ʱÿ�ζ�����    
    viewer.runOnVisualizationThread(viewerPsycho);  
    while (!viewer.wasStopped())  
    {  
        //�ڴ˴����������������    
        user_data++;  
    }  
  
  
  
    return (0);  
}  