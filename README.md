# PrefixLog
A simple debug log for c++ with a focus on usability.

It prefixes any text printed, while still behaving just like `std::cout`.

======

#### Basic Usage:
```c++
std::cout << "START\n";
Log("***| ") << "This Log adds a prefix\nto every line \n and an automatic newline when done.";
std::cout << "STOP\n";
/* OUTPUT:
START
***| This Log adds a prefix
***| to every line
***| and an automatic newline when done.
STOP
*/
```

#### Insertion Operators:
```c++
Log(5) << "It supports " 
       << "insertion operators"  // still same line
       << std::endl              // new line
       << "and std::endl";
/* OUTPUT:
     It supports insertion operators
     and std::endl.
*/
```

#### Trailing Newlines:
```c++
std::cout << "START\n";
Log(5, '_') << " You don't need \\n (or std::endl) as the last character\n"; 
Log(5, '_') << " But it handles them in case you forget :)" << std::endl;
std::cout << "STOP\n";
/* OUTPUT:
START
_____ You don't need \n or std::endl as the last character
_____ But it handles them in case you forget :)
STOP
*/
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
  << "It works with manipulators: " << fixed << setprecision(4) << 1.5 << endl
  << "And std::cout overloaded objects: " << Foo("secret");
/* OUTPUT:
  INFO: It works with manipulators: 1.5000
  INFO: And std::cout overloaded objects: Foo contains 'secret'
*/
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
