#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>

int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  // �����ȡ����
  pcl::PCDReader reader;
  // ��ȡ�����ļ�
  reader.read<pcl::PointXYZ> ("test7.pcd", *cloud);

  std::cerr << "Cloud before filtering: " << std::endl;
  std::cerr << *cloud << std::endl;

  // �����˲�������ÿ����������ٽ���ĸ�������Ϊ50 ��������׼��ı�������Ϊ1  ����ζ�����һ
   //����ľ��볬����ƽ������һ����׼�����ϣ���õ㱻���Ϊ��Ⱥ�㣬�������Ƴ����洢����
  pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;   //�����˲�������
  sor.setInputCloud (cloud);                           //���ô��˲��ĵ���
  sor.setMeanK (50);                               //�����ڽ���ͳ��ʱ���ǲ�ѯ���ٽ�����
  sor.setStddevMulThresh (1.0);                      //�����ж��Ƿ�Ϊ��Ⱥ��ķ�ֵ
  sor.filter (*cloud_filtered);                    //�洢

  std::cerr << "Cloud after filtering: " << std::endl;
  std::cerr << *cloud_filtered << std::endl;

  pcl::PCDWriter writer;
  writer.write<pcl::PointXYZ> ("test7_inliers.pcd", *cloud_filtered, false);

  sor.setNegative (true);
  sor.filter (*cloud_filtered);
  writer.write<pcl::PointXYZ> ("test7_outliers.pcd", *cloud_filtered, false);

  return (0);
}