#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "hashtable.h"


using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 3) {
		cerr << "Error format: a.out Parameterfile Wordfile" << endl;
		exit(0);
	}

    int bucket_size = 0;
    int Constant = 0;
    string num1;
    string num2;
    string input_word;

    vector<string> wordlist;
    int    total_word = 0;

    std::ifstream inputnum(argv[1]);
    std::ifstream inputfile(argv[2]);
	

    //get our parameter
    getline(inputnum, num1);
    getline(inputnum, num2);
    bucket_size = stoi(num1);
    Constant = stoi(num2);

    //get our words
    while(getline(inputfile,input_word)){
        total_word += 1;
        wordlist.resize(total_word);
        wordlist[total_word - 1] = input_word;
    }



    //now we know how much words we have
    //we want to turn words into int
    vector<int> numlist;
    numlist.resize(total_word);

    int max_bucket = -1;
    int max_bucket_id = -1;
    //now we make a bucket_tracker to track the bucket
    vector<int>bucket_tracker;
    bucket_tracker.resize(bucket_size);
    //and time to track each bucket for its item number
    for (int i = 0; i<wordlist.size();i++){
        numlist[i] = convert1(wordlist[i],bucket_size,Constant,0);
        bucket_tracker[numlist[i]] += 1;
        if(bucket_tracker[numlist[i]]>max_bucket){
            max_bucket = bucket_tracker[numlist[i]];
            max_bucket_id = numlist[i];
        }
    }

    vector<int> bucket_result;
    bucket_result.resize(21);
    //after we clean the duplicatest, we output a result page.
    for (int i = 0; i < bucket_tracker.size(); i++){
        bucket_result[bucket_tracker[i]] += 1;
    }

    //we want the bucket for the most collision
    int max = 9999;
    int maxbucket = 9999;
    for (int i = 0; i < bucket_result.size(); i++){
        if(bucket_result[i]>0){
            max = i-1;
        }
    }    
    //if there is no collision, we just say zero
    if (max == -1){
        max = 0;
    }
    
    cout << "Size of input: " << total_word << endl;
    cout << "Number of words in table: " << total_word << endl;
    cout << "Primary array size: " << bucket_size << endl;

    cout << "Maximum number of collisions in a hashbucket: " << max << endl;

    cout << "The number of hashbuckets b with x elements:" << endl;
    for (int i = 0; i < 21;i++){
        cout << "x=" << i << " : b=" << bucket_result[i] << endl;
    }

    auto dict = new Hash();
    dict->createmap(bucket_size);

   for (int i = 0; i < bucket_tracker.size(); i++){
       dict->resizelement(i, bucket_tracker[i]);
    }

    for (int i = 0; i < wordlist.size();i++){
        dict->insertword(numlist[i], wordlist[i]);
    }


    //Now find the most popular string
    cout << "Keys in most populated bucket:";
    vector<string> maxcollision = dict->findword(max_bucket_id);
    for (int i = 0; i < maxcollision.size();i++){
        cout << " " << maxcollision[i];
    }
    cout << endl;


    //see if we have query words
    string query_wordlist_name;
    string query_word;
    vector<string> query_wordlist;
    if(argc==4){
        std::ifstream query_wordlist_name(argv[3]);
        while(getline(query_wordlist_name,query_word)){
            query_wordlist.push_back(query_word); 
        }
        cout << endl;
        cout << "Queries" << endl;
        vector<int> position;
        for(int i=0;i<query_wordlist.size();i++){
            position = dict->queryword(query_wordlist[i],bucket_size,Constant);
            if(position[0] == -999 &&  position[1] == -999){
                cout << "Key \"" << query_wordlist[i] << "\" does not exist." << endl;
            }else{
                cout << "Key \"" << query_wordlist[i] << "\" exists at (" << position[0] << ", " << position[1] << ")." << endl;
            }
        }
    }
    

    


    return 0;
}

















