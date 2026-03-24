#ifndef BITS_H
#define BITS_H
#include <iostream>
#include <bitset>
#include <cassert>


class Bits {
    using IType = unsigned long long; // We only have to change the integer type here, if desired
    enum {NBITS = sizeof(IType)*8};
    IType bits = 0;
public:
    Bits() = default;
    Bits(IType n) {
        bits = n;
    }
    static int size() {
        return NBITS;
    }
    bool at(int pos) const {  // Returns (tests) the bit at bit-position pos
        assert(0 <= pos && pos < NBITS);
        return bits & (IType(1) << pos);
    }
    void set(int pos){
        bits |= (IType(1) << pos);
    }     // Sets the bit at position pos
    void set(){
        bits = ~IType(0);
    }            // Sets all bits
    void reset(int pos){
        bits &= ~(IType(1) << pos);
    }    // Resets (makes zero) the bit at position pos
    void reset(){
        bits = IType(0);
    }      // Resets all bits
    void assign(int pos, bool val){
        if (val){
            bits |= (IType(1) << pos);
        }else{
            bits &= ~(IType(1) << pos);
        }
    } // Sets or resets the bit at position pos depending on val
    void assign(IType n){
        bits = n;
    }    // Replaces the underlying integer with n
    void toggle(int pos){
        bits ^=(IType(1) << pos);
    }   // Flips the bit at position pos
    void toggle(){
        bits = ~bits;
    }            // Flips all bits
    void shift(int n){
        if (n > 0) {
            if (n >= NBITS) {
                bits = 0;
            } else {
                bits >>= n;
            }
        } else if (n < 0) {
            int k = -n;
            if (k >= NBITS) {
                bits = 0;
            } else {
                bits <<= k;
            }
        }

    }      // If n > 0, shifts bits right n places; if n < 0, shifts left
    void rotate(int n){
        if (n == 0) return;

        
        int k = n % NBITS;
        if (k < 0) k += NBITS; 

     
        bits = (bits >> k) | (bits << (NBITS - k));

    }   // If n > 0, rotates right n places; if n < 0, rotates left
    int ones() const{
        int count = 0;
        IType x = bits;
        while (x) {
            count += x & 1;
            x >>= 1;
        }
        return count;

    }        // Returns how many bits are set in the underlying integer
    int zeroes() const {      // Returns how many bits are reset in the underlying integer
        return NBITS - ones();
    }
    IType to_int() const {
        return bits;
    }
    friend bool operator==(const Bits& b1, const Bits& b2) {
        return b1.bits == b2.bits;
    }
    friend bool operator!=(const Bits& b1, const Bits& b2) {
        return b1.bits != b2.bits;
    }
    friend std::ostream& operator<<(std::ostream& os, const Bits& b) {
        return os << std::bitset<NBITS>(b.bits);    // Be sure to #include <bitset>
    }
};




#endif