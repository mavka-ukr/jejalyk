#ifndef JS_H
#define JS_H

#include <string>
#include <vector>

namespace jejalyk::js {
  class JsNode {
   public:
    virtual std::string toString();
    virtual ~JsNode() = default;
  };

  class JsBody {
   public:
    std::vector<JsNode*> nodes;
  };
}  // namespace jejalyk::js

#endif  // JS_H
