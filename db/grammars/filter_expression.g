grammar filter_expression;

options {
	language = C;
}

@parser::includes {
//#include <stdlib.h>
   #include "filterparser.h"
   #include "filterdefs.h"
   #include "constantexpression.h"
   #include "unaryexpression.h"
   #include "simpleexpression.h"
   #include "binaryexpression.h"
   #include <stdlib.h>
   #include <stdio.h>
   #include <strings.h>
   
}

/*
@postinclude {
static void displayRecognitionErrorNew  (pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 * tokenNames) throw(ParseException)
{ 
    switch (recognizer->state->exception->type) {
    	case ANTLR3_UNWANTED_TOKEN_EXCEPTION:
		break;
	default:
		throw ParseException(1, "error");
    }
}
 }

@parser::apifuncs {
  RECOGNIZER->displayRecognitionError       = displayRecognitionErrorNew;
//  RECOGNIZER->antlr3RecognitionExceptionNew = antlr3RecognitionExceptionNewNew;
//  RECOGNIZER->mismatch                      = mismatchNew;
}
*/

start_point returns [BaseExpression* val]
        @init{
	} : filter_expr EOF 
	{
	    $val = $filter_expr.val;
	};
	
filter_expr returns [BaseExpression* val]
	 @init {
	 BaseExpression* result = NULL;
	}
	@after {
	   $val = result;
	}:
	 b1=boolean_expr {
	        BaseExpression* expr1 = $b1.val;
	        result = expr1;
	}
	(OR b2=boolean_expr{
	    BaseExpression* expr2 = $b2.val;
	    BinaryExpression* binary = new BinaryExpression(FO_OR);
	    binary->push(result);
	    binary->push(expr2);
	    result = binary;
	})* 
	 (AND b3=boolean_expr{
	    BaseExpression* expr3 = $b3.val;
	    BinaryExpression* binary = new BinaryExpression(FO_AND);
	    binary->push(result);
	    binary->push(expr3);
	    result = binary;
	})* ;

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
	:	binary_noparent_expr 
	{
	   $val = $binary_noparent_expr.val;
	} | binary_parent_expr {
	   $val = $binary_parent_expr.val;
	};
		
binary_noparent_expr returns [BaseExpression* val]
@init {
FILTER_OPERATORS oper;
BinaryExpression* result = NULL;
}
@after {
   $val = result;
}
	:
	  (b1=unary_expr ) o=operand_expr b2=unary_expr {
  	      oper = parseFilterOperator((char*)$o.text->chars);
	      result = new BinaryExpression(oper);
	      result->push($b1.val);
	      result->push($b2.val);
	  };

binary_parent_expr  returns [BaseExpression* val]
	: LPAREN binary_expr RPAREN {
	$val = $binary_expr.val;
	};
	
unary_expr returns [BaseExpression* val]
	@init {
	     val = NULL;
	}
	: (c1=constant_expr {
	        $val = c1;
	} | x1=xpath_expr {
	        $val = x1;
	});
	
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
	    char* ptext = (char*)$STRING.text->chars;
	    char* text = (char*)malloc(strlen(ptext) - 1);
	    memset(text, 0, strlen(ptext) - 1);
	    memcpy(text, ptext + 1, strlen(ptext) - 2);
	    
	    $val = new ConstantExpression(text);
	    free (text);
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
