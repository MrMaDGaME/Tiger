                                                                // -*- C++ -*-
%require "3.0"
%language "C++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.value.type variant
%define api.token.constructor

// We use a GLR parser because it is able to handle Shift-Reduce and
// Reduce-Reduce conflicts by forking and testing each way at runtime. GLR
// permits, by allowing few conflicts, more readable and maintainable grammars.
%glr-parser
%skeleton "glr2.cc"

// In TC, we expect the GLR to resolve one Shift-Reduce and zero Reduce-Reduce
// conflict at runtime. Use %expect and %expect-rr to tell Bison about it.
  // FIXME: Some code was deleted here (Other directives).
%expect 1
%expect-rr 1 // remettre a 0

%define parse.error verbose
%defines
%debug
// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define api.filename.type {const std::string}
%locations

// The parsing context.
%param { ::parse::TigerParser& tp }

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>

  // Pre-declare parse::parse to allow a ``reentrant'' parsing within
  // the parser.
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

%code provides
{
  // Announce to Flex the prototype we want for lexing (member) function.
  # define YY_DECL_(Prefix)                               \
    ::parse::parser::symbol_type                          \
    (Prefix parselex)(::parse::TigerParser& tp)
  # define YY_DECL YY_DECL_(yyFlexLexer::)
}

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"


/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/chunk.hh>
# include <ast/chunk-list.hh>
}

  // FIXME: Some code was deleted here (Printers and destructors).


/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/scantiger.hh>
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>
# include <parse/tiger-driver.hh>

  namespace
  {

    /// Get the metavar from the specified map.
    template <typename T>
    T*
    metavar(parse::TigerParser& tp, unsigned key)
    {
      parse::Tweast* input = tp.input_;
      return input->template take<T>(key);
    }

  }

  /// Use our local scanner object.
  inline
  ::parse::parser::symbol_type
  parselex(parse::TigerParser& tp)
  {
    return tp.scanner_->parselex(tp);
  }
}

// Definition of the tokens, and their pretty-printing.
%token AND          "&"
       ARRAY        "array"
       ASSIGN       ":="
       BREAK        "break"
       CAST         "_cast"
       CLASS        "class"
       COLON        ":"
       COMMA        ","
       DIVIDE       "/"
       DO           "do"
       DOT          "."
       ELSE         "else"
       END          "end"
       EQ           "="
       EXTENDS      "extends"
       FOR          "for"
       FUNCTION     "function"
       GE           ">="
       GT           ">"
       IF           "if"
       IMPORT       "import"
       IN           "in"
       LBRACE       "{"
       LBRACK       "["
       LE           "<="
       LET          "let"
       LPAREN       "("
       LT           "<"
       MINUS        "-"
       METHOD       "method"
       NE           "<>"
       NEW          "new"
       NIL          "nil"
       OF           "of"
       OR           "|"
       PLUS         "+"
       PRIMITIVE    "primitive"
       RBRACE       "}"
       RBRACK       "]"
       RPAREN       ")"
       SEMI         ";"
       THEN         "then"
       TIMES        "*"
       TO           "to"
       TYPE         "type"
       VAR          "var"
       WHILE        "while"
       EOF 0        "end of file"

%type <ast::Exp*>             exp
%type <ast::ChunkList*>       chunks

%type <ast::TypeChunk*>       tychunk
%type <ast::TypeDec*>         tydec
%type <ast::NameTy*>          typeid
%type <ast::Ty*>              ty

%type <ast::FunctionChunk*>   funchunk
%type <ast::FunctionDec*>     fundec
%type <ast::VarChunk*>        varchunk
%type <ast::VarDec*>          vardec
%type <ast::Var*>             lvalue
%type <ast:SeqExp*>           exps

%type <ast::Field*>           tyfield
%type <ast::fields_type*>     tyfields tyfields.1
  // FIXME: Some code was deleted here (More %types).

  // FIXME: Some code was deleted here (Priorities/associativities).

// Solving conflicts on:
// let type foo = bar
//     type baz = bat
// which can be understood as a list of two TypeChunk containing
// a unique TypeDec each, or a single TypeChunk containing two TypeDec.
// We want the latter.
%precedence CHUNKS
%precedence TYPE
  // FIXME: Some code was deleted here (Other declarations).

%precedence "then" "else" "do"
%left "|"
%left "&"
%nonassoc ">=" "<=" "=" "<>" "<" ">" ":="
%left "+" "-"
%left "*" "/"
%precedence "of"


