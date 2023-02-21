#include <stdlib.h>
#include <string.h>
#include <string>

#if defined(_MSC_VER)
#include <direct.h>
#define getcwd _getcwd
#elif defined(__GNUC__)
#include <unistd.h>
#endif

std::string get_current_directory() {
  char *buffer;
  if ((buffer = getcwd(NULL, 0)) == NULL) {
    return "Couldn't find directory.";
  } else {
    std::string answer = buffer;
    free(buffer);
    return answer;
  }
}