// 支持 8,16,32,64 bits mode
#ifndef __BITS_H__
#define __BITS_H__

#include <string>
#include <bitset>
#include <QObject>
using std::string;
using std::bitset;
#define uint64_t unsigned long long
#define BIT_MAX_LENGTH 64
class Bits : public QObject {
    Q_OBJECT

private:
    bitset<BIT_MAX_LENGTH> bit_mask;
    bitset<BIT_MAX_LENGTH> bit_data;
    unsigned int width;

    void set_bit_mask(unsigned int width);
//    bitset<BIT_MAX_LENGTH> get_mask(unsigned int bit_num);
//    bitset<BIT_MAX_LENGTH> get_mask(unsigned int bit_start, unsigned int bit_end);

public:
    enum STR_TYPE {HEX,DEC,OCT,BIN,DEC_S,ADDR};
    enum SHF_TYPE {SHF_LOGIC,SHF_ARITH,SHF_ROTATE};
    /***************** data read functions ******************/
    Bits(unsigned int width);
    bool get_bit(unsigned int bit_num);
    unsigned int get_bit_count();
    unsigned int get_width();
    uint64_t get_data();
    string get_hex_string();
    string get_dec_unsigned_string();
    string get_dec_signed_string();
    string get_oct_string();
    string get_bin_string();
    string get_addr_string();
    string get_string(Bits::STR_TYPE type);

    /***************** data change functions *****************/

    void set_width(unsigned int width);
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

    void shift_left(unsigned int bit_num);
    void shift_right(unsigned int bit_num);
    void set_shift_mode(SHF_TYPE shift_type);
    SHF_TYPE get_shift_mode();
    /* if success return true, set the value.
       if failed, return false, not set the value. */
    void set_data(unsigned long long bit_data);
    bool set_hex_string(string input_str);
    bool set_dec_unsigned_string(string input_str);
    bool set_dec_signed_string(string input_str);
    bool set_oct_string(string input_str);
    bool set_bin_string(string input_str);
    bool set_addr_string(string input_str);
    bool set_string(string input_str, Bits::STR_TYPE type);

    /***************** format check functions ******************/
    bool is_hex_format(string input_str);
    bool is_dec_unsigned_format(string input_str);
    bool is_dec_signed_format(string input_str);
    bool is_oct_format(string input_str);
    bool is_bin_format(string input_str);
    bool is_addr_format(string input_str);

    void broadcast_value_changed();
private:
    SHF_TYPE shift_mode = SHF_LOGIC;
    void send_value_changed_signal();
signals:
    void value_changed();

};

#endif
