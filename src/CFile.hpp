#ifndef FDRAIIWRAPPER_HPP_
#define FDRAIIWRAPPER_HPP_

#include <cstdio>
#include <stdexcept>
#include <string>

class ErrorOpeningFile : public std::runtime_error {
public:
  ErrorOpeningFile(std::string const &msg) : std::runtime_error(msg) {}
};

class ErrorWritingToFile : public std::runtime_error {
public:
  ErrorWritingToFile(std::string const &msg) : std::runtime_error(msg) {}
};

/**
 * An RAII wrapper for C-style file.
 */
struct CFile {
private:
  FILE *fd;

public:
  CFile(const CFile &) = delete;
  CFile &operator=(const CFile &) = delete;
  CFile(std::string filepath, std::string rw) {
    fd = fopen(filepath.c_str(), rw.c_str());
    if (fd == nullptr)
      throw ErrorOpeningFile(std::string{"File path: '"} + filepath + "'.");
  }
  CFile(CFile &&orig) {
    fd = orig.fd;
    orig.fd = nullptr;
  }
  ~CFile() {
    if (fd != nullptr)
      fclose(fd);
  }

  [[deprecated]] void write(const char *str) {
    if (std::fputs(str, fd) == EOF) {
      throw ErrorWritingToFile(
          "Call to std::fputs returned EOF with string: \"" + std::string{str} +
          "\"\n");
    }
  }

  void write(const std::string str) {
    if (std::fputs(str.c_str(), fd) == EOF) {
      throw ErrorWritingToFile("Call to std::fputs returned EOF\n");
    }
  }

  void write(const char *buffer, std::size_t num_chars) {
    if (num_chars != 0 && std::fwrite(buffer, num_chars, 1, fd) == 0) {
      throw ErrorWritingToFile("Call to std::fputs returned EOF\n");
    }
  }
};

#endif // FDRAIIWRAPPER_HPP_
