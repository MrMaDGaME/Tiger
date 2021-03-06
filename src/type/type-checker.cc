/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <memory>

#include <ast/all.hh>
#include <range/v3/view/iota.hpp>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace type
{
  namespace
  {
    // Try to cast the type into a nil type.
    // If it's not actually a `type::Nil`, return `nullptr`.
    // This allows us to write more clear code like:
    // if (auto nil = to_nil(e.type_get())
    // ...
    const Nil* to_nil(const Type& type)
    {
      return dynamic_cast<const Nil*>(&type.actual());
    }

  } // namespace

  TypeChecker::TypeChecker()
    : super_type()
    , error_()
  {}

  const Type* TypeChecker::type(ast::Typable& e)
  {
    // FIXME: Some code was deleted here.
    if (!e.type_get())
        e.accept(*this);
    return e.type_get();
  }

  const Record* TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
    // FIXME: Some code was deleted here.
    /*for (auto var : e)
      res->field_add(var);
    return res;*/
  }

  const Record* TypeChecker::type(const ast::VarChunk& e)
  {
    auto res = new Record;
    for (const auto& var : e)
      res->field_add(var->name_get(), *type(*var));

    return res;
  }

  const misc::error& TypeChecker::error_get() const { return error_; }

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  void TypeChecker::error(const ast::Ast& ast, const std::string& msg)
  {
    error_ << misc::error::error_type::type << ast.location_get() << ": " << msg
           << std::endl;
  }

  void TypeChecker::type_mismatch(const ast::Ast& ast,
                                  const std::string& exp1,
                                  const Type& type1,
                                  const std::string& exp2,
                                  const Type& type2)
  {
    error_ << misc::error::error_type::type << ast.location_get()
           << ": type mismatch" << misc::incendl << exp1 << " type: " << type1
           << misc::iendl << exp2 << " type: " << type2 << misc::decendl;
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                const Type& type1,
                                const std::string& exp2,
                                const Type& type2)
  {
     if (!type1.compatible_with(type2))
         type_mismatch(ast, exp1, type1, exp2, type2);
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                ast::Typable& type1,
                                const std::string& exp2,
                                ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
    // FIXME: Some code was deleted here (Check types).
    check_types(ast, exp1, *type1.type_get(), exp2, *type2.type_get());
  }

  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void TypeChecker::operator()(ast::SimpleVar& e)
  {
    // FIXME: Some code was deleted here.

  }

  // FIXME: Some code was deleted here.

  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void TypeChecker::operator()(ast::NilExp& e)
  {
    auto nil_ptr = std::make_unique<Nil>();
    type_default(e, nil_ptr.get());
    created_type_default(e, nil_ptr.release());
  }

  void TypeChecker::operator()(ast::IntExp& e)
  {
    // FIXME: Some code was deleted here.
    type_default(e, &Int::instance());
  }

  void TypeChecker::operator()(ast::StringExp& e)
  {
    // FIXME: Some code was deleted here.
    type_default(e, &String::instance());
  }

  // Complex values.

  void TypeChecker::operator()(ast::RecordExp& e)
  {
    // If no error occured, check for nil types in the record initialization.
    // If any error occured, there's no need to set any nil types.
    // If there are any record initializations, set the `record_type_`
    // of the `Nil` to the expected type.
    // FIXME: Some code was deleted here.
    /*if (!error_) {
        for (auto &ftype: e.fields_get()) {
            if (type(ftype))
        }
    }*/
  }

  void TypeChecker::operator()(ast::OpExp& e)
  {
    // FIXME: Some code was deleted here.
    auto left = &e.left_get();
    auto right = &e.right_get();
    ast::OpExp::Oper oper = e.oper_get();
    if(type(*left)->compatible_with(*type(*right)))
    {
        if (!dynamic_cast<const Int*>(type(*left)) && !dynamic_cast<const Nil*>(type(*left)))
        {
            if (dynamic_cast<const String*>(type(*left)))
            {
                if (oper == ast::OpExp::Oper::add
                    || oper == ast::OpExp::Oper::sub
                    || oper == ast::OpExp::Oper::mul
                    || oper == ast::OpExp::Oper::div)
                    error(e, "Wrong operator for type string");
            }
            else if (dynamic_cast<const Record*>(type(*left)))
            {
                if (oper != ast::OpExp::Oper::eq && oper != ast::OpExp::Oper::ne)
                    error(e, "Wrong operator for type record");
            }
            else
                error(e, "Unrecognized type");
        }
    }
    else
    {
        error(e, "Left operand is not compatible with right operand\n");
    }
    // If any of the operands are of type Nil, set the `record_type_` to the
    // type of the opposite operand.
    if (!error_)
      {
        // DONE: Some code was deleted here.
        if (Nil* nil = dynamic_cast<Nil*>(left))
            nil->record_type_set(*type(*left));
        else if (Nil* nil = dynamic_cast<Nil*>(right))
            nil->record_type_set(*type(*right));
      }
  }

  // FIXME: Some code was deleted here.
  void TypeChecker::operator()(ast::SeqExp& e){
      if (e.exps_get().size()) {
          ast::Exp *last = e.exps_get()[0];
          for (ast::Exp *exp: e.exps_get()) {
              type(*exp);
              last = exp;
          }
          e.type_set(last->type_get());
      }
      else
          e.type_set(&Void::instance());
  }
  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  void TypeChecker::operator()(ast::FunctionChunk& e)
  {
    chunk_visit<ast::FunctionDec>(e);
  }

  void TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store the type of this function.
  template <>
  void TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
    const Type* res_type;
    if (e.result_get())
        res_type = type(*e.result_get());//type() pas sur que ca marche
    else
        res_type = &Void::instance();
    auto function = new Function(type(e.formals_get()), *res_type);
    e.type_constructor_set(function);//A v??rifier
    e.type_set(function);
  }

  // Type check this function's body.
  template <>
  void TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    if (e.body_get())
      {
        visit_routine_body<Function>(e);

        // Check for Nil types in the function body.
        if (!error_)
          {
            // FIXME: Some code was deleted here.

          }
      }
  }

  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void TypeChecker::operator()(ast::VarDec& e)
  {
    // FIXME: Some code was deleted here.
  }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/

  void TypeChecker::operator()(ast::TypeChunk& e)
  {
    chunk_visit<ast::TypeDec>(e);
  }

  void TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store this type.
  template <> void TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
    // FIXME: Some code was deleted here.
    Named* name = new Named(e.name_get());
    e.type_constructor_set(name);
    e.type_set(name);
  }

  // Bind the type body to its name.
  template <> void TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    // FIXME: Some code was deleted here.
     Named* name = dynamic_cast<Named*>(e.type_get());
     //add a Named le type du body
     type(e.ty_get());
     name->type_set(e.ty_get->type_get());
     if (e.sound())
     {
         error(e, "VASY DJ FAIT PETER LE SON\n");
     }
  }

  /*------------------.
  | Visiting /Chunk/. |
  `------------------*/

  template <class D> void TypeChecker::chunk_visit(ast::Chunk<D>& e)
  {
    // FIXME: Some code was deleted here.
    for (auto elt : e)
    {
        visit_dec_header<D>(*elt);
    }
    for (auto elt : e)
    {
        visit_dec_body<D>(*elt);
    }
  }

  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void TypeChecker::operator()(ast::NameTy& e)
  {
    // FIXME: Some code was deleted here (Recognize user defined types, and built-in types).
    if (!e.def_get())
    {
        if (e.name_get() == "int")
        {
            e.type_set(&Int::instance());
        }
        else if (e.name_get() == "string")
        {
            e.type_set(&String::instance());
        }
    }
    else
        e.type_set(e.def_get()->type_get());

  }

  void TypeChecker::operator()(ast::RecordTy& e)
  {
    // FIXME: Some code was deleted here.
  }

  void TypeChecker::operator()(ast::ArrayTy& e)
  {
    // FIXME: Some code was deleted here.
  }

} // namespace type
