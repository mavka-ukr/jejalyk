#include "CompilationScope.h"

namespace jejalyk {
    bool CompilationScope::has_module(const std::string& name) {
        return root()->modules.contains(name);
    }

    std::string CompilationScope::get_module(const std::string& name) {
        return root()->modules.find(name)->second;
    }

    void CompilationScope::set_module(const std::string& name, std::string code) {
        root()->modules.insert_or_assign(name, code);
    }

    std::string CompilationScope::put_debug(const std::string& path, const size_t& line, const size_t& column) {
        if (!root()->store_debug) {
            return "";
        }
        const auto debug_id = std::to_string(root()->debug.size());
        const auto debug_name = "DI" + debug_id;
        root()->debug[debug_name] = "\"" + path + ":" + std::to_string(line) + ":" + std::to_string(column) + "\"";
        return debug_name;
    }

    CompilationError* CompilationScope::assign(const std::string& name) {
        subjects.insert_or_assign(name, new CompilationSubject());
        return nullptr;
    }

    CompilationSubject* CompilationScope::get_local(const std::string& name) const {
        const auto subject_it = subjects.find(name);
        if (subject_it != subjects.end()) {
            return subject_it->second;
        }
        return nullptr;
    }

    bool CompilationScope::has_local(const std::string& name) const {
        const auto subject_it = subjects.find(name);
        if (subject_it != subjects.end()) {
            return true;
        }
        return false;
    }

    CompilationSubject* CompilationScope::get(const std::string& name) const {
        if (const auto subject = get_local(name)) {
            return subject;
        }
        if (parent) {
            return parent->get(name);
        }
        return nullptr;
    }

    bool CompilationScope::has(const std::string& name) const {
        if (has_local(name)) {
            return true;
        }
        if (parent) {
            return parent->has(name);
        }
        return false;
    }

    CompilationScope* CompilationScope::root() {
        if (parent) {
            return parent->root();
        }
        return this;
    }

    CompilationError* CompilationMicroScope::assign(const std::string& name) {
        return parent->assign(name);
    }

    CompilationSubject* CompilationMicroScope::get(const std::string& name) const {
        return parent->get(name);
    }


    CompilationSubject* CompilationMicroScope::get_local(const std::string& name) const {
        return parent->get_local(name);
    }

    bool CompilationMicroScope::has_local(const std::string& name) const {
        return parent->has_local(name);
    }

    bool CompilationMicroScope::has(const std::string& name) const {
        return parent->has(name);
    }

    CompilationScope* CompilationMicroScope::root() {
        return parent->root();
    }
}
