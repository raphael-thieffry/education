#include <iostream>
#include <cassert>
#include <memory>


template<typename T, int N>
struct small_array {
    private:
    T data[N];
    public :
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

template<typename T, int N>
struct large_array {
    private :
    std::unique_ptr<small_array<T, N>> a;
    public :
    large_array() : a(std::make_unique<small_array<T, N>>()) {}

    large_array(large_array const &other) : a(std::make_unique<small_array<T, N>>(*other.a)) {}

    large_array(large_array &&other) : a(std::move(other.a)) {}

    large_array &operator=(large_array const &other) {
        a = std::make_unique<small_array<T, N>>(*other.a);
        return *this;
    }

    T &operator[](int i)  { 
        return a->operator[](i); 
    }

    T const &operator[](int i) const  {
        return a->operator[](i); 
    }

    T at(int i) const  { 
        return a->at(i); 
    }

    T& at(int i)  { 
        return a->at(i); 
    }

    int size() const { return a->size(); }

    T *begin() { return a->begin(); }

    T *end() { return a->end(); }

    void swap(large_array &other) {
        a.swap(other.a);
    }
    
};

int main() {
    large_array <int , 1000 * 1000 * 10> t;
    t.at(2) = 42;
    large_array <int , 1000 * 1000 * 10> const u = t;
    for (std:: size_t i = 0; i < 4; ++i) {
        std::cout << '[' << i << "] = " << u.at(i) << '\n';
    }
    //t.at(4) = 0; // assertion failed!

    std::cout<< "test swap\n";
    large_array <int , 1000 * 1000 * 10> t2;
    for (int i = 0; i < t2.size(); ++i) {
        t2[i] = i;
    }
    t.swap(t2);
    std::cout << "t\n";
    int i = 0;
    for (auto &v : t) {
        i++;
        if(i > 10)
            break;
        std::cout << v << std::endl;
    }
    i = 0;
    std::cout << "t2\n";
    for (auto &v : t2) {
        i++;
        if(i > 10)
            break;
        std::cout << v << std::endl;
    }

    
    //operateur d'affectation de copie

    large_array <int , 1000 * 1000 * 10> t3;
    t3 = t2;
    std::cout << "t3\n";
    i = 0;
    for (auto &v : t3) {
        i++;
        if(i > 10)
            break;
        std::cout << v << std::endl;
    }

    std::cout << "End of program\n";

}