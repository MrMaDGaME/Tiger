                                                            /* -*- C++ -*- */
%option c++
%option nounput
%option debug
%option batch

%{

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>

  // FIXME: Some code was deleted here.
  // yy::parser::location_type tp.location_
  // END_FIXME

// Convenient shortcuts.
#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)


// Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
  } while (false)

YY_FLEX_NAMESPACE_BEGIN
%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+
/* DONE: Some code was deleted here. */
identifier      [a-zA-Z]+[a-zA-Z0-9_]*
// END_FIXME
%%
%{
  // DONE: Some code was deleted here (Local variables).

    #define YY_USER_ACTION
    do {
        tp.location_.columns(yyleng);
    } while (false);
  // END_FIXME
  // Each time yylex is called.
  tp.location_.step();
}%

 /* The rules.  */
{int}         {
                // DONE: Some code was deleted here (Decode, and check the value).
                int val = std::stoi(yytext);
                return TOKEN_VAL(INT, val);
              }

  /* DONE: Some code was deleted here. */
"_main"       return TOKEN_VAL(ID, yytext);
{identifier}  return TOKEN_VAL(ID,yytext);
.             {
                    std::cerr << "unexpected character: " << yytext << '\n';

              }
%%

// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
