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
identifier      [a-zA-Z][a-zA-Z0-9_]*
end_of_line     [\n\r]+
white_character [\t ]
  /* FIXME: Some code was deleted here. */
%%

%{
  // FIXME: Some code was deleted here (Local variables) prob ln 88 a 98.
  std::string grown_string;
  int com_count = 0;

  #define YY_USER_ACTION
     do {
        tp.location_.columns(yyleng);
     } while (false);
  // Each time yylex is called.
  tp.location_.step();
%}

 /* The rules.  */
"_chunks"       return TOKEN(CHUNKS);

"_exp"          return TOKEN(EXP);

"_lvalue"       return TOKEN(LVALUE);

"_namety"       return TOKEN(NAMETY);

"if"            return TOKEN(IF);

"array"         return TOKEN(ARRAY);

":="            return TOKEN(ASSIGN);

"break"         return TOKEN(BREAK);

"_cast"         return TOKEN(CAST);

"class"         return TOKEN(CLASS);

"&"             return TOKEN(AND);

":"             return TOKEN(COLON);

","             return TOKEN(COMMA);

"/"             return TOKEN(DIVIDE);

"do"            return TOKEN(DO);

"."             return TOKEN(DOT);

"else"          return TOKEN(ELSE);

"end"           return TOKEN(END);

"="             return TOKEN(EQ);

"extends"       return TOKEN(EXTENDS);

"for"           return TOKEN(FOR);

"function"      return TOKEN(FUNCTION);

">="            return TOKEN(GE);

">"             return TOKEN(GT);

"import"        return TOKEN(IMPORT);

"in"            return TOKEN(IN);

"{"             return TOKEN(LBRACE);

"["             return TOKEN(LBRACK);

"<="            return TOKEN(LE);

"let"           return TOKEN(LET);

"("             return TOKEN(LPAREN);

"<"             return TOKEN(LT);

"-"             return TOKEN(MINUS);

"method"        return TOKEN(METHOD);

"<>"            return TOKEN(NE);

"new"           return TOKEN(NEW);

"nil"           return TOKEN(NIL);

"of"            return TOKEN(OF);

"|"             return TOKEN(OR);

"+"             return TOKEN(PLUS);

"primitive"     return TOKEN(PRIMITIVE);

"}"             return TOKEN(RBRACE);

"]"             return TOKEN(RBRACK);

")"             return TOKEN(RPAREN);

";"             return TOKEN(SEMI);

"then"          return TOKEN(THEN);

"*"             return TOKEN(TIMES);

"to"            return TOKEN(TO);

"type"         return TOKEN(TYPE);

"var"           return TOKEN(VAR);

"while"         return TOKEN(WHILE);


{int}         {
                int val = std::stoi(yytext);
                if (val < INT_MIN || val > INT_MAX)
                {
                    tp.error_ << misc::error::error_type::scan << tp.location_ << ": int out_of_bound: " << misc::escape(yytext) << '\n';
                }
                return TOKEN_VAL(INT, val);
              }

"\""        { grown_string.clear();
              grown_string.append("\"");
              BEGIN SC_STRING; }

<SC_STRING>{
                    "\""    { BEGIN INITIAL; grown_string.append("\""); return TOKEN_VAL(STRING, grown_string); }
                    "\\\\"  { grown_string.append("\\\\"); }
                    "\\\""  { grown_string.append("\\\""); }
                    "\\a"   { grown_string.append("\\a"); }
                    "\\b"   { grown_string.append("\\b"); }
                    "\\f"   { grown_string.append("\\f"); }
                    "\\n"   { grown_string.append("\\n"); }
                    "\\r"   { grown_string.append("\\r"); }
                    "\\t"   { grown_string.append("\\t"); }
                    "\\v"   { grown_string.append("\\v"); }
                    [0-9]   { grown_string.append(yytext); }
                    [a-zA-Z]    { grown_string.append(yytext); }
                    \\[0-3][0-7]{2}   { grown_string.append(1, strtol(yytext + 1, 0, 8)); }
                    \\x[0-9a-fA-F]{2}  { grown_string.append(1, strtol(yytext + 2, 0, 16)); }
                    <<EOF>> { tp.error_ << misc::error::error_type::scan << tp.location_ << ": unterminated string : " << misc::escape(yytext) << '\n' ; BEGIN INITIAL;}
                    .   { grown_string.append(yytext); }
}

"/*"        {   com_count++;
                BEGIN SC_COMMENT;}

<SC_COMMENT>{
                "*/"    {com_count--; if(com_count==0) BEGIN INITIAL; tp.location_.step();}
                "/*"    {com_count++; tp.location_.step();}
                <<EOF>> { tp.error_ << misc::error::error_type::scan << tp.location_ << ": unterminated comment : " << misc::escape(yytext) << '\n' ;
                          BEGIN INITIAL;}
                .       {tp.location_.step();}
            }

{end_of_line}     {
                      tp.location_.lines(yyleng);
                      tp.location_.step();
                  }

{white_character} tp.location_.step();

"_main"         return TOKEN_VAL(ID, "_main");

{identifier}    {
                    std::string str(yytext);
                    auto res = misc::symbol(str);
                    return TOKEN_VAL(ID,res);
                }

<<EOF>>         return TOKEN(EOF);


.             {
                  tp.error_ << misc::error::error_type::scan
                                  << tp.location_
                                  << ": invalid identifier: `"
                                  << misc::escape(yytext) << "'\n";
                  //return TOKEN(UNKOWN);
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