%start program

%%
program:
  /* Parsing a source program.  */
  exp { tp.ast_ = $1; }
| /* Parsing an imported file.  */
  chunks { tp.ast_ = $1; }
;

exps:
    %empty          { $$ = tp.td_.make_ChunkList(@$); }
  | exp             { tp.ast_ = $1; }
  | exp ";" exps    { tp.ast_ = $1; tp.td_.make_SeqExp(@$, $3); }


exp:
  INT                                           { $$ = tp.td_.make_IntExp(@$, $1); }
  // FIXME: Some code was deleted here (More rules).
  | "nil"                                       { tp.td_.make_NilExp(@$); }
  | STRING                                      { tp.td_.make_StringExp(@$, $1); }
  /* Array and record creations. */
  | typeid "[" exp "]" "of" exp                 { tp.td_.make_ArrayExp(@$, tp.td_.make_ArrayTy(@1, $1), $3, $6); }
  | typeid "{" "}"                              { tp.td_.make_RecordExp(@$, tp.td_.make_RecordTy(@1, $1), nullptr); }
  | typeid "{" ID "=" exp "}"                   { tp.td_.make_RecordExp(@$, tp.td_.make_RecordTy(@1, $1), tp.td_.make_fieldinits_type(tp.td_.make_OpExp(@3, $3, eq, $5))); }
  | typeid "{" ID "=" exp record_r "}"          { tp.td_.make_RecordExp(@$, tp.td_.make_RecordTy(@1, $1), tp.td_.make_fieldinits_type(tp.td_.make_OpExp(@3, $3, eq, $5))); }

  /* Variables, field, elements of an array. */
  | lvalue                      { tp.td_.make_SimpleVar(@$, $1); }

  /* Function call. */
  | ID "(" ")"                  { tp.td_.make_FunctionChunk(nullptr); }
  | ID "(" exp ")"              { tp.td_.make_FunctionChunk($3); }
  | ID "(" exp function_r ")"   { tp.td_.make_FunctionChunk($3); }

  /* Operations. */
  | "-" exp         { tp.td_.make_OpExp(@$, 0, sub, $2); }
  | exp "+" exp     { tp.td_.make_OpExp(@$, $1, add, $3); }
  | exp "<=" exp    { tp.td_.make_OpExp(@$, $1, le, $3); }
  | exp ">=" exp    { tp.td_.make_OpExp(@$, $1, ge, $3); }
  | exp "<>" exp    { tp.td_.make_OpExp(@$, $1, ne, $3); }
  | exp "-" exp     { tp.td_.make_OpExp(@$, $1, sub, $3); }
  | exp "*" exp     { tp.td_.make_OpExp(@$, $1, mul, $3); }
  | exp "/" exp     { tp.td_.make_OpExp(@$, $1, div, $3); }
  | exp "=" exp     { tp.td_.make_OpExp(@$, $1, eq, $3); }
  | exp "<" exp     { tp.td_.make_OpExp(@$, $1, lt, $3); }
  | exp ">" exp     { tp.td_.make_OpExp(@$, $1, gt, $3); }
  | exp "&" exp     { $$ = $1 && $3; }
  | exp "|" exp     { $$ = $1 || $3; }
  | "(" exps ")"    { tp.td_.make_SeqExp(@$, $2); }

  /* Assignment. */
  | lvalue ":=" exp     { tp.td_.make_AssignExp(@$, $1, $3); }

  /* Control structures. */
  | "if" exp "then" exp                     { tp.td_.make_IfExp(@$, $2, $4); }
  | "if" exp "then" exp "else" exp          { tp.td_.make_IfExp(@$, $2, $4, $6); }
  | "while" exp "do" exp                    { tp.td_.make_WhileExp(@$, $2, $4); }
  | "for" ID ":=" exp "to" exp "do" exp     { tp.td_.make_ForExp(@$, make_VarDec(@2, $2, nullptr, $4), $6, $8); }
  | "break"                                 { tp.td_.make_BreakExp(@$); }
  | "let" chunks "in" exp "end"             { tp.td_.make_make_LetExp(@$, $2, $4); }
;

record_r:
     "," ID "=" exp             { tp.td_.make_RecordExp(@$, $2, $4); }
   | "," ID "=" exp record_r    { tp.td_.make_RecordExp(@$, $2, $4); }
;

