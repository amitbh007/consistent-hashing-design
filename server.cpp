#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include "CryptoHash.h"

using namespace std;

struct node{
    int next;
    int id;
};

class compare{
public:
    bool operator()(pair<int,int> a,pair<int,int> b){
        return a.second>b.second;
    }
};

int find_here(vector<int> v,int b, int e, int key){
    if(b>e){
        return 0;
    }

    int mid=(b+e)/2;

    if(key==v[mid]){
        return v[mid];
    }
    else if(key>v[mid]){
        // if(key<v[mid+1]){
        //     return v[mid+1];
        // }
        // else
         return find_here(v,mid+1,e,key);
    }
    else{
        // if(key>v[mid-1]){
        //     return v[mid];
        // }
        // else
         return find_here(v,b,mid-1,key);
    }
}

class server{
    int server_ID;
    map<int,pair<int,int>> cache;
    public:
        int a=0;
        server(){
            server_ID=0;
        }
        server(int id){

            server_ID=id; //this hash is only for ID
        }

        int show_ID(){
            return server_ID;
        }

        void insert(int id,int data){
           if(cache[id].second==0){
            //new id
            if(cache.size()==4){
                int small=INT_MAX;
                int key;
                for(auto x:cache){
                    if(x.second.second<small){
                        small=x.second.second;
                        key=x.first;
                    }
                }
                cache.erase(key);

            }
            cache[id].first=data;
            cache[id].second=1;
           }
           else{
            // request id cache already present
            cache[id].first+=data;
            cache[id].second++;

           }
        }

        void show(){
            for(auto x:cache){
                cout<<"( "<<x.first<<" - "<<x.second.first<<" ) ";
            }
        }


};


class systemo{

int size;
map<int,int> server_space;
vector<int> location;
map<int,server> mp;

public:
    systemo(int a){
        size=a;


    }

    void add_server(string name){
        //create the server
        int server_name=(hash6(name.c_str(),name.length()))%size;
        server s(server_name);
        mp[server_name]=s;


        // put server in space
        int it[4];
         it[0]=(hash1(name.c_str(),name.length()))%size;
         it[1]=(hash2(name.c_str(),name.length()))%size;
         it[2]=(hash3(name.c_str(),name.length()))%size;
         it[3]=(hash4(name.c_str(),name.length()))%size;

         for(int i=0;i<4;i++){
            // cout<<it[i]<<" ";
            if(server_space[it[i]]!=0){
                server_space[it[i]]=server_name;
                location.push_back(it[i]);
            }
         }

         sort(location.begin(),location.end());

    }

    void serve(string name,int data){
        //c_str converts string to an array of letters
        int critical_id=(hash5(name.c_str(),name.length()))%size;
        int i;

        if(critical_id>location[location.size()-1]){
            i=*(location.begin());
        }
       else{
         i=find_here(location,0,location.size()-1,critical_id);
       }


        //binary search to find the server for corresponding id


        mp[server_space[i]].insert(critical_id,data);

    }

    void view_system(){
        for(auto x:mp){
            int a=x.first;
            cout<<"server no. "<<a<<" :- ";
            mp[a].show();
            cout<<endl;
        }

    }

};

int main(){

systemo s(20);

s.add_server("alpha009");
// // s.add_server("beta089");
// // s.add_server("gamna109");



// s.serve("request_id_35467",4);
// // s.serve("request_id_35467",6);
// // s.serve("request_id_21349",5);
// // s.serve("request_id_21349",6);
// // s.serve("request_id_86509",7);
// // s.serve("request_id_86509",7);
// // s.serve("request_id_78343",8);
// // s.serve("request_id_307689",19);


s.view_system();

    return 0;
}
