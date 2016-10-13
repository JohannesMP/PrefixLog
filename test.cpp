#include <iostream>
#include <iomanip>
#include "PrefixLog.h"

using namespace std;
using Debug::Log;

struct Foo { 
  Foo(string s) : text("Foo contains '" + s + "'") {}
  string text;
};
ostream &operator<<(ostream& os, const Foo& foo) { return os << foo.text; }

int main()
{
  // Can be used as a raw function call
  Log("1) Basic Usage:"); 
  Log("***| ") << "This Log adds a prefix\nto every line \nand an automatic newline when done.";

  Log("2) Insertion Operators:");
  Log(5) << "It supports "         // Starting a line
         << "insertion operators"  // Still same line
         << endl                   // New line
         << "and std::endl";

  Log("3) Trailing Newlines:");
  Log(5, '-') << " You don't need \\n (or std::endl) as the last character\n"; 
  Log(5, '+') << " But it handles them in case you forget :)" << std::endl;

  Log("4) Manipulators and Overloads:");
  Log("  INFO: ") 
    << "It works with manipulators: " << fixed << setprecision(4) << 1.5 << endl
    << "And std::cout overloaded objects: " << Foo("secret");

  // By itself is just a newline
  Log();
}



