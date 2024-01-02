#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_try_node(Scope* scope, mavka::ast::TryNode* try_node) {
    const auto try_scope = scope->make_proxy();

    const auto body_result = try_scope->compile_body(try_node->body);
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
    catch_scope->put_ignore_variable(try_node->name);
    const auto catch_body_result =
        catch_scope->compile_body(try_node->catch_body);
    if (catch_body_result->error) {
      return catch_body_result;
    }

    std::vector<js::JsNode*> catch_body;
    const auto js_if = new js::JsIfNode();
    js_if->body = new js::JsBody();
    // м_п && м_п instanceof Падіння
    js_if->condition = js::make_raw("м_" + try_node->name + " && " + "м_" +
                                    try_node->name + " instanceof Падіння");
    // м_п = м_п.значення
    js_if->body->nodes.push_back(
        js::make_assign(js::make_id("м_" + try_node->name),
                        js::make_chain("м_" + try_node->name, "значення")));
    catch_body.push_back(js_if);
    for (const auto catch_body_js_node : catch_body_result->js_body->nodes) {
      catch_body.push_back(catch_body_js_node);
    }

    const auto js_catch_body = new js::JsBody();
    js_catch_body->nodes = catch_body;

    const auto js_try = new js::JsTryNode();
    js_try->try_body = body_result->js_body;
    js_try->catch_body = js_catch_body;
    js_try->name = "м_" + try_node->name;

    return success(nullptr, js_try);
  }
} // namespace jejalyk::typeinterpreter