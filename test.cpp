#include <iostream>
#include <iomanip>
#include "PrefixLog.h"

using namespace std;
using namespace Debug;

struct Foo { 
  Foo(string s) : text("Foo contains '" + s + "'") {}
  string text;
};
ostream &operator<<(ostream& os, const Foo& foo) { return os << foo.text; }

int main()
{
  cout << "DEMO 1:\n";
  Log(5) << "This Log prefixes what it prints,\neven if more than one line.";

  cout << "DEMO 2:\n";
  Log("|***|") << " It has "<< "insertion operator" << " support" 
    << endl << " which works with std::endl.";
  
  cout << "DEMO 3:\n";
  Log(5, '_') << " You don't need \\n or std::endl as the last character\n"; 
  Log(5, '_') << " But it handles them in case you forget :)" << endl;

  cout << "DEMO 4:\n";
  Log("  INFO: ") 
    << "It works with manipulators: " << fixed << setprecision(4) << 1.5 << endl
    << "And std::cout overloaded objects: " << Foo("secret");
}



