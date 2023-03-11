#include "priority_queue.hpp"
#include <iostream>
int main(){
    sjtu::priority_queue<int> pq;
    for(int i=1;i<=10;++i) {
        pq.push(i);
    }
    for(int i=1;i<=10;++i){
        std::cout<<pq.top()<<' ';
        pq.pop();
    }
}
