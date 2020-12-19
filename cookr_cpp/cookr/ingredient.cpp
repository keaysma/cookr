#include "ingredient.hpp"

//copy ctor
/*Ingredient::Ingredient(Ingredient & ingredient){
    set_name(ingredient.name);
    set_amount(ingredient.amount);
    set_wordtype(ingredient.wordtype);
}*/

//methods
void Ingredient::find_and_replace(const string find_str, const string replace_str){
    size_t loc;
    while((loc = name.find(find_str)) != string::npos)
        name.replace(loc, find_str.length(), replace_str);
}

//operator overrides
Ingredient Ingredient::operator + (string str) {
    Ingredient _ingredient (*this);

    string name_ = _ingredient.get_name() + " " + str;
    _ingredient.set_name(name_);

    return _ingredient;
}

//general operator overrides
Ingredient operator + (string str, Ingredient & ingredient){
    Ingredient _ingredient (ingredient);

    string _name = str + " " + _ingredient.get_name();
    _ingredient.set_name(_name);

    return _ingredient;
}
