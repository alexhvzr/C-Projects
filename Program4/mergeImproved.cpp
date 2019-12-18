//
// Created by Alex Hayden van Zuiden-Rylander on 2019-02-22.
//
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

template<class Comparable>
void merge(vector<Comparable> & src, vector<Comparable> & dstn, int nItems){
    int f1,f2,l1,l2;
    int currentIndex = 0;
    for(int i = 0; i < src.size(); i += nItems*2){
        f1= i;
        l1 = i+nItems-1;
        f2 = l1+1;
        l2 = f2+nItems-1;
        for( ; f1 <= l1 && f2 <= l2; currentIndex++){

            dstn[currentIndex] = (src[f1] < src[f2]) ? src[f1++] : src[f2++];
        }
        for( ; f1 <= l1; ++f1, ++currentIndex){
            dstn[currentIndex] = src[f1];
        }
        for( ; f2 <= l2; ++f2, ++currentIndex){
            dstn[currentIndex] = src[f2];
        }
//        for(int j =0; j < dstn.size(); j++){ // Uncomment to test iteration sorting debug.
//            cout<< dstn[j] << " ";
//        } cout << endl;
    }
};



template<class Comparable>
void mergeImproved(vector<Comparable> &a) {        // the driver

    int size = a.size();
    vector<Comparable> b(size); //temp array to swap between

    //find # and divide-and-conquer layers. Also equal to log(size).
    int iterations = 1;
    for (int items = 2; items < size; items *= 2, ++iterations); // Calculate iterations.
    int merge_itr = 0;

    //for each layer perform merge sort.
    for (int items = 0; merge_itr < iterations; ++merge_itr) {

        items = int(pow(double(2), double(merge_itr))); // Computed number of items to compare.

        if (merge_itr%2 == 0){           // Merge from vector a to b.
            merge(a,b,items);
        } else if (merge_itr%2 == 1){    // Merge from vector b to a.
            merge(b,a,items);
        }

    }
     if(merge_itr % 2 == 1){
        for(int i = 0; i < size; i++){
            a[i] = b[i];
        }
    }


};