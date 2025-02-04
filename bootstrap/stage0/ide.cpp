#include "ide.h"
namespace Jakt {
namespace ide {
ErrorOr<ide::Usage> get_enum_variant_usage_from_type_id_and_name(const NonnullRefPtr<types::CheckedProgram> program,const types::TypeId type_id,const String name) {
{
{
JaktInternal::ArrayIterator<types::CheckedEnum> _magic = ((((((program)->get_module(((type_id).module))))->enums)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnum> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnum enum_ = (_magic_value.value());
{
if ((!(((((enum_).type_id)).equals(type_id))))){
continue;
}
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if ((((variant).name()) == name)){
const JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> variants = TRY((ide::enum_variant_fields(program,variant)));
const JaktInternal::Optional<types::NumberConstant> number_constant = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, ErrorOr<ide::Usage>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();String const& name = __jakt_match_value.name;
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->to_number_constant(program)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
));
const utility::Span span = ((variant).span());
return ( ide::Usage { typename ide::Usage::EnumVariant(span,name,type_id,variants,number_constant) } );
}
}

}
}

utility::panic(String("unreachable: should have found variant"));
}

}
}

utility::panic(String("unreachable: should have found variant"));
}
}

ErrorOr<JaktInternal::Array<String>> completions_for_type_id(const NonnullRefPtr<types::CheckedProgram> program,const types::TypeId type_id) {
{
JaktInternal::Array<String> output = (TRY((Array<String>::create_with({}))));
const NonnullRefPtr<types::Type> ty = ((program)->get_type(type_id));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Array<String>>>{
auto&& __jakt_match_variant = *ty;
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
const types::CheckedEnum enum_ = ((program)->get_enum(enum_id));
const NonnullRefPtr<types::Scope> scope = TRY((((program)->get_scope(((enum_).scope_id)))));
{
JaktInternal::ArrayIterator<String> _magic = ((TRY((((((scope)->functions)).keys())))).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String function_name = (_magic_value.value());
{
const types::FunctionId function_id = (((((scope)->functions)).get(function_name)).value());
const NonnullRefPtr<types::CheckedFunction> checked_function = ((program)->get_function(function_id));
if (((((((checked_function)->params)).first())).has_value())){
const types::CheckedParameter param = (((((checked_function)->params)).first()).value());
if ((((((param).variable)).name) == String("this"))){
String full_call = ((checked_function)->name);
bool first = true;
(full_call += String("("));
JaktInternal::ArrayIterator<types::CheckedParameter> iter = ((((checked_function)->params)).iterator());
const JaktInternal::Optional<types::CheckedParameter> dummy = ((iter).next());
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = iter;
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(full_call += String(", "));
}
else {
(first = false);
}

(full_call += ((((param).variable)).name));
}

}
}

(full_call += String(")"));
TRY((((output).push(full_call))));
}
}
else {
TRY((((output).push(TRY((String::formatted(String("{}()"),((checked_function)->name))))))));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
const types::CheckedStruct structure = ((program)->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
const types::CheckedVariable field_var = ((program)->get_variable(field));
TRY((((output).push(((field_var).name)))));
}

}
}

const NonnullRefPtr<types::Scope> scope = TRY((((program)->get_scope(((structure).scope_id)))));
{
JaktInternal::ArrayIterator<String> _magic = ((TRY((((((scope)->functions)).keys())))).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String function_name = (_magic_value.value());
{
const types::FunctionId function_id = (((((scope)->functions)).get(function_name)).value());
const NonnullRefPtr<types::CheckedFunction> checked_function = ((program)->get_function(function_id));
if (((((((checked_function)->params)).first())).has_value())){
const types::CheckedParameter param = (((((checked_function)->params)).first()).value());
if ((((((param).variable)).name) == String("this"))){
String full_call = ((checked_function)->name);
bool first = true;
(full_call += String("("));
JaktInternal::ArrayIterator<types::CheckedParameter> iter = ((((checked_function)->params)).iterator());
const JaktInternal::Optional<types::CheckedParameter> dummy = ((iter).next());
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = iter;
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(full_call += String(", "));
}
else {
(first = false);
}

(full_call += ((((param).variable)).name));
}

}
}

(full_call += String(")"));
TRY((((output).push(full_call))));
}
}
else {
TRY((((output).push(TRY((String::formatted(String("{}()"),((checked_function)->name))))))));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
{
const types::CheckedStruct structure = ((program)->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
const types::CheckedVariable field_var = ((program)->get_variable(field));
TRY((((output).push(((field_var).name)))));
}

}
}

const NonnullRefPtr<types::Scope> scope = TRY((((program)->get_scope(((structure).scope_id)))));
{
JaktInternal::ArrayIterator<String> _magic = ((TRY((((((scope)->functions)).keys())))).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String function_name = (_magic_value.value());
{
const types::FunctionId function_id = (((((scope)->functions)).get(function_name)).value());
const NonnullRefPtr<types::CheckedFunction> checked_function = ((program)->get_function(function_id));
if (((((((checked_function)->params)).first())).has_value())){
const types::CheckedParameter param = (((((checked_function)->params)).first()).value());
if ((((((param).variable)).name) == String("this"))){
String full_call = ((checked_function)->name);
bool first = true;
(full_call += String("("));
JaktInternal::ArrayIterator<types::CheckedParameter> iter = ((((checked_function)->params)).iterator());
const JaktInternal::Optional<types::CheckedParameter> dummy = ((iter).next());
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = iter;
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(full_call += String(", "));
}
else {
(first = false);
}

(full_call += ((((param).variable)).name));
}

}
}

(full_call += String(")"));
TRY((((output).push(full_call))));
}
}
else {
TRY((((output).push(TRY((String::formatted(String("{}()"),((checked_function)->name))))))));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
return (output);
}
}

ErrorOr<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>> enum_variant_fields(const NonnullRefPtr<types::CheckedProgram> program,const types::CheckedEnumVariant checked_enum_variant) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>, ErrorOr<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>>>{
auto&& __jakt_match_variant = checked_enum_variant;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();JaktInternal::Array<types::VarId> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>> __jakt_var_501; {
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> output = (TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
const types::CheckedVariable variable = ((program)->get_variable(field));
const JaktInternal::Optional<String> var_name = static_cast<JaktInternal::Optional<String>>(((variable).name));
const JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId> o = (Tuple{var_name, ((variable).type_id)});
TRY((((output).push(o))));
}

}
}

