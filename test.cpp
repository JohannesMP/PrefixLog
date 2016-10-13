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
  Log("1) Setting Prefix:"); 
  Log("***| ") << "This Log\nadds a prefix\nto every line.";

  Log("2) Works like std::cout:");
  Log(5) << "It works "            // New line
         << "just like std::cout"  // Still same line
         << std::endl              // New line
         << "and supports std::endl.";

  Log("3) Trailing Newlines:");
  Log(5, '-') << " You don't need \\n (or std::endl) as the last character"; 
  Log(5, '+') << " But it handles them in case you forget :)" << std::endl;

  Log("4) Manipulators and Overloads:");
  Log("  INFO: ") 
    << "It supports manipulators: " << fixed << setprecision(4) << 1.5 << endl
    << "And std::cout overloaded objects: " << Foo("secret");

  Log("5) Function Fallback:");
  Log("- Can be used as standalone function.");
  Log("- Unlike prefix mode, the last trailing newline is not ignored!\n");
  Log("---");
}