function_r:
    "," exp                 { tp.ast_ = $2; }
   | "," exp function_r     { tp.ast_ = $2; }
;

lvalue:
    ID                          { tp.td_.make_NameTy(@$, $1); }
  /* Record field access. */
  | lvalue "." ID               { tp.td_.make_FieldVar(@$, $1, $3); }
  /* Array subscript. */
  | lvalue "[" exp "]"          { tp.td_.make_SubscriptVar(@$, $1, $3); }
;

/*---------------.
| Declarations.  |
`---------------*/

%token CHUNKS "_chunks";
chunks:
  /* Chunks are contiguous series of declarations of the same type
     (TypeDec, FunctionDec...) to which we allow certain specific behavior like
     self referencing.
     They are held by a ChunkList, that can be empty, like in this case:
        let
        in
            ..
        end
     which is why we end the recursion with a %empty. */
  %empty                  { $$ = tp.td_.make_ChunkList(@$); }
| tychunk   chunks        { $$ = $2; $$->push_front($1); }
  // FIXME: Some code was deleted here (More rules).
| funchunk   chunks       { $$ = $2; $$->push_front($1); }
| varchunk   chunks       { $$ = $2; $$->push_front($1); }
;
// FIXME: Some code was deleted here (More rules). DONE

  // END FIXME: Some code was deleted here (More rules). DONE
;

varchunk:
     vardec %prec CHUNKS    { $$ = tp.td_.make_VarChunk(@1); $$->push_front(*$1); }
    | vardec tychunk        { $$ = $2; $$->push_front(*$1); }
;

funchunk:
     fundec %prec CHUNKS    { $$ = tp.td_.make_FunctionChunk(@1); $$->push_front(*$1); }
    | fundec tychunk        { $$ = $2; $$->push_front(*$1); }
;

vardec:
 "var" ID ":=" exp                 { $$ = tp.td_.make_VarDec(@$, $2, nullptr, $4); }
 |"var" ID ":" typeid ":=" exp    { $$ = tp.td_.make_VarDec(@$, $2, $4, $6); }
 ;

fundec :
    "function" ID "(" tyfields ")" "=" exp              { tp.td_.make_FunctionDec(@$, $2, make_VarChunk(@4), nullptr, $7); }
  | "function" ID "(" tyfields ")" ":" typeid "=" exp   { tp.td_.make_FunctionDec(@$, $2, make_VarChunk(@4), make_NameTy(@7, $7), $7); }
  | "primitive" ID "(" tyfields ")"                     { tp.td_.make_FunctionDec(@$, $2, make_VarChunk(@4), nullptr, nullptr); }
  | "primitive" ID "(" tyfields ")" ":" typeid          { tp.td_.make_FunctionDec(@$, $2, make_VarChunk(@4), make_NameTy(@7, $7), nullptr); }
;

/*--------------------.
| Type Declarations.  |
`--------------------*/

tychunk:
  /* Use `%prec CHUNKS' to do context-dependent precedence and resolve a
     shift-reduce conflict. */
  tydec %prec CHUNKS  { $$ = tp.td_.make_TypeChunk(@1); $$->push_front(*$1); }
| tydec tychunk       { $$ = $2; $$->push_front(*$1); }
;

tydec:
  "type" ID "=" ty { $$ = tp.td_.make_TypeDec(@$, $2, $4); }
;

ty:
  typeid               { $$ = $1; }
| "{" tyfields "}"     { $$ = tp.td_.make_RecordTy(@$, $2); }
| "array" "of" typeid  { $$ = tp.td_.make_ArrayTy(@$, $3); }
;

tyfields:
  %empty               { $$ = tp.td_.make_fields_type(); }
| tyfields.1           { $$ = $1; }
;

tyfields.1:
  tyfields.1 "," tyfield { $$ = $1; $$->emplace_back($3); }
| tyfield                { $$ = tp.td_.make_fields_type($1); }
;

tyfield:
  ID ":" typeid     { $$ = tp.td_.make_Field(@$, $1, $3); }
;

%token NAMETY "_namety";
typeid:
  ID                    { $$ = tp.td_.make_NameTy(@$, $1); }
  /* This is a metavariable. It it used internally by TWEASTs to retrieve
     already parsed nodes when given an input to parse. */
| NAMETY "(" INT ")"    { $$ = metavar<ast::NameTy>(tp, $3); }
;

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
    std::cerr << l << ":" << m << '\n';
}