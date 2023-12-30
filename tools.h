#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>

namespace jejalyk::tools {
  std::string implode(const std::vector<std::string>& lst,
                      const std::string& delim);

  std::string implode_with_prefix(const std::vector<std::string>& lst,
                                  const std::string& delim,
                                  const std::string& prefix);

  std::string repeat_string(const std::string& s, int n);

  bool is_digit(std::string s);

  void replace_all(std::string& str,
                   const std::string& from,
                   const std::string& to);

  std::string safe_substr(const std::string& str, int start, int count);

  std::vector<std::string> split(std::string s, std::string delimiter);

  std::string trim(const std::string& source);

  template <typename Base, typename T>
  bool instanceof (const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
  }

  template <typename Base, typename T>
  bool instance_of(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
  }
} // namespace jejalyk::tools
#endif // TOOLS_H
