#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib> 
using namespace std;

string generate_random_text(unordered_map<string,vector<char>> &m,int k) {
    string result_text = "",initial_seed="";

    int max_size = 0;
    
    for(auto pair:m){ 
        if(pair.second.size() > max_size){
            max_size = pair.second.size();
            initial_seed = pair.first;
        }
    }

    result_text += initial_seed;

    while(result_text.length() < 2009){
        string last_k_chars = result_text.substr(result_text.length() - k, k);

        if (m.find(last_k_chars) == m.end()) {
            break;
        }

        char next_char = m[last_k_chars][rand() % m[last_k_chars].size()];
        
        result_text += next_char;
    }


    return result_text;
}

string k_0_random_text(vector<char> &all_chars) {
    string result_text = "";
    int size = all_chars.size();
    for (int i = 0; i < 2009; i++) {
        result_text += all_chars[rand() % size];
    }
    return result_text;
}

int main(){

    string fileName;
    while(1){
        int k;
        cout << "Enter order: ";
        cin>>k;
        
        if (k < 0) {
            cout << "Order must be a non-negative integer." << endl;
            continue;
        }

        cout<<endl;

        cout << "Enter the file name (or 'exit' to quit): ";
        cin >> fileName;
        if (fileName == "exit") {
            break;
        }

        FILE *file = fopen(fileName.c_str(), "r");
        if (file == NULL) {
            cout << "Error opening file: " << fileName << endl;
            continue;
        }

        char ch;
        unordered_map<string,vector<char>> m;
        string key="";
        
        
        for(int i=0;i<k;i++){    
            ch = fgetc(file);
            if(ch == EOF){  
                cout << "File is too small for the given order." << endl;
                fclose(file);
                return 0;
            }
            key+=ch;
        }
        
        string result="";

        if(k==0){   
            vector<char> all_chars;   
            while ((ch = fgetc(file)) != EOF) {
                all_chars.push_back(ch);
            }     
            result=k_0_random_text(all_chars); 

        }else{
            while ((ch = fgetc(file))!= EOF) {
                m[key].push_back(ch);
                key = key.substr(1) + ch; 
            }
            cout << endl;
    
            result=generate_random_text(m,k);
        }

        
        cout << "Generated text: " << result << endl;
        
        fclose(file);
    }

    return 0;
}
