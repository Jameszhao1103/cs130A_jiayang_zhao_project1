#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib> 
#include <vector>

class Hash{
    public:
    struct item{
        int num_item;
        std::vector<std::string> element;

        

        void initial(int num_object){
            element.resize(num_object);
            for (int i = 0; i < element.size();i++){
                element.at(i) = "";
            }
        }
    };

    std::vector<item> hashmap;

    void createmap(int size){
        hashmap.resize(size);
    }

    void resizelement(int index, int size){
        hashmap[index].element.resize(size);
        for (int i = 0; i < hashmap[index].element.size();i++){
            hashmap[index].element.at(i) = "";
        }
    }


    void insertword(int bucket_num, std::string word){
        for (int i = 0; i < hashmap[bucket_num].element.size();i++){
            if(hashmap[bucket_num].element.at(i).length()==0){
                hashmap[bucket_num].element.at(i) = word;
                break;
            }
        }
    }
    
    std::vector<std::string> findword(int bucket_num){
        return hashmap[bucket_num].element;
    }
};

int convert1(std::string s, int p, int c, int index){
    if (index == s.length()-1){
        return int(s[index])%p;
    }else{
        int temp = int(s[index]);
        int new_index = index + 1;
        return (temp + c * (convert1(s,p,c,new_index)))%p;
    }
}








#endif
