#ifndef OSLAB_REFINEDSJF_H
#define OSLAB_REFINEDSJF_H

class refinedsjf {
public:

    refinedsjf();

    int at,bt,ct,tat,wt;

    void findwt() {
        wt = tat - bt;
    }

    void findtat() {
        tat = ct - at;
    };

    void swap(int *a, int *b);

    void calculateEverything(refinedsjf obj[], int n);

    void display(refinedsjf obj[], int n);

};
#endif //OSLAB_REFINEDSJF_H