__jakt_var_501 = output; goto __jakt_label_460;

}
__jakt_label_460:; __jakt_var_501.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>> __jakt_var_502; {
const JaktInternal::Optional<String> string_none = JaktInternal::OptionalNone();
__jakt_var_502 = (TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({(Tuple{string_none, type_id})})))); goto __jakt_label_461;

}
__jakt_label_461:; __jakt_var_502.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<String> get_enum_variant_signature_from_type_id_and_name(const NonnullRefPtr<types::CheckedProgram> program,const types::TypeId type_id,const String name) {
{
const NonnullRefPtr<types::Module> mod = ((((program)->modules))[((((type_id).module)).id)]);
{
JaktInternal::ArrayIterator<types::CheckedEnum> _magic = ((((mod)->enums)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnum> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnum enum_ = (_magic_value.value());
{
if (((((enum_).type_id)).equals(type_id))){
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& v_name = __jakt_match_value.name;
{
if ((v_name == name)){
const JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> params = TRY((ide::enum_variant_fields(program,variant)));
const JaktInternal::Optional<types::NumberConstant> none = JaktInternal::OptionalNone();
return (TRY((ide::get_enum_variant_signature(program,name,type_id,params,none))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& v_name = __jakt_match_value.name;
{
if ((v_name == name)){
const JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> params = TRY((ide::enum_variant_fields(program,variant)));
const JaktInternal::Optional<types::NumberConstant> none = JaktInternal::OptionalNone();
return (TRY((ide::get_enum_variant_signature(program,name,type_id,params,none))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();String const& v_name = __jakt_match_value.name;
{
if ((v_name == name)){
const JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> params = TRY((ide::enum_variant_fields(program,variant)));
const JaktInternal::Optional<types::NumberConstant> value = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, ErrorOr<String>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_503; {
__jakt_var_503 = ((expr)->to_number_constant(program)); goto __jakt_label_462;

}
__jakt_label_462:; __jakt_var_503.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_504; {
const JaktInternal::Optional<types::NumberConstant> none = JaktInternal::OptionalNone();
__jakt_var_504 = none; goto __jakt_label_463;

}
__jakt_label_463:; __jakt_var_504.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
return (TRY((ide::get_enum_variant_signature(program,name,type_id,params,value))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& v_name = __jakt_match_value.name;
{
if ((v_name == name)){
const JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> params = TRY((ide::enum_variant_fields(program,variant)));
const JaktInternal::Optional<types::NumberConstant> none = JaktInternal::OptionalNone();
return (TRY((ide::get_enum_variant_signature(program,name,type_id,params,none))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}

}
}

}
}

}
}

return (String(""));
}
}

ErrorOr<String> get_type_signature(const NonnullRefPtr<types::CheckedProgram> program,const types::TypeId type_id) {
{
const types::StructId array_struct_id = TRY((((program)->find_struct_in_prelude(String("Array")))));
const types::StructId dictionary_struct_id = TRY((((program)->find_struct_in_prelude(String("Dictionary")))));
const types::StructId optional_struct_id = TRY((((program)->find_struct_in_prelude(String("Optional")))));
const types::StructId range_struct_id = TRY((((program)->find_struct_in_prelude(String("Range")))));
const types::StructId set_struct_id = TRY((((program)->find_struct_in_prelude(String("Set")))));
const types::StructId tuple_struct_id = TRY((((program)->find_struct_in_prelude(String("Tuple")))));
const types::StructId weak_ptr_struct_id = TRY((((program)->find_struct_in_prelude(String("WeakPtr")))));
const NonnullRefPtr<types::Type> type = ((program)->get_type(type_id));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Never>();
return JaktInternal::ExplicitValue(String("never"));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Void>();
return JaktInternal::ExplicitValue(String("void"));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Bool>();
return JaktInternal::ExplicitValue(String("bool"));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U8>();
return JaktInternal::ExplicitValue(String("u8"));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U16>();
return JaktInternal::ExplicitValue(String("u16"));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U32>();
return JaktInternal::ExplicitValue(String("u32"));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U64>();
return JaktInternal::ExplicitValue(String("u64"));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I8>();
return JaktInternal::ExplicitValue(String("i8"));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I16>();
return JaktInternal::ExplicitValue(String("i16"));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I32>();
return JaktInternal::ExplicitValue(String("i32"));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I64>();
return JaktInternal::ExplicitValue(String("i64"));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::F32>();
return JaktInternal::ExplicitValue(String("f32"));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::F64>();
return JaktInternal::ExplicitValue(String("f64"));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Usize>();
return JaktInternal::ExplicitValue(String("usize"));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::JaktString>();
return JaktInternal::ExplicitValue(String("String"));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CInt>();
return JaktInternal::ExplicitValue(String("c_int"));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CChar>();
return JaktInternal::ExplicitValue(String("c_char"));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
String const& name = __jakt_match_value.value;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Unknown>();
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::Array<types::TypeId> const& params = __jakt_match_value.params;
types::TypeId const& return_type_id = __jakt_match_value.return_type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_505; {
JaktInternal::Array<String> param_names = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId x = (_magic_value.value());
{
TRY((((param_names).push(TRY((((program)->type_name(x))))))));
}

}
}

const String return_type = TRY((((program)->type_name(return_type_id))));
__jakt_var_505 = TRY((String::formatted(String("function({}) -> {}"),utility::join(param_names,String(", ")),return_type))); goto __jakt_label_464;

}
__jakt_label_464:; __jakt_var_505.release_value(); }));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((String("raw ") + TRY((ide::get_type_signature(program,type_id)))));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_506; {
const types::CheckedEnum enum_ = ((program)->get_enum(id));
__jakt_var_506 = ((JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((enum_).is_boxed));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("boxed "));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
 + String("enum ")) + ((enum_).name)); goto __jakt_label_465;

}
__jakt_label_465:; __jakt_var_506.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_507; {
const types::CheckedStruct struct_ = ((program)->get_struct(id));
__jakt_var_507 = (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();return JaktInternal::ExplicitValue(String("class "));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();return JaktInternal::ExplicitValue(String("struct "));
};/*case end*/
default: {
{
utility::panic(String("unreachable: should've been struct"));
}
};/*case end*/
}/*switch end*/
}()
)) + ((struct_).name)); goto __jakt_label_466;

}
__jakt_label_466:; __jakt_var_507.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_508; {
const types::CheckedStruct record = ((program)->get_struct(id));
String output = ((record).name);
(output += String("<"));
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_508 = (output + String(">")); goto __jakt_label_467;

}
__jakt_label_467:; __jakt_var_508.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_509; {
const types::CheckedEnum enum_ = ((program)->get_enum(id));
String output = String("");
if (((enum_).is_boxed)){
(output += String("boxed "));
}
(output += String("enum "));
(output += ((enum_).name));
(output += String("<"));
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_509 = (output + String(">")); goto __jakt_label_468;

}
__jakt_label_468:; __jakt_var_509.release_value(); }));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_510; {
if (((id).equals(array_struct_id))){
if (((args).is_empty())){
return (String("[]"));
}
return (TRY((String::formatted(String("[{}]"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)]))))))));
}
if (((id).equals(dictionary_struct_id))){
if ((((args).size()) < static_cast<size_t>(2ULL))){
return (String("[:]"));
}
return (TRY((String::formatted(String("[{}: {}]"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(1LL)]))))))));
}
if (((id).equals(optional_struct_id))){
if (((args).is_empty())){
return (String(""));
}
return (TRY((String::formatted(String("{}?"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)]))))))));
}
if (((id).equals(range_struct_id))){
if (((args).is_empty())){
return (String(""));
}
return (TRY((String::formatted(String("{}..{}"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))),TRY((((program)->type_name(((args)[static_cast<i64>(0LL)])))))))));
}
if (((id).equals(set_struct_id))){
if (((args).is_empty())){
return (String(""));
}
return (TRY((String::formatted(String("{{{}}}"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)]))))))));
}
if (((id).equals(tuple_struct_id))){
String output = String("(");
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
return ((output + String(")")));
}
if (((id).equals(weak_ptr_struct_id))){
if (((args).is_empty())){
return (String(""));
}
return (TRY((String::formatted(String("weak {}?"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)]))))))));
}
const types::CheckedStruct record = ((program)->get_struct(id));
String output = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();return JaktInternal::ExplicitValue(String("class "));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();return JaktInternal::ExplicitValue(String("struct "));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
utility::panic(String("unreachable: can't be an enum"));
}
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
utility::panic(String("unreachable: can't be an enum"));
}
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::RecordType::Garbage>();
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
(output += ((record).name));
(output += String("<"));
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_510 = (output + String(">")); goto __jakt_label_469;

}
__jakt_label_469:; __jakt_var_510.release_value(); }));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("&{}"),TRY((((program)->type_name(type_id))))))));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("&mut {}"),TRY((((program)->type_name(type_id))))))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_scope(const NonnullRefPtr<types::CheckedProgram> program,const NonnullRefPtr<types::Scope> scope,const utility::Span span) {
{
{
JaktInternal::DictionaryIterator<String,types::VarId> _magic = ((((scope)->vars)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::VarId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::VarId> scope_var = (_magic_value.value());
{
const types::CheckedVariable var = ((program)->get_variable(((scope_var).get<1>())));
if (((((var).definition_span)).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((var).type_id)) } ));
}
}

}
}

