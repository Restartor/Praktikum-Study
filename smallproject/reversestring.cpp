#include <iostream>
#include <algorithm>
#include <string>

int main() {
  std::string str = "!dlroW olleH";
  std::cout << "Original string: " << str << std::endl;

  std::reverse(str.begin(), str.end()); // Reverses the string
  std::cout << "Reversed string: " << str << std::endl;

  return 0;
}