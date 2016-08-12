/*
@author Jonathan Vasquez
@date 4/19/16
@Project1
*/
#include "Clustering.h"
#include <cstdlib>
#include <iostream>
#include <fstream>


using namespace std;
/*
Takes in file on console sort of like in python. It is more convenient for user.
BONUS POINTS will be greatly appreciated
*/
Clustering::Clustering(char fp[])
{
    CHECK=true;
    fstream file(fp);//file from terminal/console
    file>>num_of_points>>num_of_clusters;//reads points and data in this order
    int index,i;

    cluster= new double*[num_of_points];//creates cluster dynamic array
    
    for(i=0;i<num_of_points;i++)
    {
        cluster[i]=new double[num_of_clusters+1];//counter
    }
    points = new double *[num_of_points];//updates points
    for(i=0;i<num_of_points;i++)
    {
        points[i]=new double[2];
        //Read the data set
        file>>points[i][0]>>points[i][1];//input scheme
    }

    int arrIndex[num_of_clusters];
    fill_n(arrIndex,num_of_clusters,0);

    srand(time(0));//better than ran() because it updates regularly based on time()
    centroids=new double*[num_of_clusters];//creates centroids
    for(i=0;i<num_of_clusters;i++)
    {
        centroids[i]=new double[2];

        //Picks random index for centroids
        index=(rand()%num_of_points);

        //makes sure no centroid is picked twice
        while(arrIndex[(index%num_of_clusters)]!=0)
        index++;
        arrIndex[(index%num_of_clusters)]++;

        //x coordinate
        centroids[i][0]=points[index][0];

        //y coordinate
        centroids[i][1]=points[index][1];
    }
    file.close();//closes file safely
}
////////////////////////////////////////
/*
Destructor
*/
Clustering::~Clustering()
{
    int i=0;
    for(i=0;i<=num_of_clusters;i++)
    delete [] cluster[i];
    delete []cluster;

    for(i=0;i<2;i++)
    delete [] points[i];
    delete [] points;


    for(i=0;i<2;i++)
    delete [] centroids[i];
    delete [] centroids;

}
/*
Finds the Euclidean Distance
*/
double Clustering::euclidean_distance(double x1, double y1, double x2, double y2)
{
    double z= x1>x2?x1-x2:x2-x1;
    z+= (y1>y2?y1-y2:y2-y1);//ternary operator takes less space than bunch of conditions
    //Returns the distance between the two points
    return z;
}

void Clustering::perform_cluster()
{
    int steps=1;
    int old;
    bool newCheck,check1;
    while(CHECK)
    {
        check1=true;
        newCheck=true;

        for(int i=0;i<num_of_points;i++)
        {
            old=int(cluster[i][num_of_clusters]);

            for(int j=0;j<num_of_clusters;j++)
            {
                //Write the distance data for each centroid
                cluster[i][j]=euclidean_distance(points[i][0],points[i][1],centroids[j][0],centroids[j][1]);
            }
            //Set the respective centroid id
            minimum_of_distance(cluster[i]);

            // Mark if the centroid has changed
            if(old==int(cluster[i][num_of_clusters]))
            newCheck=true;
            else
            newCheck=false;

            check1 = check1 & newCheck;
        }

        //Print step wise
        print(steps);
        getchar();
        //Get the new centroids
        set_centroids();

        steps++;

        //loop till there is no change in centroids
        CHECK = !check1;
    }
    for(int i=0;i<num_of_clusters;i++)
    {
        cout<<"\nCluster "<<i+1<<" :"<<endl;
        for(int j=0;j<num_of_points;j++)
        {
            if(cluster[j][num_of_clusters]==i)
            cout<<points[j][0]<<","<<points[j][1]<<endl;
        }
        cout<<"\n*******************************************"<<endl;
    }
}

void Clustering::minimum_of_distance(double temp[])
{
    double min=temp[0];
    temp[num_of_clusters]=0;
    for(int j=1;j<num_of_clusters;j++)
    {
        if(min>temp[j])
        {
            //Set the minimum value
            min=temp[j];

            //Set the respective centroid id
            temp[num_of_clusters]=j;
        }
    }
}
 void Clustering::print(int step)
 {
     int i,j;
     cout<<"Step Number: "<<step<<endl;
     for(i=0;i<num_of_points;i++)
     {
         cout<<"Point "<<i<<":  ";
         for(j=0;j<num_of_clusters;j++)
         {
             cout<<cluster[i][j]<<"   ";
         }
         cout<<cluster[i][j]+1<<" ";
         cout<<endl;
     }

    cout<<"The centroids are:"<<endl;
    for(i=0;i<num_of_clusters;i++)
    cout<<centroids[i][0]<<"   "<<centroids[i][1]<<endl;
    cout<<"*****************************************\n"<<endl;
 }

void Clustering::set_centroids()
{
    int *total_points=new int[num_of_clusters];
    int i,j;

    //Fill total_points with 0
    fill_n(total_points,num_of_clusters,0);//fill_n is used as an output scheme sort of like a complex cout<<

    for(i=0;i<num_of_points;i++)
    {
        //Count the number of points in a cluster
        total_points[int(cluster[i][num_of_clusters])]++;
    }

    for(i=0;i<num_of_clusters;i++)
    {
        double total_x=0;
        double total_y=0;
        for(j=0;j<num_of_points;j++)
        {
            //for the centroid id == cluster id
            if(cluster[j][num_of_clusters]==i)
            {
                //Total x co-ordinate
                total_x+=points[j][0];

                //Total y co-ordinate
                total_y+=points[j][1];
            }
        }

        //Finding the mean on x and y co-ordinate
        centroids[i][0]=total_x/total_points[i];
        centroids[i][1]=total_y/total_points[i];
    }

    delete []total_points;
}