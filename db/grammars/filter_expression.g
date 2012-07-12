grammar filter_expression;

options {
	language = C;
}

@parser::includes {
//#include <stdlib.h>
   #include <stdlib.h>
   #include <stdio.h>
}
@postinclude
 {
 
 }

start_point returns [void* val]
        @init{
	} : filter_expr EOF 
	{
	};
	
filter_expr returns [char* val]
	: boolean_expr (OR boolean_expr)* (AND boolean_expr)* {
	};

boolean_expr returns [char*]
	: (LPAREN NOT? binary_expr | unary_expr RPAREN) |
	(NOT? binary_expr | unary_expr);
	
binary_expr returns [char* val]
	: (LPAREN (unary_expr) operand_expr (unary_expr) RPAREN) |
	  ((unary_expr) operand_expr (unary_expr));
	
unary_expr returns [char* val]
	: (constant_expr | xpath_expr);
	
xpath_expr returns [char* val]
	: XPATH {
	};

constant_expr returns [char* val]
	: INT | STRING;

operand_expr returns [char* val]
	: OPER;
	
NOT	:	'not';
AND 	:	 'and';
OR	:	'or';

OPER	:	('==' | '>' | '>=' | '<' | '<=');

INT :	'0'..'9'+;

FLOAT
    :   ('0'..'9')+ '.' ('0'..'9')* EXPONENT?
    |   '.' ('0'..'9')+ EXPONENT?
    |   ('0'..'9')+ EXPONENT
    ;

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

WS  :   ( ' '
        | '\t'
        | '\r'
        | '\n'
        ) {$channel=HIDDEN;}
    ;

STRING
    :  ('\'' ( ESC_SEQ | ~('\\'|'\'') )* '\'')|
       ('"' ( ESC_SEQ | ~('\\'|'"') )* '"');

XPATH
    : '$' STRING;


fragment
EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;

fragment
HEX_DIGIT : ('0'..'9'|'a'..'f'|'A'..'F') ;

fragment
ESC_SEQ
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
    |   UNICODE_ESC
    |   OCTAL_ESC
    ;

fragment
OCTAL_ESC
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;

fragment
UNICODE_ESC
    :   '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;

COMMA
	:	',';
LPAREN :	'(';
RPAREN :	')';
LBRAN :	'{';
RBRAN :	'}';
LBRAK
	:	'[';
RBRAK
	:	']';
COLON
	:	':';
SEMICOLON
        :       ';';

// CHAR:  '\'' ( ESC_SEQ | ~('\''|'\\') ) '\''
//    ;
