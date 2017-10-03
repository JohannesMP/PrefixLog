# PrefixLog
A simple header-only debug log for c++ with a focus on ease of use.

It can prefix multi-line text automaticaly, while still behaving just like `std::cout`.

------


#### 1) Setting Prefix:
```c++
std::cout << "START\n";
Log("***| ") << "This Log\nadds a prefix\nto every line.";
std::cout << "STOP\n";

//START
//***| This Log 
//***| adds a prefix
//***| to every line
//STOP
```

#### 2) Like std::cout:
```c++
Log(5) << "It works "            // New line
       << "just like std::cout"  // Still same line
       << std::endl              // New line
       << "and supports std::endl.";

//     It works just like std::cout
//     and supports std::endl.
```

#### 3) Trailing Newlines:
```c++
std::cout << "START\n";
Log(5, '-') << " You don't need \\n (or std::endl) as the last character."; 
Log(5, '+') << " But it still handles them in case you forget :)" << std::endl;
std::cout << "STOP\n";

//START
//----- You don't need \n or std::endl as the last character.
//+++++ But it still handles them in case you forget :)
//STOP
```

#### 4) Manipulators and Overloads:
```c++
struct Foo { 
  Foo(string n) : name(n) {}
  string name;
};
ostream &operator<<(ostream& os, const Foo& foo) { 
  return os << "[\n"
            << "  Foo:'" << foo.name << "'\n"  // multi-line object
            << "]"; 
}

// ...

Log("  INFO: ") 
  << "It supports manipulators: " << fixed << setprecision(4) << 1.5 << endl
  << "And and objects, even if multi-line:\n" << Foo("bar");

//  INFO: It supports manipulators: 1.5000
//  INFO: And and objects, even if multi-line:
//  INFO: [
//  INFO:   Foo:'bar'
//  INFO: ]

```

#### 5) Function Fallback:
```c++
std::cout << "START\n";
Log("- Can be used as standalone function.");
Log("- Unlike prefix mode, the last trailing newline is not ignored!\n");
std::cout << "STOP\n";

//START
//- Can be used as standalone function.
//- Unlike prefix mode, the last trailing newline is not ignored!
//
//STOP
```

------

Please see Test.cpp for detailed usage.

------


### Todo

* Log File Support
  * Currently there is no support for outputting the printed log to a file automatically.
  * It should be easy to set up a static configuration object read by `PrefixLogProxy`, and used to print to a defined log file or stream whenever it writes to `std::cout` internally.
  
* Improve prefixing on newlines in strings
  * Currently newline characters in strings just use `find` and `replace` to add the prefix.
  * Performance can probably be improved by walking the string with a pointer.
