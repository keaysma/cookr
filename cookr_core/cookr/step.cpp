#include "step.hpp"

int32_t Step::count(const string find_str){
    int32_t counts = 0, last_instance = 0, find_str_len = find_str.size();

    while((last_instance = step_text.find(find_str, last_instance)) != string::npos){
        last_instance += find_str_len;
        ++counts;
    }

    return counts;
}

void Step::find_and_replace(const string find_str, const string replace_str){
    size_t loc;
    if((loc = step_text.find(find_str)) != string::npos)
        step_text.replace(loc, find_str.length(), replace_str);
}

void Step::find_and_replace_all(const string find_str, const string replace_str){
    size_t loc;
    while((loc = step_text.find(find_str)) != string::npos)
        step_text.replace(loc, find_str.length(), replace_str);
}