{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> function_id = (_magic_value.value());
{
const NonnullRefPtr<types::CheckedFunction> checked_function = ((program)->get_function(((function_id).get<1>())));
const JaktInternal::Optional<ide::Usage> usage = TRY((ide::find_span_in_function(program,checked_function,span)));
if (((usage).has_value())){
return ((usage.value()));
}
}

}
}

{
JaktInternal::DictionaryIterator<String,types::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::StructId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::StructId> struct_id = (_magic_value.value());
{
const types::CheckedStruct checked_struct = ((program)->get_struct(((struct_id).get<1>())));
const JaktInternal::Optional<ide::Usage> usage = TRY((ide::find_span_in_struct(program,checked_struct,span)));
if (((usage).has_value())){
return ((usage.value()));
}
}

}
}

{
JaktInternal::DictionaryIterator<String,types::EnumId> _magic = ((((scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::EnumId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::EnumId> enum_id = (_magic_value.value());
{
const types::CheckedEnum checked_enum = ((program)->get_enum(((enum_id).get<1>())));
const JaktInternal::Optional<ide::Usage> usage = TRY((ide::find_span_in_enum(program,checked_enum,span)));
if (((usage).has_value())){
return ((usage.value()));
}
}

}
}

{
JaktInternal::ArrayIterator<types::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<types::ScopeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ScopeId child = (_magic_value.value());
{
const NonnullRefPtr<types::Scope> scope = TRY((((program)->get_scope(child))));
const JaktInternal::Optional<ide::Usage> usage = TRY((ide::find_span_in_scope(program,scope,span)));
if (((usage).has_value())){
return ((usage.value()));
}
}

}
}

return (JaktInternal::OptionalNone());
}
}

ErrorOr<String> get_constructor_signature(const NonnullRefPtr<types::CheckedProgram> program,const types::FunctionId function_id) {
{
const NonnullRefPtr<types::CheckedFunction> checked_function = ((program)->get_function(function_id));
const types::TypeId type_id = ((checked_function)->return_type_id);
const NonnullRefPtr<types::Module> mod = ((((program)->modules))[((((type_id).module)).id)]);
{
JaktInternal::ArrayIterator<types::CheckedStruct> _magic = ((((mod)->structures)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedStruct> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedStruct struct_ = (_magic_value.value());
{
if (((((struct_).type_id)).equals(type_id))){
String output = TRY((ide::get_type_signature(program,type_id)));
(output += String("("));
bool first = true;
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(output += String(", "));
}

const types::CheckedVariable variable = ((program)->get_variable(field));
if (((variable).is_mutable)){
(output += String("mut "));
}
(output += TRY((String::formatted(String("{}: {}"),((variable).name),TRY((((program)->type_name(((variable).type_id)))))))));
}

}
}

(output += String(")"));
return (output);
}
}

}
}

return (String(""));
}
}

ErrorOr<JaktInternal::Array<String>> find_dot_completions(const NonnullRefPtr<types::CheckedProgram> program,const utility::Span span) {
{
const JaktInternal::Optional<ide::Usage> result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<String>, ErrorOr<JaktInternal::Array<String>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::Variable>();types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<String>> __jakt_var_511; {
__jakt_var_511 = TRY((ide::completions_for_type_id(program,type_id))); goto __jakt_label_470;

}
__jakt_label_470:; __jakt_var_511.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Call>();
types::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<String>> __jakt_var_512; {
const types::TypeId result_type_id = ((((program)->get_function(function_id)))->return_type_id);
__jakt_var_512 = TRY((ide::completions_for_type_id(program,result_type_id))); goto __jakt_label_471;

}
__jakt_label_471:; __jakt_var_512.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
)));
}
else {
return ((TRY((Array<String>::create_with({})))));
}

}
}

