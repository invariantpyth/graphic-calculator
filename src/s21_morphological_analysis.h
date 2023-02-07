#ifndef SRC_MORPHOLOGICAL_ANALYSIS_H_
#define SRC_MORPHOLOGICAL_ANALYSIS_H_
#define OPERATORS_COUNT 19
const char sin_o[] = "sin";
const char cos_o[] = "cos";
const char tan_o[] = "tan";
const char acos_o[] = "acos";
const char asin_o[] = "asin";
const char atan_o[] = "atan";
const char sqrt_o[] = "sqrt";
const char ln_o[] = "ln";
const char log_o[] = "log";
const char mod_o[] = "mod";
const char open_parenthesis[] = "(";
const char close_parenthesis[] = ")";
const char plus[] = "+";
const char minus[] = "-";
const char multiply[] = "*";
const char divide[] = "/";
const char power[] = "*";
const char unary_plus[] = "+";
const char unary_minus[] = "-";
const char* operators[] = {sin_o,
                           cos_o,
                           tan_o,
                           acos_o,
                           asin_o,
                           atan_o,
                           sqrt_o,
                           ln_o,
                           log_o,
                           mod_o,
                           open_parenthesis,
                           close_parenthesis,
                           plus,
                           minus,
                           multiply,
                           divide,
                           power,
                           unary_minus,
                           unary_plus};
const char variable[] = "x";


char* which_operator(char* operator, int is_unary);
double atof(char* number);
size_t is_operator(char* str);
size_t is_number(char* str);
char** parse(char* input_string);

#endif  // SRC_MORPHOLOGICAL_ANALYSIS_H_