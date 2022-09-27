#include <iostream>
#include <random>
#include <ctime>


using namespace std;

// par 20000000 - 100000000 threads - 2
const long int VECTOR_LEN = 70000000;
const int THREADS = 4;

const int MAX_RAND = 100;


long int sequentialScalarProduct(const vector<long int> &a, const vector<long int> &b, long int len) {
    long int res = 0;
    for (long int i = 0; i < len; i++) {
        res += a[i] * b[i];
    }
    return res;
}

long int parallelScalarProduct(const vector<long int> &a, const vector<long int> &b, long int len) {
    long int res = 0;
    long int i;
    # pragma omp parallel shared(res, a, b, len) default(none) num_threads(THREADS)
    {
        long int private_sum = 0;
    # pragma omp for
        for (i = 0; i < len; i++) {
            private_sum += a[i] * b[i];
        }
    #pragma omp atomic
        res += private_sum;

    }
    return res;
}


vector<long int>
initVector(long int len, uniform_int_distribution<long int> intDistro, default_random_engine defEngine) {
    vector<long int> vec;
    for (long int i = 0; i < len; i++) {
        vec.push_back(intDistro(defEngine));
    }
    return vec;
}

int main() {
    default_random_engine defEngine(time(nullptr));
    uniform_int_distribution<long int> intDistro(1, MAX_RAND);
    vector<long int> a = initVector(VECTOR_LEN, intDistro, defEngine);
    cout << "first arr filled" << endl;
    vector<long int> b = initVector(VECTOR_LEN, intDistro, defEngine);
    cout << "start" << endl;

    unsigned int start_time_seq = clock();
    long int res = sequentialScalarProduct(a, b, VECTOR_LEN);
    unsigned int end_time_seq = clock();
    cout << "a.b = " << res << endl;
    cout << "seq time(sec) = " << float((end_time_seq - start_time_seq)) / CLOCKS_PER_SEC << endl;

    unsigned int start_time_par = clock();
    long int res_par = parallelScalarProduct(a, b, VECTOR_LEN);
    unsigned int end_time_par = clock();
    cout << "a.b = " << res_par << endl;
    cout << "par time(sec) = " << float((end_time_par - start_time_par)) / CLOCKS_PER_SEC << endl;

    return 0;
}