ErrorOr<utility::Span> find_definition_in_program(const NonnullRefPtr<types::CheckedProgram> program,const utility::Span span) {
{
const JaktInternal::Optional<ide::Usage> result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::Variable>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Call>();
types::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_function(function_id)))->name_span));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Typename>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::NameSet>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::EnumVariant>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
else {
return (span);
}

}
}

ErrorOr<String> get_var_signature(const NonnullRefPtr<types::CheckedProgram> program,const String name,const types::TypeId var_type_id,const ide::Mutability mutability,const ide::VarType var_type,const ide::VarVisibility visibility,const JaktInternal::Optional<types::TypeId> struct_type_id) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = var_type;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::VarType::Variable>();
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_513; {
const String mut_string = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = mutability;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Mutability::Mutable>();
return JaktInternal::ExplicitValue(String("mut"));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Mutability::Immutable>();
return JaktInternal::ExplicitValue(String("let"));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
));
const String type_name = TRY((ide::get_type_signature(program,var_type_id)));
__jakt_var_513 = TRY((String::formatted(String("{} {}: {}"),mut_string,name,type_name))); goto __jakt_label_472;

}
__jakt_label_472:; __jakt_var_513.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::VarType::Field>();
{
String record_string = String("");
if (((struct_type_id).has_value())){
(record_string = TRY((ide::get_type_signature(program,(struct_type_id.value())))));
}
const String visibility_string = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = visibility;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::VarVisibility::Public>();
return JaktInternal::ExplicitValue(String("public "));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::VarVisibility::Private>();
return JaktInternal::ExplicitValue(String("private "));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
));
const String type_name = TRY((ide::get_type_signature(program,var_type_id)));
if ((record_string != String(""))){
return (TRY((String::formatted(String("{}\\n\\t{}{}: {}"),record_string,visibility_string,name,type_name))));
}
else {
return (TRY((String::formatted(String("{}{}: {}"),visibility_string,name,type_name))));
}

}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<utility::Span> find_type_definition_in_program(const NonnullRefPtr<types::CheckedProgram> program,const utility::Span span) {
{
const JaktInternal::Optional<ide::Usage> result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::Variable>();utility::Span const& span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_514; {
__jakt_var_514 = TRY((ide::find_type_definition_for_type_id(program,type_id,span))); goto __jakt_label_473;

}
__jakt_label_473:; __jakt_var_514.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Call>();
types::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_515; {
__jakt_var_515 = ((((program)->get_function(function_id)))->name_span); goto __jakt_label_474;

}
__jakt_label_474:; __jakt_var_515.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Typename>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_516; {
__jakt_var_516 = TRY((ide::find_type_definition_for_type_id(program,type_id,span))); goto __jakt_label_475;

}
__jakt_label_475:; __jakt_var_516.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::NameSet>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::EnumVariant>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
else {
return (span);
}

}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_expression(const NonnullRefPtr<types::CheckedProgram> program,const NonnullRefPtr<types::CheckedExpression> expr,const utility::Span span) {
{
const JaktInternal::Optional<ide::Usage> none = JaktInternal::OptionalNone();
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::BinaryOp>();NonnullRefPtr<types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_517; {
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,lhs,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_517 = TRY((ide::find_span_in_expression(program,rhs,span))); goto __jakt_label_476;

}
__jakt_label_476:; __jakt_var_517.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktArray>();JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_518; {
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedExpression> val = (_magic_value.value());
{
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,val,span)));
if (((found).has_value())){
return (found);
}
}

}
}

if (((repeat).has_value())){
return (TRY((ide::find_span_in_expression(program,(repeat.value()),span))));
}
__jakt_var_518 = none; goto __jakt_label_477;

}
__jakt_label_477:; __jakt_var_518.release_value(); }));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Block>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& call_span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_519; {
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> ___expr__ = (_magic_value.value());
{
const JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> jakt_____expr__ = ___expr__;
const String _ = ((jakt_____expr__).get<0>());
const NonnullRefPtr<types::CheckedExpression> expr = ((jakt_____expr__).get<1>());

const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
}

}
}

if ((((((call).function_id)).has_value()) && ((call_span).contains(span)))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Call((((call).function_id).value())) } ));
}
__jakt_var_519 = none; goto __jakt_label_478;

}
__jakt_label_478:; __jakt_var_519.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktDictionary>();JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_520; {
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>> key__value__ = (_magic_value.value());
{
const JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>> jakt__key__value__ = key__value__;
const NonnullRefPtr<types::CheckedExpression> key = ((jakt__key__value__).get<0>());
const NonnullRefPtr<types::CheckedExpression> value = ((jakt__key__value__).get<1>());

JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,key,span)));
if (((found).has_value())){
return (found);
}
(found = TRY((ide::find_span_in_expression(program,value,span))));
if (((found).has_value())){
return (found);
}
}

}
}

