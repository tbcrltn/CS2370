#include <iostream>
#include <stdexcept>
#include <cstddef>
using std::size_t;

class Vector {
    enum {CHUNK = 10};
    size_t capacity;
    size_t n_elems;
    int* data_ptr;
    void grow() {
        std::cout << "grow" << std::endl;
        size_t new_capacity = static_cast<size_t>(capacity * 1.6);
        if (new_capacity <= capacity) new_capacity = capacity + 1;
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < n_elems; i++)
            new_data[i] = data_ptr[i];
        delete[] data_ptr;
        data_ptr = new_data;
        capacity = new_capacity;
    }
public:
    Vector() { capacity = CHUNK; n_elems = 0; data_ptr = new int[capacity]; }
    ~Vector() { delete[] data_ptr; }
    Vector(const Vector& v) {
        capacity = v.capacity;
        n_elems = v.n_elems;
        data_ptr = new int[capacity];
        for (size_t i = 0; i < n_elems; i++)
            data_ptr[i] = v.data_ptr[i];
    }
    Vector& operator=(const Vector& v) {
        if (this != &v) {
            delete[] data_ptr;
            capacity = v.capacity;
            n_elems = v.n_elems;
            data_ptr = new int[capacity];
            for (size_t i = 0; i < n_elems; i++)
                data_ptr[i] = v.data_ptr[i];
        }
        return *this;
    }
    int front() const { if(n_elems==0) throw std::range_error("front"); return data_ptr[0]; }
    int back() const { if(n_elems==0) throw std::range_error("back"); return data_ptr[n_elems-1]; }
    int at(size_t pos) const { if(pos>=n_elems) throw std::range_error("at"); return data_ptr[pos]; }
    size_t size() const { return n_elems; }
    bool empty() const { return n_elems==0; }
    int& operator[](size_t pos) { return data_ptr[pos]; }
    void push_back(int item) { if(n_elems==capacity) grow(); data_ptr[n_elems++] = item; }
    void pop_back() { if(n_elems==0) throw std::range_error("pop_back"); --n_elems; }
    void insert(size_t pos, int item) {
        if(pos>n_elems) throw std::range_error("insert");
        if(n_elems==capacity) grow();
        for(size_t i=n_elems;i>pos;i--) data_ptr[i]=data_ptr[i-1];
        data_ptr[pos]=item; ++n_elems;
    }
    void erase(size_t pos) {
        if(pos>=n_elems) throw std::range_error("erase");
        for(size_t i=pos;i<n_elems-1;i++) data_ptr[i]=data_ptr[i+1];
        --n_elems;
    }
    void clear() { n_elems=0; }
    bool operator==(const Vector& v) const {
        if(n_elems!=v.n_elems) return false;
        for(size_t i=0;i<n_elems;i++) if(data_ptr[i]!=v.data_ptr[i]) return false;
        return true;
    }
    bool operator!=(const Vector& v) const { return !(*this==v); }
    int* begin() { return n_elems==0?nullptr:data_ptr; }
    int* end() { return n_elems==0?nullptr:data_ptr+n_elems; }
};

int main() {
    Vector v;
    for(int i=0;i<15;i++) v.push_back(i*2);
    std::cout << "Vector contents:"; for(size_t i=0;i<v.size();i++) std::cout<<" "<<v.at(i); std::cout<<std::endl;
    v.insert(5,999);
    std::cout << "After insert at 5:"; for(size_t i=0;i<v.size();i++) std::cout<<" "<<v[i]; std::cout<<std::endl;
    v.erase(2);
    std::cout << "After erase at 2:"; for(size_t i=0;i<v.size();i++) std::cout<<" "<<v[i]; std::cout<<std::endl;
    v.pop_back();
    std::cout << "After pop_back:"; for(size_t i=0;i<v.size();i++) std::cout<<" "<<v[i]; std::cout<<std::endl;
    v.clear();
    std::cout << "After clear, empty? "<<(v.empty()?"yes":"no")<<std::endl;
    return 0;
}