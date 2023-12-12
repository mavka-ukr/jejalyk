#pragma once

namespace jejalyk::tools {
    inline std::string implode(const std::vector<std::string>& lst, const std::string& delim) {
        std::string ret;
        for (const auto& s: lst) {
            if (!ret.empty()) {
                ret += delim;
            }
            ret += s;
        }
        return ret;
    }

    inline std::string implode_with_prefix(const std::vector<std::string>& lst,
                                           const std::string& delim,
                                           const std::string& prefix) {
        std::string ret;
        for (const auto& s: lst) {
            if (!ret.empty()) {
                ret += delim;
            }
            for (const auto& p: prefix) {
                ret += p;
            }
            ret += s;
        }
        return ret;
    }

    inline std::string repeat_string(const std::string& s, const int n) {
        std::string ret;
        for (int i = 0; i < n; i++) {
            ret += s;
        }
        return ret;
    }

    inline bool is_digit(std::string s) {
        return s == "0" || s == "1" || s == "2" || s == "3" || s == "4" ||
               s == "5" || s == "6" || s == "7" || s == "8" || s == "9";
    }

    inline void replace_all(std::string& str, const std::string& from, const std::string& to) {
        if (from.empty())
            return;
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

    inline std::string safe_substr(const std::string& str, size_t start, size_t count) {
        if (start < 0) {
            start = 0;
        }
        if (count < 0) {
            count = 0;
        }
        if (start + count > str.length()) {
            count = str.length() - start;
        }
        return str.substr(start, count);
    }

    template<typename Base, typename T>
    bool instanceof(const T* ptr) {
        return dynamic_cast<const Base *>(ptr) != nullptr;
    }
}