__jakt_var_520 = none; goto __jakt_label_479;

}
__jakt_label_479:; __jakt_var_520.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedExpression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_521; {
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
(found = TRY((ide::find_span_in_expression(program,index,span))));
if (((found).has_value())){
return (found);
}
__jakt_var_521 = none; goto __jakt_label_480;

}
__jakt_label_480:; __jakt_var_521.release_value(); }));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedStruct>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
String const& index = __jakt_match_value.index;
utility::Span const& index_span = __jakt_match_value.span;
types::TypeId const& known_type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_522; {
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
if (((index_span).contains(span))){
const types::TypeId type_id = ((expr)->type());
JaktInternal::Optional<types::TypeId> result_type = JaktInternal::OptionalNone();
if ((!(((known_type_id).equals(types::unknown_type_id()))))){
(result_type = static_cast<JaktInternal::Optional<types::TypeId>>(known_type_id));
}
if (((((program)->get_type(type_id)))->index() == 22 /* Struct */)){
const types::StructId struct_id = (((program)->get_type(type_id))->get<types::Type::Struct>()).value;
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((((((program)->get_struct(struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
const types::CheckedVariable var = ((program)->get_variable(field));
if ((index != ((var).name))){
continue;
}
return ( ide::Usage { typename ide::Usage::Variable(((var).definition_span),index,result_type.value_or_lazy_evaluated([&] { return ((var).type_id); }), ide::Mutability { typename ide::Mutability::DoesNotApply() } , ide::VarType { typename ide::VarType::Field() } ,JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::VarVisibility, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = ((var).visibility);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedVisibility::Public>();
return JaktInternal::ExplicitValue( ide::VarVisibility { typename ide::VarVisibility::Public() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedVisibility::Private>();
return JaktInternal::ExplicitValue( ide::VarVisibility { typename ide::VarVisibility::Private() } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedVisibility::Restricted>();return JaktInternal::ExplicitValue( ide::VarVisibility { typename ide::VarVisibility::Restricted() } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)),type_id) } );
}

}
}

}
}
__jakt_var_522 = none; goto __jakt_label_481;

}
__jakt_label_481:; __jakt_var_522.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedDictionary>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_523; {
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_523 = TRY((ide::find_span_in_expression(program,index,span))); goto __jakt_label_482;

}
__jakt_label_482:; __jakt_var_523.release_value(); }));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Match>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Array<types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
utility::Span const& match_span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_524; {
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase match_case = (_magic_value.value());
{
const JaktInternal::Optional<ide::Usage> found = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::EnumVariant>();String const& name = __jakt_match_value.name;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
types::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
size_t const& index = __jakt_match_value.index;
types::ScopeId const& scope_id = __jakt_match_value.scope_id;
types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_525; {
if (((marker_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>(TRY((ide::get_enum_variant_usage_from_type_id_and_name(program,subject_type_id,name)))));
}
__jakt_var_525 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_484;

}
__jakt_label_484:; __jakt_var_525.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::Expression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expression;
types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_526; {
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_526 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_485;

}
__jakt_label_485:; __jakt_var_526.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::CatchAll>();types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((marker_span).contains(span)));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_527; {
const JaktInternal::Set<String> all_cases = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Set<String>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *((program)->get_type(type_id));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<String>> __jakt_var_528; {
JaktInternal::Set<String> names = (TRY((Set<String>::create_with_values({}))));
const types::CheckedEnum enum_ = ((program)->get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
TRY((((names).add(((variant).name())))));
}

}
}

__jakt_var_528 = names; goto __jakt_label_487;

}
__jakt_label_487:; __jakt_var_528.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<String>> __jakt_var_529; {
JaktInternal::Set<String> names = (TRY((Set<String>::create_with_values({}))));
const types::CheckedEnum enum_ = ((program)->get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
TRY((((names).add(((variant).name())))));
}

}
}

__jakt_var_529 = names; goto __jakt_label_488;

}
__jakt_label_488:; __jakt_var_529.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<String>> __jakt_var_530; {
__jakt_var_530 = (TRY((Set<String>::create_with_values({TRY((String::formatted(String("else ({})"),TRY((((program)->type_name(type_id)))))))})))); goto __jakt_label_489;

}
__jakt_label_489:; __jakt_var_530.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
JaktInternal::Set<String> remaining_cases = all_cases;
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase other_case = (_magic_value.value());
{
if (((other_case).index() == 0 /* EnumVariant */)){
const String name = (other_case.get<types::CheckedMatchCase::EnumVariant>()).name;
((remaining_cases).remove(name));
}
}

}
}

__jakt_var_527 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((remaining_cases).is_empty()));
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_531; {
JaktInternal::Array<String> cases_array = (TRY((Array<String>::create_with({}))));
TRY((((cases_array).ensure_capacity(((remaining_cases).size())))));
{
JaktInternal::SetIterator<String> _magic = ((remaining_cases).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
TRY((((cases_array).push(name))));
}

}
}

__jakt_var_531 = static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::NameSet(cases_array) } ); goto __jakt_label_490;

}
__jakt_label_490:; __jakt_var_531.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}()))
; goto __jakt_label_486;

}
__jakt_label_486:; __jakt_var_527.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}()))
);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
if (((found).has_value())){
return (found);
}
}

}
}

__jakt_var_524 = TRY((ide::find_span_in_expression(program,expr,span))); goto __jakt_label_483;

}
__jakt_label_483:; __jakt_var_524.release_value(); }));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ForcedUnwrap>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& method_span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> ___expr__ = (_magic_value.value());
{
const JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> jakt_____expr__ = ___expr__;
const String _ = ((jakt_____expr__).get<0>());
const NonnullRefPtr<types::CheckedExpression> expr = ((jakt_____expr__).get<1>());

(found = TRY((ide::find_span_in_expression(program,expr,span))));
if (((found).has_value())){
return (found);
}
}

}
}

if ((((((call).function_id)).has_value()) && ((method_span).contains(span)))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Call((((call).function_id).value())) } ));
}
return (none);
}
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Var>();types::CheckedVariable const& var = __jakt_match_value.var;
utility::Span const& var_span = __jakt_match_value.span;
{
const JaktInternal::Optional<types::TypeId> none_type_id = JaktInternal::OptionalNone();
if (((var_span).contains(span))){
const ide::Mutability mutability = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::Mutability,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((var).is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( ide::Mutability { typename ide::Mutability::Mutable() } );
}
else {
return JaktInternal::ExplicitValue( ide::Mutability { typename ide::Mutability::Immutable() } );
}
}()))
;
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Variable(((var).definition_span),((var).name),((var).type_id),mutability, ide::VarType { typename ide::VarType::Variable() } , ide::VarVisibility { typename ide::VarVisibility::DoesNotApply() } ,none_type_id) } ));
}
return (none);
}
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NamespacedVar>();JaktInternal::Array<types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
types::CheckedVariable const& var = __jakt_match_value.var;
utility::Span const& var_span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_532; {
if ((((var_span).contains(span)) && (!(((namespaces).is_empty()))))){
const types::CheckedNamespace last_ns = (((namespaces).last()).value());
if (((((TRY((((program)->get_scope(((last_ns).scope))))))->namespace_name)).has_value())){
const JaktInternal::Optional<types::EnumId> enum_id = TRY((((program)->find_enum_in_scope(((last_ns).scope),((last_ns).name)))));
if (((enum_id).has_value())){
const types::CheckedEnum enum_ = ((program)->get_enum((enum_id.value())));
return (static_cast<JaktInternal::Optional<ide::Usage>>(TRY((ide::get_enum_variant_usage_from_type_id_and_name(program,((enum_).type_id),((var).name))))));
}
}
}
__jakt_var_532 = none; goto __jakt_label_491;

}
__jakt_label_491:; __jakt_var_532.release_value(); }));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::TryBlock>();NonnullRefPtr<types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
String const& error_name = __jakt_match_value.error_name;
types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_533; {
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_statement(program,stmt,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_533 = TRY((ide::find_span_in_block(program,catch_block,span))); goto __jakt_label_492;

}
__jakt_label_492:; __jakt_var_533.release_value(); }));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Try>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<types::CheckedBlock> const& catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_534; {
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_534 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((catch_block).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,(catch_block.value()),span))));
}
else {
return JaktInternal::ExplicitValue(none);
}
}()))
; goto __jakt_label_493;

}
__jakt_label_493:; __jakt_var_534.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Range>();JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& to = __jakt_match_value.to;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_535; {
if (((from).has_value())){
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,(from.value()),span)));
if (((found).has_value())){
return (found);
}
}
if (((to).has_value())){
return (TRY((ide::find_span_in_expression(program,(to.value()),span))));
}
__jakt_var_535 = none; goto __jakt_label_494;

}
__jakt_label_494:; __jakt_var_535.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(none);
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_block(const NonnullRefPtr<types::CheckedProgram> program,const types::CheckedBlock block,const utility::Span span) {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedStatement> statement = (_magic_value.value());
{
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_statement(program,statement,span)));
if (((found).has_value())){
return (found);
}
}

}
}

