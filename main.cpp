#include <functional>
#include <iostream>

// Memory error 1 - Create dangling reference
// Here we create a lambda that captures the variable `a` by reference,
// and return this lambda from the function. Once create_dangling returns, `a` goes out of scope, but the lambda still holds a reference to it. Later, when we invoke the lambda in the main function, we are trying to use a reference to a variable that has already gone out of scope.
std::function<int()> create_dangling()
{
  int a = 5;

  std::function<int()> dangling_lambda = [&a](){ return a; };

  return dangling_lambda;
}

// Memory error 2 - Simple leak
// We allocate memory on the heap which we never clean up
int* leak_memory()
{
  int* b = new int(5);
  return b;
}

int main()
{
  auto foo = create_dangling();
  std::cout << "a: " << foo() << std::endl;

  int* b = leak_memory();
  std::cout << "b: " << *b << std::endl;
}
