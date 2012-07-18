grammar filter_expression;

options {
	language = C;
}

@parser::includes {
//#include <stdlib.h>
   #include <stdlib.h>
   #include <stdio.h>
   #include "filterparser.h"
   #include "filterdefs.h"
   #include "constantexpression.h"
   #include "unaryexpression.h"
   #include "simpleexpression.h"
   #include "binaryexpression.h"
   
}
@postinclude
 {
 
 }

start_point returns [BaseExpression* val]
        @init{
	} : filter_expr EOF 
	{
	    $val = $filter_expr.val;
	};
	
filter_expr returns [BaseExpression* val]
	: b1=boolean_expr (OR b2=boolean_expr)* (AND b3=boolean_expr)* {
		BaseExpression* expr1 = $b1.val;
		BaseExpression* result = expr1;
		if ($b2.val != NULL) {
		    BaseExpression* expr2 = $b2.val;
		    BinaryExpression* binary = new BinaryExpression(FO_OR);
		    binary->push(result);
		    binary->push(expr2);
		    result = binary;
		}
		if ($b3.val != NULL) {
		    BaseExpression* expr3 = $b3.val;
		    BinaryExpression* binary = new BinaryExpression(FO_AND);
		    binary->push(result);
		    binary->push(expr3);
		    result = binary;
		}
		val = result;
	};

boolean_expr returns [BaseExpression* val]
	: 
	(NOT? (b3=binary_expr 
	{
	    $val = $b3.val;
	}
	| b4=unary_expr {
	    $val = $b4.val;
	}	
	));
	
binary_expr returns [BaseExpression* val]
	: (LPAREN (b1=unary_expr) o1=operand_expr (b2=unary_expr) RPAREN) |
	  ((b3=unary_expr) o2=operand_expr (b4=unary_expr)) {
	  	FILTER_OPERATORS oper;
	  	BaseExpression* e1 = NULL;
	  	BaseExpression* e2 = NULL;
	  	if ($o1.text != NULL) {
	  	   oper = parseFilterOperator((char*)$o1.text->chars);
	  	   e1 = $b1.val;
	  	   e2 = $b2.val;
	  	} else if ($o2.text != NULL) {
	  	   oper = parseFilterOperator((char*)$o2.text->chars);
	  	   e1 = $b3.val;
	  	   e2 = $b4.val;
	  	}
	  	BinaryExpression* result = new BinaryExpression(oper);
	  	result->push(e1);
	  	result->push(e2);
	  	$val = result;
	  };
	
unary_expr returns [BaseExpression* val]
	: (c1=constant_expr | x1=xpath_expr) {
		if ($c1.val != NULL) {
		   $val = c1;
		} else {
		   $val = x1;
		}
	};
	
xpath_expr returns [BaseExpression* val]
	: XPATH {
	     char* text = (char*)$XPATH.text->chars;
	     SimpleExpression* result = new SimpleExpression(text);
	     $val = result;
	};

constant_expr returns [BaseExpression* val]
	: (INT
	{
	    int i = atoi((char*)$INT.text->chars);
	    $val = new ConstantExpression(i);
	} | STRING{
	    $val = new ConstantExpression((char*)$STRING.text->chars);
	});

operand_expr returns [BaseExpression* val]
	: OPER;
	
NOT	:	'not';
AND 	:	 'and';
OR	:	'or';

OPER	:	('==' | '>' | '>=' | '<' | '<=' | AND | OR);

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

STRING 		: 	'\"' ( options{ greedy=false; }: (~('\"') | ('\\"')) )* '\"' | '\'' ( options{ greedy=false; }: (~('\'') | ('\\\'')) )* '\'' ;

DOLLAR 	:	 '$';
XPATH
    : DOLLAR STRING;


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
