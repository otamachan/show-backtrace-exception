#include <execinfo.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <cxxabi.h>
#include <cstdlib>

extern "C" {
void* __cxa_allocate_exception(size_t thrown_size) {
  void* p = malloc(thrown_size);
  if(p == NULL) {
    printf("Could not allocate memory\n");
    exit(0);
  }
  std::array<void*, 24> stack;
  size_t size = backtrace(stack.data(), 24);
  backtrace_symbols_fd(stack.data(), size, STDOUT_FILENO);
  return p;
}
}
