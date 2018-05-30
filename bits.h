// 支持 8,16,32,64 bits mode
#include <string>
#include <bitset>
using std::string;
using std::bitset;
#define uint64_t unsigned long long
#define BIT_MAX_LENGTH 64
class Bits {
private:
    bitset<BIT_MAX_LENGTH> bit_mask;
    bitset<BIT_MAX_LENGTH> bit_data;
    unsigned int width;

    void set_bit_mask(unsigned int width);
//    bitset<BIT_MAX_LENGTH> get_mask(unsigned int bit_num);
//    bitset<BIT_MAX_LENGTH> get_mask(unsigned int bit_start, unsigned int bit_end);

public:
    Bits(unsigned int width);
    void set_width(unsigned int width);
    bool get_bit(unsigned int bit_num);
    uint64_t get_data();

    void set_bit(unsigned int bit_num);
    void clear_bit(unsigned int bit_num);
    void reverse_bit(unsigned  int bit_num);
    void set_bits(unsigned  int bit_start, unsigned  int bit_end);
    void clear_bits(unsigned  int bit_start, unsigned  int bit_end);
    void reverse_bits(unsigned  int bit_start, unsigned int bit_end);
    void clear_all();
    void set_all();
    void reverse_all();

    void shift_arithmetic_right(unsigned  int bit_num);
    void shift_logic_right(unsigned  int bit_num);
    void shift_logic_left(unsigned  int bit_num);
    void shift_rotate_right(unsigned int bit_num);

    string get_hex_string();
    string get_dec_unsigned_string();
    string get_dec_signed_string();
    string get_oct_string();
    string get_bin_string();
    //string get_addr_string();

    /* 
        if success return true, set the value.
        if failed, return false, not set the value.
    */
    bool set_hex_string(string input_str);
    bool set_dec_unsigned_string(string input_str);
    bool set_dec_signed_string(string input_str);
    bool set_oct_string(string input_str);
    bool set_bin_string(string input_str);

    bool is_hex_format(string input_str);
    bool is_dec_unsigned_format(string input_str);
    bool is_dec_signed_format(string input_str);
    bool is_oct_format(string input_str);
    bool is_bin_format(string input_str);

    void set_data(unsigned long long bit_data);

};

