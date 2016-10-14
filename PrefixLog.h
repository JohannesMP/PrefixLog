/*******************************************************************************
 * Don't Be a Jerk: The Open Source Software License.
 * Adapted from: https://github.com/evantahler/Dont-be-a-Jerk
 *******************************************************************************
 * _I_ am the software author - JohannesMP on Github.
 * _You_ are the user of this software. You might be a _we_, and that's OK!
 *
 * This is free, open source software. I will never charge you to use,
 * license, or obtain this software. Doing so would make me a jerk.
 *
 * You may use this code (and by "code" I mean _anything_ contained within 
 * this project) for whatever you want. Personal use, Educational use, 
 * Corporate use, and all other uses are OK!
 *
 * I offer no warranty on anything in this project, and you are using it at
 * your own risk, of your own free will. I've tried my best to ensure that 
 * there are no gaping security holes where using this software might erase
 * your hard drive or give your dog diarrhea, but it might happen. I'm sorry. 
 * However, I warned you, so you can't sue me. Suing people over free 
 * software would make you a jerk.
 *
 * If you find bugs, it would be nice if you let me know so I can fix them.
 * You don't have to, but it would be appreciated.
 *
 * Speaking of bugs, I am not obligated to fix anything, nor am I obligated 
 * to add any features for you, though I will consider your suggestions. 
 * Feeling entitled about free software would make you a jerk.
 *
 * If you add a new feature or fix a bug, it would be nice if you contributed 
 * it back to the project, but you don't have to. The repository/site you 
 * obtained this software from should contain a way for you to contact me. 
 * Contributing to open source makes you awesome!
 *
 * If you use this software, you may remove this license, and don't have to
 * give me any credit, but it would be great if you did.
 *
 * Don't be a jerk. Enjoy your free software! :)
*/
#pragma once

#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;

// typedefs
typedef std::string String;

namespace PrefixLog
{
  struct PrefixLogProxy
  {
    String prefix_;      // What to prefix each line in the log with
    String next_prefix_; // Just cached for when we newline
    bool   is_prefixed_; // Has the current line been prefixed?
    int    line_count_;  // How many lines have been printed?

    PrefixLogProxy(const String prefix)
      : prefix_(prefix)
      , next_prefix_("\n" + prefix_)
      , is_prefixed_(false)
      , line_count_(0)
    {}
    
    ~PrefixLogProxy()
    {
      // Handle trailing newline
      if(is_prefixed_) 
        cout << endl;

      // Handle standalone call
      if(line_count_ < 1) 
        cout << prefix_ << endl;
    }

    // Helper function for inserting the prefix
    void HandlePrefix()
    {
      if(!is_prefixed_)
      {
        is_prefixed_ = true;
        line_count_++;
        cout << prefix_;
      }
    }

    // Standard Templetized << operator
    template <typename T>
    PrefixLogProxy &operator<< (const T &obj)
    {
      HandlePrefix();
      std::stringstream stream;
      stream << obj;
      return (*this) << String(stream.str());
    }

    // << operator specifically for c-style strings
    PrefixLogProxy &operator<< (const char *c_str)
    {
      return (*this) << String(c_str);
    }

    // << operator specifically for Strings
    PrefixLogProxy &operator<< (String str)
    {
      HandlePrefix();

      // replace all newlines with prefix, except when trailing
      size_t pos = 0;
      while (true) 
      {
          pos = str.find("\n", pos);
          if(pos == String::npos) 
            break;

          if(pos == str.size()-1)
          {
            is_prefixed_ = false;
            break;
          }

          str.replace(pos, 1, next_prefix_);
          pos += next_prefix_.length();
      }

      cout << str;

      return *this;
    }

    // Function that takes the Proxy, and returns it
    typedef PrefixLogProxy& (*PrefixLogProxyManipulator)(PrefixLogProxy&);

    // Handle manipulators
    PrefixLogProxy& operator<<(PrefixLogProxyManipulator manip)
    {
      HandlePrefix();
      // call the function, and return it's value
      return manip(*this);
    }

    // This is the type of cout
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;
    // This is the function signature of endl
    typedef CoutType& (*StandardEndLine)(CoutType&);

    // Handle << endl
    PrefixLogProxy& operator<<(StandardEndLine manip)
    {
      HandlePrefix();
      is_prefixed_  = false;
      // Call, but don't return.
      manip(cout);
      return *this;
    }
  };

  inline PrefixLogProxy Log(const String& prefix)
  {
    return PrefixLogProxy(prefix);
  }

  inline PrefixLogProxy Log(int indent = 2, unsigned char padding = ' ')
  {
    return PrefixLogProxy(String(indent, padding));
  }
}