return (JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_program(const NonnullRefPtr<types::CheckedProgram> program,const utility::Span span) {
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> iterator = ((((program)->modules)).iterator());
const JaktInternal::Optional<NonnullRefPtr<types::Module>> dummy = ((iterator).next());
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = iterator;
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
const NonnullRefPtr<types::Scope> scope = TRY((((program)->get_scope(types::ScopeId(((module)->id),static_cast<size_t>(0ULL))))));
return (TRY((ide::find_span_in_scope(program,scope,span))));
}

}
}

return (JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_function(const NonnullRefPtr<types::CheckedProgram> program,const NonnullRefPtr<types::CheckedFunction> checked_function,const utility::Span span) {
{
if (((((checked_function)->return_type_span)).has_value())){
if ((((((checked_function)->return_type_span).value())).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((checked_function)->return_type_id)) } ));
}
}
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if (((((((param).variable)).definition_span)).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((((param).variable)).type_id)) } ));
}
}

}
}

return (TRY((ide::find_span_in_block(program,((checked_function)->block),span))));
}
}

ErrorOr<JaktInternal::Optional<String>> find_typename_in_program(const NonnullRefPtr<types::CheckedProgram> program,const utility::Span span) {
{
const JaktInternal::Optional<ide::Usage> result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<String>, ErrorOr<JaktInternal::Optional<String>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::Variable>();String const& name = __jakt_match_value.name;
types::TypeId const& type_id = __jakt_match_value.type_id;
ide::Mutability const& mutability = __jakt_match_value.mutability;
ide::VarType const& var_type = __jakt_match_value.var_type;
ide::VarVisibility const& visibility = __jakt_match_value.visibility;
JaktInternal::Optional<types::TypeId> const& struct_type_id = __jakt_match_value.struct_type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_536; {
const String result = TRY((ide::get_var_signature(program,name,type_id,mutability,var_type,visibility,struct_type_id)));
__jakt_var_536 = static_cast<JaktInternal::Optional<String>>(result); goto __jakt_label_495;

}
__jakt_label_495:; __jakt_var_536.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Call>();
types::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_537; {
const String result = TRY((ide::get_function_signature(program,function_id)));
__jakt_var_537 = static_cast<JaktInternal::Optional<String>>(result); goto __jakt_label_496;

}
__jakt_label_496:; __jakt_var_537.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Typename>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_538; {
const String result = TRY((ide::get_type_signature(program,type_id)));
__jakt_var_538 = static_cast<JaktInternal::Optional<String>>(result); goto __jakt_label_497;

}
__jakt_label_497:; __jakt_var_538.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::NameSet>();
JaktInternal::Array<String> const& names = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_539; {
String output = String("");
bool first = true;
{
JaktInternal::ArrayIterator<String> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
if ((!(first))){
(output += String(" | "));
}
else {
(first = false);
}

(output += name);
}

}
}

__jakt_var_539 = static_cast<JaktInternal::Optional<String>>(output); goto __jakt_label_498;

}
__jakt_label_498:; __jakt_var_539.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::EnumVariant>();String const& name = __jakt_match_value.name;
types::TypeId const& type_id = __jakt_match_value.type_id;
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> const& variants = __jakt_match_value.variants;
JaktInternal::Optional<types::NumberConstant> const& number_constant = __jakt_match_value.number_constant;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_540; {
const String result = TRY((ide::get_enum_variant_signature(program,name,type_id,variants,number_constant)));
__jakt_var_540 = static_cast<JaktInternal::Optional<String>>(result); goto __jakt_label_499;

}
__jakt_label_499:; __jakt_var_540.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
else {
return (JaktInternal::OptionalNone());
}

}
}

