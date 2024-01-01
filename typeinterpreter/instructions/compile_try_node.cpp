#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_try_node(Scope* scope, mavka::ast::TryNode* try_node) {
    const auto body_result = scope->compile_body(try_node->body);
    if (body_result->error) {
      return body_result;
    }

    const auto object_structure_subject = scope->get_root_object();
    const auto object_instance_result =
        object_structure_subject->create_instance(scope, {});
    if (object_instance_result->error) {
      return object_instance_result;
    }

    const auto catch_scope = scope->make_child();
    catch_scope->is_async = scope->is_async;
    catch_scope->set_local(try_node->name, object_instance_result->value);
    const auto catch_body_result =
        catch_scope->compile_body(try_node->catch_body);
    if (catch_body_result->error) {
      return catch_body_result;
    }

    const auto js_try = new js::JsTryNode();
    js_try->try_body = body_result->js_body;
    js_try->catch_body = catch_body_result->js_body;
    js_try->name = try_node->name;

    return success(nullptr, js_try);
  }
} // namespace jejalyk::typeinterpreter