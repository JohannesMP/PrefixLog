#include <string>
#include <iostream>
#include <iomanip>
#include "PrefixLog.h"

using namespace std;

struct Foo { 
  Foo(string n) : name(n) {}
  string name;
};
ostream &operator<<(ostream& os, const Foo& foo) { 
  return os << "[\n"                    // multi-line object output
            << "  Foo:'" << foo.name << "'\n"
            << "]"; 
}

int main()
{
  using PrefixLog::Log;

  Log("1) Setting Prefix:"); 
  Log("***| ") << "This Log\nadds a prefix\nto every line.";

  Log("2) Works like std::cout:");
  Log(5) << "It works "            // New line
         << "just like std::cout"  // Still same line
         << endl                   // New line
         << "and supports std::endl.";

  Log("3) Trailing Newlines:");
  Log(5, '-') << " You don't need \\n (or std::endl) as the last character"; 
  Log(5, '+') << " But it handles them in case you forget :)" << endl;

  Log("4) Manipulators and Overloads:");
  Log("  INFO: ") 
    << "It supports manipulators: " << fixed << setprecision(4) << 1.5 << endl
    << "And and objects, even if multi-line:\n" << Foo("bar");

  Log("5) Function Fallback:");
  Log("- Can be used as standalone function.");
  Log("- Unlike prefix mode, the last trailing newline is not ignored!\n");
  Log("---");
}



