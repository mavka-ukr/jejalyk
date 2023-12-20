#ifndef NEWCOMPILER_H
#define NEWCOMPILER_H

#include <map>
#include <string>
#include <vector>

namespace newcompiler {
  class Options;
  class State;
  class Error;
  class Result;
  class Scope;
  class Subject;
  class Object;

  class Options {
   public:
  };

  class State {
   public:
    Options* options;
  };

  class Error {
   public:
    std::string message;
  };

  class Result {
   public:
    Error* error;
    Subject* subject;
    std::string value;
  };

  class Scope {
   public:
    State* state;
    std::map<std::string, Subject*> subjects;

    Result* define(std::string name, Subject* subject, Scope* scope);
    Result* assign(std::string name, Subject* subject, Scope* scope);
    Result* get(std::string name, Scope* scope);
  };

  class Subject {
   public:
    std::vector<Object*> types;

    Result* get(std::string name, Scope* scope);
    Result* set(std::string name, Subject* value, Scope* scope);
    Result* call(std::vector<Subject*> args, Scope* scope);
    Result* call_named(std::map<std::string, Subject*> args, Scope* scope);
    Result* get_element(Subject* index, Scope* scope);
    Result* set_element(Subject* index, Subject* value, Scope* scope);
    Result* plus(Subject* value, Scope* scope);
    Result* minus(Subject* value, Scope* scope);
    Result* multiply(Subject* value, Scope* scope);
    Result* divide(Subject* value, Scope* scope);
  };

  class Object {
   public:
    static constexpr int OBJECT = 0;
    static constexpr int DIIA = 1;
    static constexpr int STRUCTURE = 2;

    int type = OBJECT;
  };
}  // namespace newcompiler

#endif  // NEWCOMPILER_H
