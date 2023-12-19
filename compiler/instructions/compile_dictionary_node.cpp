#include "compile_dictionary_node.h"

#include "compile_node.h"
#include "../compile.h"
#include "../../tools.h"

namespace jejalyk {
    NodeCompilationResult* compile_dictionary_node(const mavka::ast::DictionaryNode* dictionary_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_elements;
        for (const auto& element: dictionary_node->elements) {
            const auto value = compile_node(element->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            compiled_elements.push_back("[\"" + element->key + "\"," + value->result + "]");
        }
        node_compilation_result->result = "new Map([" + tools::implode(compiled_elements, ",") + "])";
        return node_compilation_result;
    }
}
