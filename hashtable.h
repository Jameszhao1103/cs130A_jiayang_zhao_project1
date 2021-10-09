#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib> 
#include <vector>

int convert1(std::string s, int p, int c, int index){
    if (index == s.length()-1){
        return int(s[index])%p;
    }else{
        int temp = int(s[index]);
        int new_index = index + 1;
        return (temp + c * (convert1(s,p,c,new_index)))%p;
    }
}

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
        hashmap[index].num_item = size;
        for (int i = 0; i < hashmap[index].element.size();i++){
            hashmap[index].element.at(i) = "";
        }
    }

    int insertword(int bucket_num, std::string word){
        for (int i = 0; i < hashmap[bucket_num].element.size();i++){
            if(hashmap[bucket_num].element.at(i).length()==0){
                hashmap[bucket_num].element.at(i) = word;
                return 0;
            }else if(hashmap[bucket_num].element.at(i) == word){
                //then we find a duplicate
                return 1;
            }
        }
    }

    int sizeofbucket(int bucket_num){
        return hashmap[bucket_num].num_item;
    }

    void changebucket(int bucket_num, int num){
        hashmap[bucket_num].num_item - num;
    }
    
    std::vector<std::string> findword(int bucket_num){
        return hashmap[bucket_num].element;
    }

    std::vector<int> queryword(std::string query_word, int p, int c){
        //get hash number of this string
        std::vector<int> not_found = {-999, -999};
        int stringidx = convert1(query_word, p, c, 0);
        if(hashmap[stringidx].num_item==0){
            return not_found;
        }else{
            for (int i = 0; i < hashmap[stringidx].num_item;i++){
                if(hashmap[stringidx].element[i]==query_word){
                    return std::vector<int>{stringidx, i};
                }
            }
            return not_found;
        }
    }


};









#endif
