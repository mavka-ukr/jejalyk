parser grammar MavkaParser;

options {
    tokenVocab=MavkaLexer;
}

file: f_program=program EOF;

program: program_element (nl program_element)*;
program_element: module | structure | mockup | diia | if | each | while | try | expr | throw | eval | wait_assign | assign | take | give | nls;

module: 'модуль' (m_name=identifier)? nl (m_body=module_body nl)? nls 'кінець';
module_body: module_body_element (nl module_body_element)*;
module_body_element: module | structure | mockup | diia | if | each | while | try | expr | throw | eval | wait_assign | assign | give | nls;

method_declaration: (md_async='тривала')? (md_static='спец')? md_name=identifier ('<' md_generics=generics '>')? '(' (nls md_params=params? nls) ')' (md_type=type_value)?;

structure: 'структура' s_name=identifier ('<' s_generics=generics '>')? ('є' s_parent=super_identifiers_chain ('<' s_parent_generics=generics '>')?)? nl (s_elements=structure_elements nl)? nls 'кінець';
structure_elements: structure_element (nl structure_element)*;
structure_element: structure_param | nls;
structure_param: (sp_static='спец')? sp_name=identifier sp_type=type_value? ('=' sp_value=param_value)?;

generics: identifier (',' identifier)*;

mockup: mockup_module | mockup_structure | mockup_diia | mockup_subject;
mockup_module: 'макет' 'модуль' mm_name=identifier nl nls (mm_elements=mockup_module_body nl)? nls 'кінець';
mockup_module_body: mockup (nl mockup)*;
mockup_structure: 'макет' 'структура' ms_name=identifier ('<' ms_generics=generics '>')? ('є' ms_parent=super_identifiers_chain ('<' ms_parent_generics=generics '>')?)? nl nls (ms_elements=mockup_structure_body nl)? nls 'кінець';
mockup_structure_body: mockup_structure_body_element (nl mockup_structure_body_element)*;
mockup_structure_body_element: structure_param | method_declaration | nls;
mockup_diia: 'макет' (md_async='тривала')? (md_static='спец')? 'дія' md_name=identifier ('<' md_generics=generics '>')? '(' ( nls md_params=params? nls ) ')' (md_type=type_value)?;
mockup_subject: 'макет' 'субʼєкт' ms_name=identifier ms_type=type_value;

diia: (d_async='тривала')? (d_static='спец')? 'дія' (d_structure=identifier '.')? d_name=identifier ('<' d_generics=generics '>')? '(' ( nls d_params=params? nls ) ')' (d_type=type_value)? nl (d_body=body nl)? nls 'кінець';

if: 'якщо' i_value=expr nl (i_body=body nl)? ((('інакше' i_else_body=body nl)? 'кінець') | ('інакше' i_else_if=if));

each: 'перебрати' (e_iterator=expr | e_fromto=fromto) 'як' (e_key_name=identifier ',')? e_name=identifier? nl (e_body=body nl)? 'кінець';

fromto: fromto_simple | fromto_complex;
fromto_simple: fs_from=fromto_value '..' (fs_to_symbol=fromto_to_symbol)? fs_to=fromto_value;
fromto_complex: fc_from=fromto_value '..' (fc_middle_symbol=fromto_middle_symbol)? fc_middle=fromto_value '..' (fc_to_symbol=fromto_to_symbol)? fc_to=fromto_value;
fromto_value: NUMBER #fromto_number
            | STRING #fromto_string
            | identifier #fromto_id
            | '(' fn_value=expr ')' #fromto_nested;
fromto_middle_symbol: '+' | '-' | '*' | '/' | PERCENT | DIVDIV | POW;
fromto_to_symbol: '!=' | '==' | '>' | '<' | '>=' | '<=';

while: 'поки' w_value=expr nl (w_body=body nl)? 'кінець';

try: 'спробувати' nl t_body=body nl 'зловити' tc_name=identifier? (tc_body=body nl)? 'кінець';

eval: 'js' e_value=value;

take: 'взяти' (tm_relative='.')? tm_elements_chain=identifiers_chain ('як' tm_as=identifier)? #take_module
    | 'взяти файл' tf_name=STRING 'як' tf_as=identifier #take_file
    | 'взяти' tr_url=STRING ('як' tr_as=identifier)? #take_remote;

give: 'дати' give_element (nls ',' nls give_element)*;
give_element: ge_name=identifier ('як' ge_as=identifier)?;

string: STRING | STRING_MULTILINE;

atom: NUMBER #number
    | string #string_value
    | identifier #id
    | c_left=atom nls '.' nls c_right=identifier #chain
    | c_value=atom ('<' call_generics '>')? '(' (c_args=args | c_named_args=named_args)? ')' #call
    | ge_left=atom '[' ge_element=expr ']' #get_element
    | '+' p_value=atom  #positive
    | '-' n_value=atom  #negative
    | DECREMENT pd_value=atom  #pre_decrement
    | INCREMENT pi_value=atom  #pre_increment
    | pd_value=atom DECREMENT #post_decrement
    | pi_value=atom INCREMENT #post_increment
    | '!' n_value=atom  #not
    | '~' bn_value=atom  #bitwise_not
    | '(' nls n_value=expr nls ')' #nested;

