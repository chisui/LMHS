#include <unordered_map>
#include <iosfwd>

class VarMapper {

public:

 bool partial;
 bool weighted;

 void map(std::istream & in, std::ostream & out);

 void unmap(std::istream & in, std::ostream & out);
 
private:

 std::unordered_map<unsigned, unsigned> var_map;
 std::unordered_map<unsigned, unsigned> inv_var_map;

};
