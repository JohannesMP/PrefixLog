# PrefixLog
A simple debug log for c++ with a focus on usability.

It prefixes any text printed, while still behaving just like `std::cout`.

------

#### Basic Usage:
```c++
Log("***| ") << "This Log prefixes what it prints,\neven if more than one line.";
/* OUTPUT:
***| This Log prefixes what it prints,
***| even if more than one line.
*/
```

#### Insertion Operators:
```c++
Log(5) << " It has "<< "insertion operator" << " support" 
  << endl << " which works with std::endl.";
/* OUTPUT:
     It has insertion operator support
     which works with std::endl.
*/
```

#### Trailing Newlines:
```c++
Log(5, '_') << " You don't need \\n or std::endl as the last character\n"; 
Log(5, '_') << " But it handles them in case you forget :)" << endl;
/* OUTPUT:
_____ You don't need \n or std::endl as the last character
_____ But it handles them in case you forget :)
*/
```

#### Manipulators and Overloads:
```c++
struct Foo 
{ 
  Foo(string s) : text("Foo contains '" + s + "'") {}
  string text;
};
ostream &operator<<(ostream& os, const Foo& foo) 
{
  return os << foo.text; 
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

------

Please see Test.cpp for detailed usage.
