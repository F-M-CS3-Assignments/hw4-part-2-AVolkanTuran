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


//Helper function to find the biggest list
vector<int> biggest_divisible_conglomerate_finder(vector<int> input){
    vector<vector<int> > bdc(input.size()+1);
    //Base case where the input size is less than or equal to 1
    bdc.at(bdc.size()-1) = {};

    vector<vector<int> > candidates;
    for(int i = bdc.size()-2; i>=0; i--){
        for(int n = i; n<input.size(); n++){
            vector<int> left = {input.at(n)};

            //Finds the position of the next number divisible the current element we are checking at i
            int j = n+1;
            while(j<input.size() && input.at(j)%input.at(n)!=0){
                j++;
            }
            vector<int> right = bdc.at(j);

            vector<int> cand(left);
            for(int k = 0; k<right.size(); k++){
                if(right.at(k)%cand.at(0)==0){
                    cand.push_back(right.at(k));
                }
            }
            candidates.push_back(cand);
        }

        unsigned int maxSizeIndex = 0;
        for(unsigned int l = 1; l<candidates.size(); l++){
            if(candidates.at(l).size() > candidates.at(maxSizeIndex).size()){
                maxSizeIndex = l;
            }
        }

        bdc.at(i) = candidates.at(maxSizeIndex);
    }
    
    return bdc.at(0);
}

vector<int> biggest_divisible_conglomerate(vector<int> input){
    //Sorts the input because it makes finding the bdc much easier
    selection_sort(input);
    //Finds the bdc
    return biggest_divisible_conglomerate_finder(input);
}