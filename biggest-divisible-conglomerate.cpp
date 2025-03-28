//Author: Ahmet Volkan Turan

#include "bdc.h"
#include <iostream>

using namespace std;

string vec_to_string(vector<int> v){
    if(v.size()==0){
        return "[]";
    }
    
    string output = "[";

    for(unsigned int i = 0; i<v.size()-1; i++){
        output += to_string(v.at(i)) + ", ";
    }
    output += to_string(v.back()) + "]";

    return output;
}

//Simple selection sort to make it easier to check the divisibility requirement and give the answer in an nice sorted manner
void selection_sort(vector<int>& input){
    if(input.size()==0){
        return;
    }
    for(int i = 0; i<input.size()-1; i++){
        int minIndex = i;
        for(int j = i+1; j<input.size(); j++){
            if(input.at(j)<input.at(minIndex)){
                minIndex = j;
            }
        }
        int temp = input.at(i);
        input.at(i) = input.at(minIndex);
        input.at(minIndex) = temp;
    }
}

vector<int> biggest_divisible_conglomerate(vector<int> input){
    //Sorts the input so that the code can work
    selection_sort(input);
    
    //Creates a vector of vectors to keep track of the possible conglomerates
    vector<vector<int> > answers(input.size());

    //Itemizes the input into their own vectors so they can build the conglomerates starting that value
    for(size_t i = 0; i<answers.size(); i++){
        answers.at(i) = {input.at(i)};
    }

    //For each value in the input it creates a conglomerate, and adds the previously calculated conglomerate
    //If the value we are checking is divisible by a previously calculated conglomerate
    //Because the list is sorted, anything that is divisible by that element is divisible by the others too 
    for(size_t i = 0; i<input.size(); i++){
        for(size_t j = i+1; j<input.size(); j++){
            if(input.at(j)%input.at(i)==0 && answers.at(i).size()>=answers.at(j).size()){
                answers.at(j) = {input.at(j)};
                for(size_t k = 0; k<answers.at(i).size(); k++){
                    answers.at(j).push_back(answers.at(i).at(k));
                }
            }
        }
    }

    //Finds the index of the biggest divisible conglomerate and returns that conglomerate
    size_t maxidx = 0;
    for(size_t i = 1; i<answers.size(); i++){
        if(answers.at(i).size()>answers.at(maxidx).size()){
            maxidx = i;
        }
    }
    return answers.at(maxidx);
}