ErrorOr<utility::Span> find_type_definition_for_type_id(const NonnullRefPtr<types::CheckedProgram> program,const types::TypeId type_id,const utility::Span span) {
{
const types::StructId array_struct_id = TRY((((program)->find_struct_in_prelude(String("Array")))));
const types::StructId dictionary_struct_id = TRY((((program)->find_struct_in_prelude(String("Dictionary")))));
const types::StructId optional_struct_id = TRY((((program)->find_struct_in_prelude(String("Optional")))));
const types::StructId range_struct_id = TRY((((program)->find_struct_in_prelude(String("Range")))));
const types::StructId set_struct_id = TRY((((program)->find_struct_in_prelude(String("Set")))));
const types::StructId tuple_struct_id = TRY((((program)->find_struct_in_prelude(String("Tuple")))));
const types::StructId weak_ptr_struct_id = TRY((((program)->find_struct_in_prelude(String("WeakPtr")))));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
auto&& __jakt_match_variant = *((program)->get_type(type_id));
switch(__jakt_match_variant.index()) {
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Never>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::F32>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::F64>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I8>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I16>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I32>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I64>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U8>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U16>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U32>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U64>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Usize>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CChar>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CInt>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Bool>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Void>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Unknown>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::JaktString>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_541; {
utility::Span output = span;
if ((((((((struct_id).equals(array_struct_id)) || ((struct_id).equals(optional_struct_id))) || ((struct_id).equals(range_struct_id))) || ((struct_id).equals(set_struct_id))) || ((struct_id).equals(tuple_struct_id))) || ((struct_id).equals(weak_ptr_struct_id)))){
(output = TRY((ide::find_type_definition_for_type_id(program,((args)[static_cast<i64>(0LL)]),span))));
}
else if (((struct_id).equals(dictionary_struct_id))){
(output = TRY((ide::find_type_definition_for_type_id(program,((args)[static_cast<i64>(1LL)]),span))));
}
else {
(output = ((((program)->get_struct(struct_id))).name_span));
}

__jakt_var_541 = output; goto __jakt_label_500;

}
__jakt_label_500:; __jakt_var_541.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_struct(struct_id))).name_span));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_enum(id))).name_span));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_enum(id))).name_span));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();types::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_struct(id))).name_span));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> get_enum_variant_signature(const NonnullRefPtr<types::CheckedProgram> program,const String name,const types::TypeId type_id,const JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> variants,const JaktInternal::Optional<types::NumberConstant> number_constant) {
{
String output = TRY((ide::get_type_signature(program,type_id)));
(output += String("::"));
(output += name);
if ((!(((variants).is_empty())))){
(output += String("("));
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId> variant_name__variant_type_id__ = (_magic_value.value());
{
const JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId> jakt__variant_name__variant_type_id__ = variant_name__variant_type_id__;
const JaktInternal::Optional<String> variant_name = ((jakt__variant_name__variant_type_id__).get<0>());
const types::TypeId variant_type_id = ((jakt__variant_name__variant_type_id__).get<1>());

if (first){
(first = false);
}
else {
(output += String(", "));
}

if (((variant_name).has_value())){
(output += (variant_name.value()));
(output += String(": "));
}
(output += TRY((((program)->type_name(variant_type_id)))));
}

}
}

(output += String(")"));
}
if (((number_constant).has_value())){
(output += String(" = "));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = (number_constant.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Signed>();
i64 const& value = __jakt_match_value.value;
{
(output += TRY((String::formatted(String("{}"),value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Unsigned>();
u64 const& value = __jakt_match_value.value;
{
(output += TRY((String::formatted(String("{}"),value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Floating>();
f64 const& value = __jakt_match_value.value;
{
(output += TRY((String::formatted(String("{}"),value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}
return (output);
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_enum(const NonnullRefPtr<types::CheckedProgram> program,const types::CheckedEnum checked_enum,const utility::Span span) {
{
const NonnullRefPtr<types::Scope> scope = TRY((((program)->get_scope(((checked_enum).scope_id)))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((checked_enum).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& name = __jakt_match_value.name;
JaktInternal::Array<types::VarId> const& fields = __jakt_match_value.fields;
utility::Span const& variant_span = __jakt_match_value.span;
{
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
const types::CheckedVariable var = ((program)->get_variable(field));
if (((((var).definition_span)).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((var).type_id)) } ));
}
}

}
}

if (((variant_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::EnumVariant(span,name,((checked_enum).type_id),(TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({})))),JaktInternal::OptionalNone()) } ));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& name = __jakt_match_value.name;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),TRY((ide::enum_variant_fields(program,variant))),JaktInternal::OptionalNone()) } ));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& name = __jakt_match_value.name;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),(TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({})))),JaktInternal::OptionalNone()) } ));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();String const& name = __jakt_match_value.name;
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),TRY((ide::enum_variant_fields(program,variant))),((expr)->to_number_constant(program))) } ));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}

}
}

const JaktInternal::Optional<ide::Usage> usage = TRY((ide::find_span_in_scope(program,scope,span)));
return (usage);
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_statement(const NonnullRefPtr<types::CheckedProgram> program,const NonnullRefPtr<types::CheckedStatement> statement,const utility::Span span) {
{
const JaktInternal::Optional<ide::Usage> none = JaktInternal::OptionalNone();
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Block>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Defer>();NonnullRefPtr<types::CheckedStatement> const& statement = __jakt_match_value.statement;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_statement(program,statement,span))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Expression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::If>();NonnullRefPtr<types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_542; {
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,condition,span)));
if (((found).has_value())){
return (found);
}
(found = TRY((ide::find_span_in_block(program,then_block,span))));
if (((found).has_value())){
return (found);
}
if (((else_statement).has_value())){
return (TRY((ide::find_span_in_statement(program,(else_statement.value()),span))));
}
__jakt_var_542 = none; goto __jakt_label_501;

}
__jakt_label_501:; __jakt_var_542.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::InlineCpp>();return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_543; {
const JaktInternal::Optional<ide::Usage> output = JaktInternal::OptionalNone();
__jakt_var_543 = output; goto __jakt_label_502;

}
__jakt_label_502:; __jakt_var_543.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Loop>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Return>();JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((val).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,(val.value()),span))));
}
else {
return JaktInternal::ExplicitValue(none);
}
}()))
);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Throw>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::VarDecl>();types::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<types::CheckedExpression> const& init = __jakt_match_value.init;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_544; {
const types::CheckedVariable checked_var = ((program)->get_variable(var_id));
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,init,span)));
if (((found).has_value())){
return (found);
}
if (((((checked_var).type_span)).has_value())){
const utility::Span type_span = (((checked_var).type_span).value());
if (((type_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((checked_var).type_id)) } ));
}
}
if (((((checked_var).definition_span)).contains(span))){
const ide::Mutability mutability = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::Mutability,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((checked_var).is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( ide::Mutability { typename ide::Mutability::Mutable() } );
}
else {
return JaktInternal::ExplicitValue( ide::Mutability { typename ide::Mutability::Immutable() } );
}
}()))
;
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Variable(((checked_var).definition_span),((checked_var).name),((checked_var).type_id),mutability, ide::VarType { typename ide::VarType::Variable() } , ide::VarVisibility { typename ide::VarVisibility::DoesNotApply() } ,JaktInternal::OptionalNone()) } ));
}
__jakt_var_544 = none; goto __jakt_label_503;

}
__jakt_label_503:; __jakt_var_544.release_value(); }));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::While>();NonnullRefPtr<types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_545; {
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,condition,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_545 = TRY((ide::find_span_in_block(program,block,span))); goto __jakt_label_504;

}
__jakt_label_504:; __jakt_var_545.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::DestructuringAssignment>();JaktInternal::Array<NonnullRefPtr<types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_546; {
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedStatement>> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedStatement> var = (_magic_value.value());
{
const JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_statement(program,var,span)));
if (((found).has_value())){
return (found);
}
}

}
}

__jakt_var_546 = TRY((ide::find_span_in_statement(program,var_decl,span))); goto __jakt_label_505;

}
__jakt_label_505:; __jakt_var_546.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Yield>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Break>();
return JaktInternal::ExplicitValue(none);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Continue>();
return JaktInternal::ExplicitValue(none);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Garbage>();
return JaktInternal::ExplicitValue(none);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_struct(const NonnullRefPtr<types::CheckedProgram> program,const types::CheckedStruct checked_struct,const utility::Span span) {
{
const NonnullRefPtr<types::Scope> scope = TRY((((program)->get_scope(((checked_struct).scope_id)))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((((checked_struct).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
const types::CheckedVariable variable = ((program)->get_variable(field));
if (((((variable).definition_span)).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((variable).type_id)) } ));
}
}

}
}

const JaktInternal::Optional<ide::Usage> usage = TRY((ide::find_span_in_scope(program,scope,span)));
return (usage);
}
}

