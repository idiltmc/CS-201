using namespace std;
#include <iostream>
#include <ctime>
#include <chrono>
#include <climits>

unsigned long long pow(int a, int b){
    unsigned long long res = 1;
    for(int i = 0 ; i < b ; i++){
        res = res * a;
    }
    return res;
}


int algorithm1(int a , long long n , int p){
   long long res = 1 ;

    for(int i = 0 ; i < n ; i++){

        res = res * a;
        res = res % p;
    
    }

    return res;
}

int algorithm2(int a , long long n , int p){
    int res = 0;
    long long mux = a;
    for(int i = 1 ; i < n ; i++){
        if(mux % p == 1){
            int b = 1;
            for(int j = 0 ; j < n % i ; j++){
                
                b = b * a;
                b = b % p;
            }
            return b;
        }
        
        mux = mux * a;
        mux = (mux % p);
        
        
    }
    res = mux % p;
    return res;
}

int algorithm3(int a , unsigned long long n , int p){
    
   if(n == 1){
       return a%p;
   }

   else if ( n % 2 == 1){
       unsigned long long result =  algorithm3(a, (n-1) / 2, p);
       return ((((a * result) % p )* result)% p);
   }
   else  {
       unsigned long long result =  algorithm3(a, n / 2, p);
       return (((( result))* result)% p);
   }
}






int main(){

    std::chrono::time_point< std::chrono::system_clock > startTime;
    std::chrono::duration< double, milli > elapsedTime;
    int res;
    long long k = 1000000;

        double alg1_arr[10];
        double alg2_arr[10];
        double alg3_arr[10];



        for(int i = 1 ; i <= 10 ; i++){

            //elasped time for algortihm 1
            startTime = std::chrono::system_clock::now();
            for(int j = 0 ; j < 10 ; j++){
                res = algorithm1(1000, 100000000*i, 101);
            }
            cout << res << endl;
            elapsedTime = std::chrono::system_clock::now() - startTime;
            cout << "Execution took for algorithm 1: " << elapsedTime.count() << " milliseconds."<< endl;
            alg1_arr[i-1] = elapsedTime.count();

            //elasped time for algortihm 2
            startTime = std::chrono::system_clock::now();
            for(int j = 0 ; j < k ; j++){
                res = algorithm2(1000, 100000000*i, 10007);
            }

            cout << res << endl;
            elapsedTime = std::chrono::system_clock::now() - startTime;
            cout << "Execution took for algorithm 2: " << elapsedTime.count() << " milliseconds."<< endl;
            alg2_arr[i-1] = elapsedTime.count() *10 ;


            //elasped time for algortihm 3
            startTime = std::chrono::system_clock::now();
            for(int j = 0 ; j < k ; j++){
                 res = algorithm3(1000, 100000*pow(2,i), 101);
            }
            cout << res << endl;
            elapsedTime = std::chrono::system_clock::now() - startTime;
            cout << "Execution took " << elapsedTime.count() << " milliseconds."
            << endl;
            alg3_arr[i-1] = elapsedTime.count() ;

        }

        for (int i = 0; i < 10; i++) {
            cout << alg1_arr[i] <<  ",";
        }
        cout << endl;

        for (int i = 0; i < 10; i++) {
            cout << alg2_arr[i] <<  ",";
        }
        cout << endl;

        for (int i = 0; i < 10; i++) {
            cout << alg3_arr[i] <<  ",";
        }
        cout << endl;
    




}

