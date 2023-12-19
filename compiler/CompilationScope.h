#pragma once

#ifndef COMPILATION_SCOPE_H
#define COMPILATION_SCOPE_H

#include <map>
#include <string>

#include "CompilationError.h"
#include "CompilationSubject.h"

namespace jejalyk {
    class CompilationScope {
    public:
        virtual ~CompilationScope() = default;

        CompilationScope* parent = nullptr;
        std::map<std::string, CompilationSubject *> subjects;
        std::map<std::string, std::string> modules;
        std::map<std::string, std::string> debug;
        bool store_debug = false;

        virtual bool has_module(const std::string& name);

        virtual std::string get_module(const std::string& name);

        virtual void set_module(const std::string& name, std::string code);

        virtual std::string put_debug(const std::string& path, const size_t& line, const size_t& column);

        virtual CompilationError* assign(const std::string& name);

        virtual CompilationSubject* get_local(const std::string& name) const;

        virtual bool has_local(const std::string& name) const;

        virtual CompilationSubject* get(const std::string& name) const;

        virtual bool has(const std::string& name) const;

        virtual CompilationScope* root();
    };


    class CompilationMicroScope final : public CompilationScope {
    public:
        virtual CompilationError* assign(const std::string& name) override;

        virtual CompilationSubject* get_local(const std::string& name) const override;

        virtual bool has_local(const std::string& name) const override;

        virtual CompilationSubject* get(const std::string& name) const override;

        virtual bool has(const std::string& name) const override;

        virtual CompilationScope* root() override;
    };
}
#endif //COMPILATION_SCOPE_H
