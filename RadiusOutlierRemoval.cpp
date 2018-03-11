#include <iostream>    
#include <pcl/io/pcd_io.h>    
#include <pcl/point_types.h>    
#include <pcl/io/io.h>    
#include <pcl/visualization/cloud_viewer.h>    
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/conditional_removal.h> 
  
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
    // 填入点云数据    
    pcl::io::loadPCDFile("test2-less.pcd", *cloud);  
	std::cerr << "Before Filter:" << cloud->points.size()<<"Points" << endl;
    // 创建滤波器对象    
    pcl::RadiusOutlierRemoval<pcl::PointXYZ> outrem;  //创建滤波器
    
    outrem.setInputCloud(cloud);    //设置输入点云
    outrem.setRadiusSearch(20);     //设置半径为0.8的范围内找临近点
    outrem.setMinNeighborsInRadius (100); //设置查询点的邻域点集数小于2的删除
    // apply filter
    outrem.filter (*cloud_filtered);     //执行条件滤波   在半径为0.8 在此半径内必须要有两个邻居点，此点才会保存
	std::cerr << "Before Filter:" << cloud_filtered->points.size() <<"Points" << endl;
    pcl::visualization::CloudViewer viewer("Cloud Viewer");  
    //showCloud函数是同步的，在此处等待直到渲染显示为止    
    viewer.showCloud(cloud_filtered);  
    //该注册函数在可视化时只调用一次    
    viewer.runOnVisualizationThreadOnce(viewerOneOff);  
    //该注册函数在渲染输出时每次都调用    
    viewer.runOnVisualizationThread(viewerPsycho);  
    while (!viewer.wasStopped())  
    {  
        //在此处可以添加其他处理    
        user_data++;  
    }  
  
  
  
    return (0);  
}  
