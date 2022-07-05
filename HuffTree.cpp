#include<bits/stdc++.h>
using namespace std;

class HuffTree{
    public :
        int freq;
        char letter;
        HuffTree *left;
        HuffTree *right;

        HuffTree(char letter, int freq){
            this->freq=freq;
            this->letter=letter;
            this->left=NULL;
            this->right=NULL;
        }
};

HuffTree* createNode(char letter, int freq){
    HuffTree *node=new HuffTree(letter,freq);
    return (node);
}

class Compare{
    public:
        bool operator() ( HuffTree* &x, HuffTree* &y){
            return (x->freq>y->freq);
        }
};

HuffTree* makeTree(vector<pair<char,int>> &charFrequency){
    if(charFrequency.size()==0) 
        return (NULL);
    
    if(charFrequency.size()==1){
        HuffTree *root=createNode('*',0);
        HuffTree *node=createNode(charFrequency[0].first,charFrequency[0].second);
        root->left=node;
        return (root);
    }

    priority_queue<HuffTree*,vector<HuffTree*>,Compare> minHeap;

    for(int i=0; i<charFrequency.size(); i++){
        HuffTree *tempNode=createNode(charFrequency[i].first,charFrequency[i].second);
        minHeap.push(tempNode);
    }

    while (minHeap.size()>1){
        HuffTree *left=minHeap.top();
        minHeap.pop();
        HuffTree *right=minHeap.top();
        minHeap.pop();
        HuffTree *tempNode=createNode('~',left->freq+right->freq);
        tempNode->left=left;
        tempNode->right=right;
        cout<<left->letter<<" + "<<left->freq<<" , "<<right->letter<<" + "<<right->freq<<endl;
        minHeap.push(tempNode);
    }

    HuffTree* root=minHeap.top();
    return (root);
}

void inorder(HuffTree *root, map<char,string> &mp,string pathCode){
    if(root==NULL) return;
    if(root->left==NULL && root->right==NULL){
        mp[root->letter]=pathCode;
        return;
    }
    
    inorder(root->left,mp,pathCode+"0");
    inorder(root->right,mp,pathCode+"1");
}

map<char,string> getEncodedValues(HuffTree* root){
    map<char,string> mp;
    inorder(root,mp,"");

    return (mp);
}

vector<pair<char,int>> frequencyDetector(string &s){
    map<char,int> mp;
    for(int i=0; i<s.length(); i++){
        mp[s[i]]++;
    }

    vector<pair<char,int>> frequency;
    for(auto it=mp.begin(); it!=mp.end(); it++){
        frequency.push_back({it->first,it->second});
        cout<<it->first<<" "<<it->second<<endl;
    }

    return frequency;
}

string decode(HuffTree* root,string &encodedTxt){
    if(root==NULL) return ("");
    string decodedTxt="";
    HuffTree *currNode=root;
    int i=0;
    while(i<=encodedTxt.length()){
        if(currNode->left==NULL && currNode->right==NULL){
            decodedTxt.push_back(currNode->letter);
            currNode=root;
        }

        else if(encodedTxt[i]=='0'){
            i++;
            currNode=currNode->left;
        }
        else{
            i++;
            currNode=currNode->right;
        }
    }
    return decodedTxt;
}

int main(){
    string s;
    cin>>s;

    vector<pair<char,int>> charFrequency=frequencyDetector(s);
    cout<<"charSize "<<charFrequency.size()<<endl;
    HuffTree *root=makeTree(charFrequency);

    map<char,string> mp=getEncodedValues(root);

    string encodedTxt="";
    for(auto it=mp.begin(); it!=mp.end(); it++){
        cout<<it->first<<"  "<<it->second<<endl;
    }

    for(int i=0; i<s.length(); i++){
        encodedTxt+=mp[s[i]];
    }

    cout<<"*****************************************"<<endl;
    cout<<s<<endl;
    cout<<encodedTxt<<endl;
    
    string decodedTxt=decode(root,encodedTxt);
    cout<<decodedTxt<<endl;

    return (0);
}

