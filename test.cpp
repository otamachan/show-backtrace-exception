#include <iostream>
#include <vector>

int test() {
  std::cout << "hello" << std::endl;
  std::vector<int> a;
  std::cout << a.at(2) << std::endl;
  return a.at(1);
}

int main() {
  return test();
}
