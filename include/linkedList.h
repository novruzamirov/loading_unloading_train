#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        char id;
        int weight;
        materialNode* next;
};

class wagonNode{
    public:
        int wagonId;
        materialNode* material;
        wagonNode* next;
};

class Train{  

    wagonNode* head;
    
    public:
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
        void orderedWagon(); // making ordered wagon from A to B
        void createNewWagon(); //creating new wagon if needed
        void findingLastWagonContainingMaterial(char); // finding last wagon that has exact material
        void deletingMaterialsWithoutWeight(); // finding for materials whoch has 0 weight and deleting it.
        void deletingWagonWithoutMaterial();
};

#endif
