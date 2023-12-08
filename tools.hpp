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

    template<typename Base, typename T>
    bool instanceof(const T* ptr) {
        return dynamic_cast<const Base *>(ptr) != nullptr;
    }
}
