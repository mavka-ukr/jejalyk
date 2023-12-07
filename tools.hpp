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

    template<typename Base, typename T>
    inline bool instanceof(const T* ptr) {
        return dynamic_cast<const Base *>(ptr) != nullptr;
    }
}
