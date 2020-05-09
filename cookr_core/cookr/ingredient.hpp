//#include <cstdio>
#include <vector>
#include <string>

using namespace std;

enum class WordType {
    CountableNoun, UncountableNoun
};

class Ingredient{
    string name;
    uint32_t amount;
    WordType wordtype;
    vector<int32_t> used_steps;

    Ingredient();

public:
    //ctors
    Ingredient(string, uint32_t);
    //Ingredient(Ingredient &);
    Ingredient(string name_, uint32_t amount_, WordType wordtype_):
        name(name_),
        amount(amount_),
        wordtype(wordtype_)
    {}

    //getters
    string get_name() const { return name; }
    uint32_t get_amount() const { return amount; }
    WordType get_wordtype() const { return wordtype; }
    vector<int32_t> get_used_steps () const { return used_steps; }

    //setters
    void set_name(string & name_){ name = name_; }
    void set_amount(uint32_t & amount_){ amount = amount_; }
    void set_wordtype(WordType & wordtype_){ wordtype = wordtype_; }
    void set_used_steps(vector<int32_t> _used_steps){ used_steps = _used_steps; }
    void add_used_steps(int32_t step_id){ used_steps.push_back(step_id); };

    //methods
    void find_and_replace(const string, const string);

    //operator overrides
    operator string(){ return name; }
    Ingredient operator + (string);
};

//general operator overrides
Ingredient operator + (string, Ingredient);