ErrorOr<String> get_function_signature(const NonnullRefPtr<types::CheckedProgram> program,const types::FunctionId function_id) {
{
const NonnullRefPtr<types::CheckedFunction> checked_function = ((program)->get_function(function_id));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = ((checked_function)->type);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::FunctionType::ImplicitEnumConstructor>();
{
const types::TypeId type_id = ((checked_function)->return_type_id);
const String name = ((checked_function)->name);
return (TRY((ide::get_enum_variant_signature_from_type_id_and_name(program,type_id,name))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::FunctionType::ImplicitConstructor>();
{
return (TRY((ide::get_constructor_signature(program,function_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
String generic_parameters = String("");
bool is_first_param = true;
if ((!(((((((checked_function)->generics))->params)).is_empty())))){
(generic_parameters += String("<"));
{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((((((checked_function)->generics))->params)).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter parameter = (_magic_value.value());
{
const String generic_type = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = parameter;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::FunctionGenericParameter::InferenceGuide>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_547; {
__jakt_var_547 = TRY((((program)->type_name(type_id)))); goto __jakt_label_506;

}
__jakt_label_506:; __jakt_var_547.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::FunctionGenericParameter::Parameter>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_548; {
__jakt_var_548 = TRY((((program)->type_name(type_id)))); goto __jakt_label_507;

}
__jakt_label_507:; __jakt_var_548.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
const String separator = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (is_first_param);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(""));
}
else {
return JaktInternal::ExplicitValue(String(", "));
}
}()))
;
(generic_parameters += TRY((String::formatted(String("{}{}"),separator,generic_type))));
(is_first_param = false);
}

}
}

(generic_parameters += String(">"));
}
String parameters = String("");
(is_first_param = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
const String anon_value = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((param).requires_label));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(""));
}
else {
return JaktInternal::ExplicitValue(String("anon "));
}
}()))
;
const String is_mutable = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((((param).variable)).is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("mut "));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
String variable_type = TRY((((program)->type_name(((((param).variable)).type_id)))));
if ((variable_type != String("void"))){
(variable_type = (String(": ") + variable_type));
}
else {
(variable_type = String(""));
}

const String separator = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (is_first_param);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(""));
}
else {
return JaktInternal::ExplicitValue(String(", "));
}
}()))
;
(parameters += TRY((String::formatted(String("{}{}{}{}{}"),separator,anon_value,is_mutable,((((param).variable)).name),variable_type))));
(is_first_param = false);
}

}
}

const String throws_str = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((checked_function)->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(" throws"));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
String returns = TRY((((program)->type_name(((checked_function)->return_type_id)))));
if ((returns != String("void"))){
(returns = (String(" -> ") + returns));
}
else {
(returns = String(""));
}

return (TRY((String::formatted(String("function {}{}({}){}{}"),((checked_function)->name),generic_parameters,parameters,throws_str,returns))));
}
}

ErrorOr<String> ide::Mutability::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* DoesNotApply */: {
[[maybe_unused]] auto const& that = this->template get<Mutability::DoesNotApply>();
TRY(builder.append("Mutability::DoesNotApply"));
break;}
case 1 /* Immutable */: {
[[maybe_unused]] auto const& that = this->template get<Mutability::Immutable>();
TRY(builder.append("Mutability::Immutable"));
break;}
case 2 /* Mutable */: {
[[maybe_unused]] auto const& that = this->template get<Mutability::Mutable>();
TRY(builder.append("Mutability::Mutable"));
break;}
}
return builder.to_string();
}
ErrorOr<String> ide::Usage::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Variable */: {
[[maybe_unused]] auto const& that = this->template get<Usage::Variable>();
TRY(builder.append("Usage::Variable"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\"", that.name));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("mutability: {}", that.mutability));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("var_type: {}", that.var_type));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("visibility: {}", that.visibility));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("struct_type_id: {}", that.struct_type_id));
}
TRY(builder.append(")"));
break;}
case 1 /* Call */: {
[[maybe_unused]] auto const& that = this->template get<Usage::Call>();
TRY(builder.append("Usage::Call"));
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* Typename */: {
[[maybe_unused]] auto const& that = this->template get<Usage::Typename>();
TRY(builder.append("Usage::Typename"));
TRY(builder.appendff("({})", that.value));
break;}
case 3 /* NameSet */: {
[[maybe_unused]] auto const& that = this->template get<Usage::NameSet>();
TRY(builder.append("Usage::NameSet"));
TRY(builder.appendff("({})", that.value));
break;}
case 4 /* EnumVariant */: {
[[maybe_unused]] auto const& that = this->template get<Usage::EnumVariant>();
TRY(builder.append("Usage::EnumVariant"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\"", that.name));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("variants: {}", that.variants));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("number_constant: {}", that.number_constant));
}
TRY(builder.append(")"));
break;}
}
return builder.to_string();
}
ErrorOr<String> ide::VarType::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Variable */: {
[[maybe_unused]] auto const& that = this->template get<VarType::Variable>();
TRY(builder.append("VarType::Variable"));
break;}
case 1 /* Field */: {
[[maybe_unused]] auto const& that = this->template get<VarType::Field>();
TRY(builder.append("VarType::Field"));
break;}
}
return builder.to_string();
}
ErrorOr<String> ide::VarVisibility::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* DoesNotApply */: {
[[maybe_unused]] auto const& that = this->template get<VarVisibility::DoesNotApply>();
TRY(builder.append("VarVisibility::DoesNotApply"));
break;}
case 1 /* Public */: {
[[maybe_unused]] auto const& that = this->template get<VarVisibility::Public>();
TRY(builder.append("VarVisibility::Public"));
break;}
case 2 /* Private */: {
[[maybe_unused]] auto const& that = this->template get<VarVisibility::Private>();
TRY(builder.append("VarVisibility::Private"));
break;}
case 3 /* Restricted */: {
[[maybe_unused]] auto const& that = this->template get<VarVisibility::Restricted>();
TRY(builder.append("VarVisibility::Restricted"));
break;}
}
return builder.to_string();
}
}
} // namespace Jakt
