#pragma once

#include <exception>

class MyException: public std::exception
{
  virtual const char* what() const throw()
  {
      return "Exception happened\n";
  }
} myexception;
