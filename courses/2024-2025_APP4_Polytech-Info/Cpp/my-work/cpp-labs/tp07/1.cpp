#include <iostream>
#include <cassert>

template<typename T, int N>
struct small_array {
    T data[N];

    small_array() = default;
    T &operator[](int i)  { 
        assert(i >= 0 && i < N);
        return data[i]; 
    }
    T const &operator[](int i) const  {
        assert(i >= 0 && i < N); 
        return data[i]; 
    }
    T at(int i) const  { 
        if( i < 0 || i >= N ) throw std::out_of_range("small_array::at");
        return data[i]; 
    }
    T& at(int i)  { 
        if( i < 0 || i >= N ) throw std::out_of_range("small_array::at");
        return data[i]; 
    }

    int size() const { return N; }

    T *begin() { return data; }
    T *end() { return data + N; }
};

int main() {
    small_array <int , 4> t;
    t.at(2) = 42;
    small_array <int , 4> const u = t;
    for (std:: size_t i = 0; i < 4; ++i) {
    std::cout << '[' << i << "] = " << u.at(i) << '\n';
    }
    t.at(4) = 0; // assertion failed!
    std::cout << "End of program\n";
}