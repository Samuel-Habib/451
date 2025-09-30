struct Test{
    double result;
    double seconds;
};

// Test n_threads(int threads, int max){
//     std::vector<int64_t> intervals(2*threads);
//     int q = max/threads;
//
//     for(int i = 0; i<threads; ++i){
//         intervals[2*i] = i * q +1;
//         intervals[2*i+1] = (i+1) *q;
//     }
//
//     std::vector<std::threads> ts;
//     std::vector<double> part(threads, 0.0);
//
//     auto t0 = std::chrono::high_resolution_clock::now();
//     
//     for(int i = 0; i< threads; ++i){
//          
//     }
//
//
// }


