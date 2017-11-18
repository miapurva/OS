#include <iostream>
#include "refinedsjf.h"

using namespace std;

refinedsjf::refinedsjf() {

}

void refinedsjf::swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void refinedsjf::calculateEverything(refinedsjf *arr, int n) {

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (arr[i].at > arr[j].at) {
                swap(&arr[i].at , &arr[j].at);
                swap(&arr[i].bt , &arr[j].bt);
            }
        }
    }

    //calculate ct tat and wt

    for (int i = 0; i < n; ++i) {
        int minimum = 1000;
        int position = i;

        if (i==0) {                         //for the first completion time
            arr[i].ct = arr[i].bt + arr[i].at;
        } else {
            for (int j = i; j < n; ++j) {
                if ((arr[j].at <= arr[i-1].ct) && (arr[i].bt<minimum)) {
                    minimum = arr[i].bt;
                    position = j;
                }
            }

            int temp1 = arr[i].at;
            arr[i].at = arr[position].at;
            arr[position].at = temp1;

            int temp2 = arr[i].bt;
            arr[i].bt = arr[position].bt;
            arr[position].bt = temp2;

            if (arr[i].at > arr[i-1].ct) {
                arr[i].ct = arr[i].at + arr[i].bt;
            } else {
                arr[i].ct = arr[i-1].ct + arr[i].bt;
            }
        }

        arr[i].findtat();
        arr[i].findwt();
    }
}

void refinedsjf::display(refinedsjf arr[], int n) {

    for (int i = 0; i < n; ++i) {
        cout << i << "\t" << arr[i].at << "\t" << arr[i].bt << "\t" << arr[i].ct << "\t" << arr[i].tat << "\t" << arr[i].wt<<endl;
    }

}
