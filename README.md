# PrefixLog
A simple debug log for c++ with a focus on usability.

It can prefix any text printed automaticaly, while still behaving just like `std::cout`.

======

#### Function Fallback:

```c++
std::cout << "START\n";
Log("Can be used as a simple function. Output has automatic newline at end.");
std::cout << "STOP\n";

//START
//Can be used as a simple function. Output has automatic newline at end.
//STOP
```

#### Setting Prefix:
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

#### Works like std::cout:
```c++
Log(5) << "It works "            // New line
       << "just like std::cout"  // Still same line
       << std::endl              // New line
       << "and supports std::endl.";

//     It works just like std::cout
//     and supports std::endl.
```

#### Trailing Newlines:
```c++
std::cout << "START\n";
Log(5, '-') << " You don't need \\n (or std::endl) as the last character\n"; 
Log(5, '+') << " But it handles them in case you forget :)" << std::endl;
std::cout << "STOP\n";

//START
//----- You don't need \n or std::endl as the last character
//+++++ But it handles them in case you forget :)
//STOP
```

#### Manipulators and Overloads:
```c++
struct Foo 
{ 
  Foo(string s) : bar("Foo contains '" + s + "'") {}
  std::string bar;
};
std::ostream &operator<<(std::ostream& os, const Foo& foo) 
{
  return os << foo.bar; 
}

// ...

Log("  INFO: ") 
  << "It supports manipulators: " << fixed << setprecision(4) << 1.5 << endl
  << "And std::cout overloaded objects: " << Foo("secret");

//OUTPUT:
//  INFO: It supports manipulators: 1.5000
//  INFO: And std::cout overloaded objects: Foo contains 'secret'
```

======

Please see Test.cpp for detailed usage.

------


### Todo

* Log File Support
  * Currently there is no support for outputting the printed log to a file automatically.
  * It should be easy to set up a static configuration object read by `PrefixLogProxy`, and used to print to a defined log file or stream whenever it writes to `std::cout` internally.
  
* Improve prefixing on newlines in strings
  * Currently newline characters in strings just use `find` and `replace` to add the prefix.
  * Performance can probably be improved by walking the string with a pointer.
