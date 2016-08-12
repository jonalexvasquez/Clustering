/*
@author Jonathan Vasquez
@date 4/29/16
@Project1
*/
#ifndef CLUSTERING_H
#define CLUSTERING_H

class Clustering
{
    public:
        Clustering(char[]); //Also initializes the the centroids to some random points from the given data set
        ~Clustering();//destructor 
        void perform_cluster(); //To start clustering the data set
        void minimum_of_distance(double[]); // To find the minimum of the Euclidean distance
        void print(int); //Print the clusters step by step
        void set_centroids(); // To set the new centroids the according the average of the points in the cluster

    private:
    int num_of_clusters;//clusters
    int num_of_points;//points
    bool CHECK;//acts like a flag
    double **points; //To store the points in co-ordinates
    double **centroids; //To store the centroids of each cluster
    double **cluster; //To store the cluster data along with the distance
    double euclidean_distance(double x1,double y1, double x2, double y2); //To calculate the euclidean distance
};

#endif 
