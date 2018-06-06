#include "bits.h"
#include <string>
#include <bitset>
#include <regex>
#include <sstream>
#include <iostream>
#include <QDebug>
#include <QRegExp>
#include <QString>

using std::string;
using std::bitset;

Bits::Bits(unsigned int width){
    this-> bit_data.reset();
    this-> set_width(width);
}

void Bits::send_value_changed_signal(){
    emit value_changed();
}

void Bits::set_bit_mask(unsigned int width){
    switch (width) {
    case 8:
        bit_mask = (0xFF);
        break;
    case 16:
        bit_mask = 0xFFFF;
        break;
    case 32:
        bit_mask = 0xFFFFFFFF;
        break;
    case 64:
        bit_mask = 0xFFFFFFFFFFFFFFFF;
        break;
    default:
        break;
    }
}
/**************** data change functions *********************/

void Bits::set_width(unsigned int width){
    set_bit_mask(width);
    bit_data = bit_data & bit_mask;
    this->width = width;
    send_value_changed_signal();
}

void Bits::set_bit(unsigned int bit_num){
    bit_data.set(bit_num);
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::clear_bit(unsigned int bit_num){
    bit_data.reset(bit_num);
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::reverse_bit(unsigned  int bit_num){
    bit_data.flip(bit_num);
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::set_bits(unsigned  int bit_start, unsigned  int bit_end){
    unsigned int i;
    for (i = bit_start; i<= bit_end; i++){
       bit_data.set(i);
    }
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::clear_bits(unsigned  int bit_start, unsigned  int bit_end){
    unsigned int i;
    for (i = bit_start; i<= bit_end; i++){
       bit_data.reset(i);
    }
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::reverse_bits(unsigned  int bit_start, unsigned int bit_end){
    unsigned int i;
    for (i = bit_start; i<= bit_end; i++){
       bit_data.flip(i);
    }
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::clear_all(){
    bit_data.reset();
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::set_all(){
    bit_data.set();
    bit_data &= bit_mask;
    send_value_changed_signal();
}
void Bits::reverse_all(){
    bit_data.flip();
    bit_data &= bit_mask;
    send_value_changed_signal();
}

/**********************   shift operate *******************/
void Bits::shift_arithmetic_right(unsigned  int bit_num){
    bit_num = bit_num % width;
    if (bit_data[width-1] == 0){
        bit_data = (bit_data >> bit_num);
    }
    else{
        bit_data = (bit_data >> bit_num);
        this->set_bits(width-bit_num, width-1);
    }
    send_value_changed_signal();
}

void Bits::shift_logic_right(unsigned  int bit_num){
    bit_num = bit_num % width;
    bit_data = (bit_data >> bit_num);
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::shift_logic_left(unsigned  int bit_num){
    bit_num = bit_num % width;
    bit_data = (bit_data << bit_num);
    bit_data &= bit_mask;
    send_value_changed_signal();
}

void Bits::shift_rotate_right(unsigned int bit_num){
    bit_num = bit_num % width;
    int temp;
    for (;bit_num>0;bit_num--){
        temp = bit_data[0];
        bit_data = bit_data >> 1;
        bit_data[width-1] = temp;
    }
    send_value_changed_signal();
}

/************* get format string ***********************/
string Bits::get_hex_string(){
    char buff[100];
    sprintf(buff,"%llX",bit_data.to_ullong());
    return string(buff);
}

string Bits::get_dec_unsigned_string(){
    char buff[100];
    sprintf(buff,"%llu",bit_data.to_ullong());
    return string(buff);
}

string Bits::get_dec_signed_string(){
    char buff[100];
    if (bit_data[width-1] == 0){
        sprintf(buff,"%lld", bit_data.to_ullong());
    }
    else{
        sprintf(buff,"%lld", (bit_data | ~ bit_mask).to_ullong());
    }
    return string(buff);
}

string Bits::get_oct_string(){
    char buff[100];
    sprintf(buff,"%llo",bit_data.to_ullong());
    return string(buff);
}

string Bits::get_bin_string(){
    return bit_data.to_string().substr(BIT_MAX_LENGTH-width);
}

uint64_t Bits::get_data(){
    return bit_data.to_ullong();
}

bool Bits::get_bit(unsigned int bit_num){
    return bit_data.test(bit_num);
}

unsigned int Bits::get_width(){
    return this->width;
}

unsigned int Bits::get_bit_count(){
    return bit_data.count();
}


/******************    check string format *************************/

bool Bits::is_hex_format(string input_str){
    unsigned int max_len;
    max_len = this->width/4;
    std::string pattern("^[0x]*0*[0-9a-fA-F]{1,"+ std::to_string(max_len) +"}$");
    std::regex re(pattern);
    return std::regex_match(input_str, re);
}

bool Bits::is_dec_unsigned_format(string input_str){
    uint64_t max_value,value;
    unsigned int max_len=20;  //64bit max dec width
    max_value = this->bit_mask.to_ullong();
    std::string pattern("^0*[0-9]{1,"+ std::to_string(max_len) +"}$");
    std::regex re(pattern);
    if (regex_match(input_str,re)){
        try {
            value = std::stoull(input_str,nullptr,10);
        }
        catch (std::out_of_range) {
            return false;
        }
        if (value <= max_value)
            return true;
    }
    return false;
}

bool Bits::is_dec_signed_format(string input_str){
    uint64_t value;
    unsigned int max_len=19;  //64bit max dec width
    std::string pattern("^-*0*[0-9]{1,"+ std::to_string(max_len) +"}$");
    std::regex re(pattern);
    if (regex_match(input_str,re)){
        try {
            value =(unsigned long long) std::stoll(input_str,nullptr,10);
        }
        catch (std::out_of_range) {
            return false;
        }
        if ((value & ~(this->bit_mask.to_ullong())) == 0)
            return true;
    }
    return false;
}

bool Bits::is_oct_format(string input_str){
    unsigned int max_len;
    bool format_ok;
    uint64_t value, max_value;
    std::stringstream ss;
    max_len = (this->width+2)/3;
    max_value = this->bit_mask.to_ullong();
    std::string pattern("^0*[0-7]{1,"+ std::to_string(max_len) +"}$");
    std::regex re(pattern);
    format_ok = std::regex_match(input_str, re);
    if(format_ok){ //check is to big
        try {
            value = std::stoull(input_str,nullptr,8);
        }
        catch (std::out_of_range) {
            return false;
        }
        if (value <= max_value)
            return true;
    }
    return false;
}

bool Bits::is_bin_format(string input_str){
    unsigned int max_len;
    max_len = this->width;
    std::string pattern("^[0-1]{1,"+ std::to_string(max_len) +"}$");
    std::regex re(pattern);
    return std::regex_match(input_str, re);
}

/****************** set value by string  *************************/

void Bits::set_data(uint64_t data){
    bit_data = data;
    bit_data &= bit_mask;
    //when the value changed, send this signal out.
    send_value_changed_signal();
}

bool Bits::set_hex_string(string input_str){
    if (is_hex_format(input_str)){
        this->set_data(std::stoull(input_str,nullptr,16));
        return true;
    }
    return false;
}

bool Bits::set_oct_string(string input_str){
    if (is_oct_format(input_str)){
        this->set_data(std::stoull(input_str,nullptr,8));
        return true;
    }
    return false;

}

bool Bits::set_bin_string(string input_str){
    if (is_bin_format(input_str)){
        this->set_data(std::stoull(input_str,nullptr,2));
        return true;
    }
    return false;
}

bool Bits::set_dec_unsigned_string(string input_str){
    if (is_dec_unsigned_format(input_str)){
        this->set_data(std::stoull(input_str,nullptr,10));
        return true;
    }
    return false;
}

bool Bits::set_dec_signed_string(string input_str){
    if (is_dec_signed_format(input_str)){
        this->set_data(std::stoull(input_str,nullptr,10));
        return true;
    }
    return false;
}

string Bits::get_addr_string(){
    uint    count[7] = {0};
    QString unit[7] = {"B", "K", "M", "G", "T", "P", "E"};// "Z", "Y", "B"};
    QString tmp_str;
    for (int i=6;i>=0;i--){
        count[i]= (bit_data.to_ullong() >> (i*10)) % 1024;
        if (count[i] != 0){
            tmp_str.append(QString::number(count[i])+unit[i]);
        }
    }
    if (tmp_str == ""){
        tmp_str = "0B";
    }
    return tmp_str.toStdString();
}

uint64_t addr_to_data(string input_str){
    uint64_t tmp_num;
    QString q_input_str = QString::fromStdString(input_str);
    //QString pattern("^(\\d+E)*(\\d+P)*(\\d+T)*(\\d+G)*(\\d+M)*(\\d+K)*(\\d+B)*$");
    //TODO: change to std::regex
    QString pattern("^(?:(\\d+)E)?(?:(\\d+)P)?(?:(\\d+)T)?(?:(\\d+)G)?(?:(\\d+)M)?(?:(\\d+)K)?(?:(\\d+)B)?$");
    QRegExp rx(pattern);
    rx.exactMatch(q_input_str.toUpper());
    tmp_num =   ( rx.cap(1).toULongLong() << 60 ) +
                ( rx.cap(2).toULongLong() << 50 ) +
                ( rx.cap(3).toULongLong() << 40 ) +
                ( rx.cap(4).toULongLong() << 30 ) +
                ( rx.cap(5).toULongLong() << 20 ) +
                ( rx.cap(6).toULongLong() << 10 ) +
                rx.cap(7).toULongLong();
    return tmp_num;
}

bool Bits::is_addr_format(std::string input_str){
    bool format_ok; uint64_t value, max_value;
    max_value = this->bit_mask.to_ullong();
    std::string pattern("^(?:(\\d+)E)?(?:(\\d+)P)?(?:(\\d+)T)?(?:(\\d+)G)?(?:(\\d+)M)?(?:(\\d+)K)?(?:(\\d+)B)?$");
    std::regex re(pattern);
    format_ok = std::regex_match(input_str, re);
    if(format_ok){ //check is to big
        value = addr_to_data(input_str);
        if (value <= max_value)
            return true;
    }
    return false;

}

bool Bits::set_addr_string(string input_str){
    if (is_addr_format(input_str)){
        this->set_data(addr_to_data(input_str));
        return true;
    }
    return false;
}

string Bits::get_string(Bits::STR_TYPE type){
    switch (type) {
    case Bits::HEX:
        return get_hex_string();
        break;
    case Bits::DEC:
        return get_dec_unsigned_string();
        break;
    case Bits::OCT:
        return get_oct_string();
        break;
    case Bits::BIN:
        return get_bin_string();
        break;
    case Bits::DEC_S:
        return get_dec_signed_string();
        break;
    case Bits::ADDR:
        return get_addr_string();
        break;
    default:
        return "";
        break;
    }
}

bool Bits::set_string(string input_str, Bits::STR_TYPE type){
    switch (type) {
    case Bits::HEX:
        return set_hex_string(input_str);
        break;
    case Bits::DEC:
        return set_dec_unsigned_string(input_str);
        break;
    case Bits::OCT:
        return set_oct_string(input_str);
        break;
    case Bits::BIN:
        return	set_bin_string(input_str);
        break;
    case Bits::DEC_S:
        return	set_dec_signed_string(input_str);
        break;
    case Bits::ADDR:
        return	set_addr_string(input_str);
        break;
    default:
        return false;
        break;
    }
}


void Bits::broadcast_value_changed(){
    send_value_changed_signal();
}

void Bits::shift_left(unsigned int bit_num){
    switch (shift_mode) {
    case SHF_LOGIC:
        shift_logic_left(bit_num);
        break;
    case SHF_ARITH:
        // same as logic left shift
        shift_logic_left(bit_num);
        break;
    case SHF_ROTATE:
        //TODO
        shift_rotate_right( abs((signed int)(width - bit_num)));
        break;
    default:
        break;
    }

}
void Bits::shift_right(unsigned int bit_num){
    switch (shift_mode) {
    case SHF_LOGIC:
        shift_logic_right(bit_num);
        break;
    case SHF_ARITH:
        shift_arithmetic_right(bit_num);
        break;
    case SHF_ROTATE:
        shift_rotate_right(bit_num);
        break;
    default:
        break;
    }
}

void Bits::set_shift_mode(SHF_TYPE shift_type){
    this->shift_mode = shift_type;
}
Bits::SHF_TYPE Bits::get_shift_mode(){
    return this->shift_mode;
}
