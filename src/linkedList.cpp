#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

int i = 1;
int wagonIsEmpty = 1;
int tWeight;
wagonNode* lastWagonContainingMaterial = NULL;

void Train::create(){
    head = NULL;
}; 

void Train::addMaterial(char material, int weight){

    tWeight = weight;

    if(head == NULL){
        wagonNode* new_wagon_node = new wagonNode();
        i = 1;
        new_wagon_node->wagonId = i;
        i++;
        new_wagon_node->next = NULL;
        new_wagon_node->material = NULL;
        head = new_wagon_node;
    }

    if(head->material == NULL){
        wagonIsEmpty = 1;
    }
        
    wagonNode* wagonTemp = head;
    materialNode* temp = wagonTemp->material;


    while(wagonTemp != NULL){

        while(temp != NULL){ 

            if(temp->id == material){

                if(temp->weight + weight > 2000){

                    weight = (weight - (2000 - temp->weight));
                    temp->weight = 2000;
                    if(wagonTemp->next != NULL){
                        wagonTemp = wagonTemp->next;
                        temp = wagonTemp->material;
                    }
                    else{
                        createNewWagon();
                        wagonTemp = wagonTemp->next;
                        temp = wagonTemp->material;
                    }
                }

                else{
                    temp->weight += weight;
                    return;
                }

            }

            else if(temp->next != NULL){
                temp = temp->next;
            }

            else{
                materialNode* new_material_node = new materialNode();
                new_material_node->id = material;
                temp->next = new_material_node;
            }

        }

        materialNode* new_material_node = new materialNode();
        new_material_node->id = material;
        wagonTemp->material = new_material_node;
        temp = wagonTemp->material;

    }

    if(temp->id == material){
        temp->weight += weight;
        return;
    }
}; 

void Train::createNewWagon(){
    wagonNode* new_wagon_node = new wagonNode();
    new_wagon_node->wagonId = i;
    i++;
    new_wagon_node->next = NULL;
    new_wagon_node->material = NULL;
    
    int tempI = 1;
    wagonNode* temp = head;
    while(tempI != i-2){
        temp = temp->next;
        tempI++;
    }

    temp->next = new_wagon_node;
}


void Train::deleteFromWagon(char material, int weight){
    //FILL THIS FUNCTION ACCORDINGLY

    findingLastWagonContainingMaterial(material);

    materialNode* lastMaterial = lastWagonContainingMaterial->material;
    while(lastMaterial->id != material){
        lastMaterial = lastMaterial->next;
    }

    // cout << lastMaterial->id << " " << lastMaterial->weight << endl;

    if(lastMaterial->weight >= weight){
        lastMaterial->weight -= weight;
    }

    else{
    
        while(weight != 0){
            weight -= lastMaterial->weight;
            lastMaterial->weight = 0;

            wagonNode* wagonForDeleting = head;

            while(wagonForDeleting->next != lastWagonContainingMaterial){
                wagonForDeleting = wagonForDeleting->next;
            }

            lastMaterial = wagonForDeleting->material;

            while(lastMaterial->id != material){
                lastMaterial = lastMaterial->next;
            }

            if(weight <= lastMaterial->weight){
                lastMaterial->weight -= weight;
                break;
            }
            else{
                weight -= lastMaterial->weight;
                lastMaterial->weight = 0;
                lastWagonContainingMaterial = wagonForDeleting;
                continue;
            }

        }

    }

    this->deletingMaterialsWithoutWeight();
    this->deletingWagonWithoutMaterial();
};  

void Train::deletingWagonWithoutMaterial(){

    wagonNode* temp2 = head;

    while(temp2 != NULL){

        wagonNode* temp = temp2;
        
        if(temp->material == NULL){
            if(temp == head){
                head = NULL;
                i--;
                delete temp;
                return;
            }
            else{
                wagonNode* test = head;
                while(test->next != temp){
                    test = test->next;
                }
                test->next = NULL;
                i--;
                delete temp;
                return;
            }
        }

        temp2 = temp2->next;
    }
}

void Train::deletingMaterialsWithoutWeight(){
    wagonNode* tempWagon = head;
    // materialNode* tempMaterial = head->material;

    while(tempWagon != NULL){

        materialNode* tempMaterial = tempWagon->material;
        while(tempMaterial != NULL){

            if(tempMaterial->weight == 0){

                if(tempWagon->material == tempMaterial){
                    tempWagon->material = tempMaterial->next;
                    delete tempMaterial;
                    break;
                }
                else if(tempMaterial->next == NULL){
                    materialNode* temp = tempWagon->material;
                    while(temp->next != tempMaterial){
                        temp = temp->next;
                    }
                    temp->next = NULL;
                    delete tempMaterial;
                    break;
                }
                else{
                    materialNode* temp = tempWagon->material;
                    while(temp->next != tempMaterial){
                        temp = temp->next;
                    }
                    temp->next = tempMaterial->next;
                    delete tempMaterial;
                    break;
                }

            }

            else{
                tempMaterial = tempMaterial->next;
            }

        }
        tempWagon = tempWagon->next;
    }

}

void Train::findingLastWagonContainingMaterial(char material){
    wagonNode* tempWagon = head;
    materialNode* tempMaterial = head->material;
    int k = 0;

    lastWagonContainingMaterial = head;


    while(tempWagon->next != NULL){

        if(tempWagon == head && k == 0){
            tempMaterial = tempWagon->material;
            k++;
        }
        else if(tempWagon == head && k == 1){
            tempMaterial = (tempWagon->next)->material;
            k++;
        }
        else{
            tempWagon = tempWagon->next;
            tempMaterial = (tempWagon->next)->material;
        }

        if(tempWagon == NULL){
            lastWagonContainingMaterial = tempWagon;
            return;
        }

        while(tempMaterial != NULL){

            if(tempMaterial->id == material){

                if(tempMaterial->weight < 2000){
                    lastWagonContainingMaterial = tempWagon->next;
                    return;
                }
                else if(tempWagon->next->next == NULL){
                    lastWagonContainingMaterial = tempWagon->next;
                    return;
                }
                else{
                    break;
                }

            }
            else if(tempMaterial->next == NULL){
                lastWagonContainingMaterial = tempWagon;
                return;
            }

            tempMaterial = tempMaterial->next;
        }



    }

}

void Train::orderedWagon(){

    wagonNode* tempWag = head;

    while(tempWag != NULL){
        materialNode *head2 = tempWag->material;
        materialNode *current = head2;
        materialNode *index = NULL;
        char tempMaterial;
        int tempWeight;

        while(current != NULL) {  
     
            index = current->next;  
                  
            while(index != NULL) {  

                if(current->id > index->id) {  
                    tempMaterial = current->id;  
                    current->id = index->id;  
                    index->id = tempMaterial; 

                    tempWeight = current->weight;
                    current->weight = index->weight;
                    index->weight = tempWeight; 
                }  
                index = index->next;  
            }  
            current = current->next;  
        }     
        tempWag = tempWag->next;
    }
}


void Train::printWagon(){
    this->orderedWagon();
    // this->deletingMaterialsWithoutWeight();
    // this->deletingWagonWithoutMaterial();
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 