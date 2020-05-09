#include <string>
#include <vector>

using namespace std;

class Step{
    string step_text, output_text;
    uint32_t id;
    int32_t dependency;
    Step();
public:
    Step(uint32_t _id, string _step_text, string _output_text, int32_t _dependency):
        id(_id),
        step_text(_step_text),
        output_text(_output_text),
        dependency(_dependency)
    {}

    uint32_t get_id () const { return id; }
    string get_step_text () const { return step_text; }
    string get_output_text () const { return output_text; }
    int32_t get_dependency () const { return dependency; }
    int32_t count(const string);
    void find_and_replace(const string, const string);
    void find_and_replace_all(const string, const string);
};