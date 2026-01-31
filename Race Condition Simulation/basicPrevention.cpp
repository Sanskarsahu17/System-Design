#include<iostream>
#include<vector>
#include<thread>

using namespace std;

bool inUse = false;
int counter = 0;

void task(int id){
    while(inUse){}
    // preemption prone 
    inUse = true;
    counter++;
    cout<<"Thread "<<id<<" counter: "<<counter<<endl;
    inUse = false;

}

int main(){
    vector<thread> threads;
    for(int i = 0; i < 10; i++){
        threads.emplace_back(task,i);
    }

    for(auto &t : threads){
        t.join();
    }

    return 0;
}