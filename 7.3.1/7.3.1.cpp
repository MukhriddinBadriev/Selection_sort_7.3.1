#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <chrono>
#include <numeric>

//void algo_sort(std::vector<int> &v) {    
//    int elem = v.size();
//    int a = 0;
//    int e = 0;
//    int min = v[a];
//   // for(int j=0;j<v.size();j++){
//    while (elem!=0) {
//        for (int i=a; i < v.size(); i++) {
//            if (v[i] <= min) {
//                min = v[i];
//                e = i;
//            }
//        }        
//        std::swap(v[e], v[a]);
//         a++;
//        --elem;
//    }
//}


void algo_sort(std::vector<int>& v, std::promise<int> prom) {
    int elem = v.size();
    
    int a = 0;
    int e = 0;
    int min = v[a];    
    while (elem != 0) {
        for (int i = a; i < v.size(); i++) {       
            if (v[i] <= min) {
                 min = v[i];
                 e = i;
            }             
        }        
        std::swap(v[e], v[a]);
        a++;
        --elem;        
    }
    prom.set_value(min);
}


int main()
{
    
    std::vector<int> v(10);    
    std::generate(v.begin(), v.end(), []() {return rand() % 10; });
    std::cout << "vector before sorting: " << "\n\n";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << ' ';
    }std::cout <<"\n\n" ;

    std::promise<int> P2;
    std::future<int> F2 = P2.get_future();
    auto res = std::async(std::launch::async,algo_sort,ref(v), move(P2));
    F2.wait();
    
    //algo_sort(v);

    std::cout << "vector after sorting: " << "\n\n";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << ' ';
    }std::cout << std::endl;
    
    return 0;
}