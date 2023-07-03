#include "tptlog/output.h"

namespace tptlog {

void FileOutput::Serialize(const string& content) {
  printf("%s\n", content.c_str());
  // TODO:
}

void FileOutput::Flush() {
}

}  // namespace tptlog