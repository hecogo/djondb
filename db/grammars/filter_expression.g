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

start_point returns [BaseExpression* val]
        @init{
	} : filter_expr EOF
	{
	    $val = $filter_expr.val;
	};
	
filter_expr returns [BaseExpression* val]
	:
	boolean_expr {
	$val = $boolean_expr.val;
	} ;

boolean_expr returns [BaseExpression* val]
	:  unary_expr {
	    $val = $unary_expr.val;
	} | binary_expr {
	    $val = $binary_expr.val;
	} | comparison_expr {
	    $val = $comparison_expr.val;
	};
	

binary_expr returns [BaseExpression* val]
@init {
    FILTER_OPERATORS oper = FO_NONE;
    BaseExpression* left = NULL;
    BaseExpression* right = NULL;
    BinaryExpression* result = NULL;
}
@after {
    result = new BinaryExpression(oper);
    result->push(left);
    result->push(right);
}
	:	(u1=unary_expr{
	   left = $u1.val;
	} | (LPAREN b1=binary_expr RPAREN{
	   left = $b1.val;
	}) | (LPAREN c1=comparison_expr RPAREN{
	    left = $c1.val;
	})) OPER_BINARY {
	   oper = parseFilterOperator((char*)$OPER_BINARY.text->chars);
	}(u2=unary_expr{
	   right = $u2.val;
	} | (LPAREN b2=binary_expr RPAREN{
	   right = $b2.val;
	}) | (LPAREN c2=comparison_expr RPAREN{
	    right = $c2.val;
	}));

comparison_expr returns [BaseExpression* val]
@init
{
FILTER_OPERATORS oper = FO_NONE;
BinaryExpression* result = NULL;
}
@after
{
$val = result;
}
	: (LPAREN u1=unary_expr o1=OPER u2=unary_expr RPAREN)
	{
	   oper = parseFilterOperator((char*)$o1.text->chars);
	   result = new BinaryExpression(oper);
	   result->push($u1.val);
	   result->push($u2.val);
	}	| (u3=unary_expr o2=OPER u4=unary_expr )
	{
	   oper = parseFilterOperator((char*)$o2.text->chars);
	   result = new BinaryExpression(oper);
	   result->push($u3.val);
	   result->push($u4.val);
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

OPER	:	('==' | '>' | '>=' | '<' | '<=' );
OPER_BINARY
	:	'and' | 'or';

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