value: atom #value_atom
     | a_left=value a_operation=arithmetic_op_mul a_right=value #arithmetic_mul
     | a_left=value a_operation=arithmetic_op_add a_right=value #arithmetic_add
     | b_left=value b_operation=bitwise_op b_right=value #bitwise
     | c_left=value c_operation=comparison_op c_right=value #comparison
     | t_left=value t_operation=test_op t_right=value #test
     ;

call_generics: type_value (',' type_value)*;

array_elements: nls array_element nls (nls ',' nls array_element nls)*;
array_element: ae_value=expr;

dictionary_args: dictionary_arg (',' dictionary_arg)*;
dictionary_arg: nls (da_name_id=identifier | da_name_string=STRING) '=' da_value=expr nls;

expr: 'предок' nls '.' nls cp_id=identifier '(' (cp_args=args | cp_named_args=named_args)? ')' #call_parent
    | value #simple
    | a_left=atom 'як' a_right=atom #as
    | t_value=value nls '?' nls t_positive=expr nls ':' nls t_negative=expr #ternary
    | ('<' a_type=type_value '>')? '[' a_elements=array_elements? ']' #array
    | ('<' d_key_type=type_value ',' d_value_type=type_value '>')? '(' d_args=dictionary_args? ')' #dictionary
    | atom ('та' atom)+ #god
    | 'чекати' w_value=value #wait
    | (f_async='тривала')? '(' f_params=params? ')' f_type=type_value? ':' f_body=expr #function
    | (d_async='тривала')? 'дія' '(' ( nls d_params=params? nls ) ')' (d_type=type_value)? nl (d_body=body nl)? nls 'кінець' #anonymous_diia
    | MML #expr_mml
    ;

throw: 'впасти' t_value=expr;

array_destruction: '[' nls array_destruction_el nls (nls ',' nls array_destruction_el nls)* ']';
array_destruction_el: ade_id=identifier;

object_destruction: '(' object_destruction_el (',' object_destruction_el)* ')';
object_destruction_el: nls ode_id=identifier nls;

assign: assign_simple | assign_by_identifier | assign_by_element | assign_array_destruction | assign_object_destruction;
assign_simple: (as_subject='субʼєкт')? as_identifier=identifier (as_type=type_value)? as_symbol=assign_symbol as_value=expr;
assign_by_identifier: abi_left=super_identifiers_chain '.' abi_identifier=identifier abi_symbol=assign_symbol abi_value=expr;
assign_by_element: abe_left=super_identifiers_chain '[' abe_index=expr ']' abe_symbol=assign_symbol abe_value=expr;
assign_array_destruction: aad_array_destruction=array_destruction '=' aad_value=expr;
assign_object_destruction: aod_object_destruction=object_destruction '=' aod_value=expr;
assign_symbol: 'це' | '=' | ':=' | '+=' | '-=' | '*=' | '/=' | '//=' | '%=' | '**=' | '&=' | '|=' | '<<=' | '>>=' | '^=' | '&&=' | '||=' | '??=';
wait_assign: 'чекати' wa_assign=assign;

identifier: ID | KID;

identifiers_chain: ic_identifier=identifier | ic_left=identifiers_chain '.' ic_right=identifier;
super_identifiers_chain: sic_identifier=identifier
                       | sic_left=super_identifiers_chain nls '.' nls sic_right=identifier
                       | sic_left=super_identifiers_chain '[' nls sic_index=expr nls ']';

type_value: type_value_item (('|' | 'або') type_value_item)*;
type_value_item: tvi_value=identifiers_chain ('<' tvi_generics=type_value_item_generics '>')?;
type_value_item_generics: type_value (',' type_value)*;

args: arg (',' arg)*;
arg: nls (a_spread='...')? a_value=expr nls;
named_args: named_arg (',' named_arg)*;
named_arg: nls na_name=identifier '=' na_value=expr nls;

params: param (nls ',' nls param)* (nls ',' nls p_variadic='...' p_variadic_name=identifier p_variadic_type=type_value?)?
      | p_variadic='...' p_variadic_name=identifier p_variadic_type=type_value?;
param: (p_name=identifier | p_array_destruction=array_destruction | p_object_destruction=object_destruction) p_type=type_value? ('=' p_value=param_value)?;
param_value: NUMBER #param_value_number
           | (STRING | STRING_MULTILINE) #param_value_string
           | identifier #param_value_identifier
           | '(' ')' #param_value_empty_dictionary
           | '[' ']' #param_value_empty_list;

body: body_element_or_return (nl body_element_or_return)*;
body_element_or_return: body_element | return_body_line;
body_element: if | each | while | try | expr | throw | wait_assign | assign | nls;
return_body_line: 'вернути' rbl_value=expr;

arithmetic_op_mul: '*' | '/' | PERCENT | DIVDIV | POW;
arithmetic_op_add: '+' | '-';
bitwise_op: XOR | OR_BW | AND_BW | '<' '<' | '>' '>';
test_op: 'і' | 'або' | '||' | '&&';
comparison_op: '==' | '!=' | '>' | '<' | '>=' | '<=' | 'є' | 'не є' | 'рівно' | 'не рівно' | 'більше' | 'не більше' | 'менше' | 'не менше' | 'містить' | 'не містить';

nl: NL;
nls: nl*;