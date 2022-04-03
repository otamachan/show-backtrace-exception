#include <execinfo.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <cxxabi.h>
#include <cstdlib>

#include <stdio.h>
#include <signal.h>
#include <dlfcn.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

#include <sblz/sblz.h>

extern "C" {
static void show_backtrace() {
  unw_cursor_t cursor;
  unw_context_t context;
  unw_getcontext(&context);
  unw_init_local(&cursor, &context);
  int count = 0;
  do {
    unw_word_t offset, pc;
    unw_get_reg(&cursor, UNW_REG_IP, &pc);
    char mangled_symbol[256];
    mangled_symbol[0] = '\0';
    (void)unw_get_proc_name(&cursor, mangled_symbol, sizeof(mangled_symbol), &offset);
    char demangled_symbol[256];
    bool ok = sblz::itanium::Demangle(mangled_symbol, demangled_symbol, sizeof(demangled_symbol));
    Dl_info info;
    dladdr((void*)pc, &info);
    fprintf(stderr, "backtrace [%d] %s(%s+0x%lx) [%p]\n",
	    count,
	    info.dli_fname,
	    ok ? demangled_symbol : mangled_symbol,
	    offset,
	    (void*)pc
	    );
    count++;
  } while (unw_step(&cursor) > 0);
}
#if 0
void* __cxa_allocate_exception(size_t thrown_size) {
  void* p = malloc(thrown_size * 3);
  if(p == NULL) {
    printf("Could not allocate memory\n");
    exit(0);
  }
  show_backtrace();
  return p;
}
#endif
static void signal_handler(int signo __attribute__((unused))) {
  show_backtrace();
}

__attribute__((constructor)) void install_signal_handler(void) {
  struct sigaction sa;
  sa.sa_handler = signal_handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGABRT, &sa, NULL)) {
    printf("Install SIGABRT\n");
  }
}

}
