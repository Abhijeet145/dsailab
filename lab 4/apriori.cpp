#include<bits/stdc++.h>
using namespace std;
//global data
int total;
//transaction ID and transactions(items)
    vector<pair<int,vector<string>>> transactions;

vector<pair<string,int>> frequentItemSets(vector<pair<int,vector<string>>> &transactions){
    map<string,int> freq;
    vector<pair<string,int>> items;
    for(auto sell : transactions){
        for(auto item:sell.second){
            freq[item]++;
        }
    }
    cout << "Item\t Frequency\t\tSupport\n";
    for(auto item:freq){
        items.push_back(item);
        cout <<item.first<<"\t\t"<<item.second<<"\t\t"<<(item.second*1.0)/total*100<<"%\n";
    }
    return items;
}


vector<pair<string,int>> processBinaryData(vector<vector<string>> &binaryData){
    map<string,int> freq;
    vector<pair<string,int>> items;
    int id = 1;
    for(int i = 1;i<binaryData.size();i++){
        vector<string> item;
        for(int j = 0;j<binaryData[i].size();j++){
            if(binaryData[i][j]=="1"){
                freq[binaryData[0][j]]++;
                item.push_back(binaryData[0][j]);
            }
        }
        transactions.push_back({id++,item});
    }
    cout << "Item\t Frequency\t\tSupport\n";
    for(auto item:freq){
        items.push_back(item);
        cout <<item.first<<"\t\t"<<item.second<<"\t\t"<<(item.second*1.0)/total*100<<"%\n";
    }
    return items;
}
vector<pair<string,int>> removeInfrequentItems(vector<pair<string,int>> &items,double support){
    vector<pair<string,int>> newItems;
    cout << "Item\t Frequency\t\tSupport\n";
    for(auto x:items){
        if(x.second*1.0/total*100 >= support){
            newItems.push_back(x);
            cout <<x.first<<"\t\t"<<x.second<<"\t\t"<<(x.second*1.0)/total*100<<"%\n";
        }
    }
    return newItems;
}

vector<vector<string>> makePairs(vector<pair<string,int>> &items,int len){
    vector<vector<string>> pairs;
    int n = items.size();
    for(int i = 0;i<n;i++){
        for(int j = i+1;j<n;j++){
            pairs.push_back({items[i].first,items[j].first});
        }
    }
    return pairs;
}

vector<pair<vector<string>,int>> getPairFreq(vector<vector<string>> &pairs,vector<pair<int,vector<string>>> &transactions){
    vector<pair<vector<string>,int>> res;
    for(auto x:pairs){
        int c = 0;
        for(auto y:transactions){//get each transaction and check for all element in pairs
            set<string> s;
            bool flag = 1;
            for(auto z:y.second){//get all items in current transaction in a set
                s.insert(z);
            }
            for(auto item:x){//now check if each element of current pair is present in this transaction
                if(s.find(item) == s.end()){//if even a single is not present 
                    flag = 0;//we mark it as false
                    break;
                }
            }
            if(flag) //if all are present 
                c++;//we increase the counter
        }
        res.push_back({x,c});
    }
    return res;
}


void printPairs(vector<pair<vector<string>,int>> &items2){
    cout << "Item\tFrequency\t\tSupport\n";
    for(auto x:items2){
        for(auto y:x.first){
            cout << y<<" ";
        }
        cout <<"\t"<<x.second<<"\t\t"<<x.second*1.0/total*100<<"%\n";
    }
}

void removeInfrequentItems(vector<pair<vector<string>,int>> &items,double support){
    // vector<pair<string,int>> newItems;
    cout << "Item\t Frequency\t\tSupport\n";
    for(auto x:items){
        if(x.second*1.0/total*100 >= support){
            for(auto y:x.first)
                cout <<y<<",";
            cout <<"\t\t"<<x.second<<"\t\t"<<(x.second*1.0)/total*100<<"%\n";
        }
    }
}
int main(){
    

    vector<pair<string,int>> items;
    double support,confidence;
    support = 50;
    confidence = 75.0;
    // string currLine;
    // ifstream MyReadFile("Market_Basket_Optimisation.csv");
    // int id =1 ;
    // while (getline(MyReadFile, currLine)) {
    //     // Output the text from the file
    //     int i = 0;
    //     string curr="";
    //     vector<string> line;
    //     while(currLine[i]!='\0'){
    //         if(currLine[i]==','){
    //             line.push_back(curr);
    //             curr="";
    //         }else{
    //             curr += currLine[i];
    //         }
    //         i++;
    //     }
    //     if(curr!="")
    //         line.push_back(curr);
    //     transactions.push_back({id,line});
    //     id++;
    // }

    // Close the file
    // MyReadFile.close();

    // transactions = {
    //     {1, {"Bread", "Cheese", "Egg", "Juice", "Yogurt"}},
    //     {2, {"Milk", "Cheese", "Egg", "Bread", "Juice"}},
    //     {3, {"Bread", "Milk", "Yogurt", "Cheese", "Egg"}},
    //     {4, {"Juice", "Bread", "Milk", "Cheese", "Yogurt"}},
    //     {5, {"Cheese", "Bread", "Juice", "Milk", "Egg"}},
    //     {6, {"Egg", "Juice", "Yogurt", "Cheese", "Milk"}},
    //     {7, {"Yogurt", "Bread", "Cheese", "Egg", "Milk"}},
    //     {8, {"Bread", "Cheese", "Juice", "Yogurt", "Egg"}},
    //     {9, {"Cheese", "Juice", "Milk", "Bread", "Egg"}},
    //     {10, {"Juice", "Bread", "Yogurt", "Cheese", "Milk"}}
    // };

    vector<vector<string>> binaryData = {
        {"Bread", "Cheese", "Egg", "Juice", "Yogurt"},
        {"1", "0", "1", "1", "0"},
        {"1", "1", "0", "0", "1"},
        {"1", "1", "1", "0", "1"},
        {"0", "1", "1", "1", "1"},
        {"1", "1", "0", "1", "0"},
        {"0", "1", "0", "1", "0"},
        {"1", "0", "1", "0", "1"},
        {"1", "1", "0", "1", "0"},
        {"1", "1", "0", "1", "1"},
        {"1", "1", "0", "0", "0"}
    };

    
    total = binaryData.size()-1;
    items = processBinaryData(binaryData);
    // total = transactions.size();
    // items = frequentItemSets(transactions);
    cout <<"Removing all items below given support\n\n\n";
    items = removeInfrequentItems(items,support);
    vector<vector<string>> pairs = makePairs(items,2);
    vector<pair<vector<string>,int>> items2 = getPairFreq(pairs,transactions);
    printPairs(items2);
    cout <<"Removing all items below given support\n\n\n";
    removeInfrequentItems(items2,support);
    return 0;
}