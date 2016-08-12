/*
@author Jonathan Vasquez
@date 4/29/16
@Project1
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
A HUGE BONUS is that the program is dynamic because it allows any number of points and clusters.So that it is not limited to 4 points and two clusters.
I did bonus work for the input of the file. To input a text file it has to be in the same folder and has to be typed as following: 
"./main text.txt"
where text.txt is the input file name and extension
The input file must be in this order:
1.)Number of points
2.)Number of clusters
3.)The data points
without literally the 1.) 2.) 3.)
Another BONUS that I did was doing the math "step by step". The screen is going to output the distances every time you press "Enter"
testing file is reduced a lot in size 
*/
#include <iostream>
#include <stdlib.h>
#include "Clustering.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc==1)//checks to see if input is on terminal and that it's not blank
    {
        cout<<"ERROR:to use the program format your input as: ./main text.txt"<<endl;
        return 0;
    }

    Clustering data(argv[1]);//argv[1] is used to input the input file(learned this in python)
    //Initializes the clustering of the data set
    data.perform_cluster();

    return 0;
}