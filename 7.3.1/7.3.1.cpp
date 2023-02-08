#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <chrono>
#include <numeric>


int find_min(std::vector<int>& v,int start, std::promise<int> find_promise) {
    int a = 0;
    int min = v[0];
    int z = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] < min) {
            min = v[i];
            z = i;
            find_promise.set_value(z);
        }
    }    
    return z;
}

void algo_sort(std::vector<int> &v) {
    int elem = v.size();
    int a = 0;
    int e = 0;
    int min = v[a];   
    while (elem!=0) {                
        std::promise<int> P;
        std::future<int> F = P.get_future();
        std::future<int> res = std::async(std::launch::async, find_min, std::ref(v), a, move(P));
        int min_number = F.get();
        std::swap(v[min_number], v[a]);
         a++;
        --elem;
    }
}
   
int main()
{
        std::vector<int> v(5);
        std::generate(v.begin(), v.end(), []() {return rand() % 10; });
        std::cout << "vector before sorting: " << "\n\n";
        for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << ' ';
        }std::cout << "\n\n";
        
        algo_sort(v);

        std::cout << "vector after sorting: " << "\n\n";
        for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << ' ';
        }std::cout << std::endl;
   
    return 0;
}