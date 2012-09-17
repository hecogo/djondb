grammar test;

start_point 
        : filter_expr EOF
	;
	
filter_expr 
	:
	boolean_expr ;

/*complex_expr
	:	(boolean_expr | (LPAREN boolean_expr RPAREN)) (OPER (boolean_expr | (LPAREN boolean_expr RPAREN)))*;
*/	
boolean_expr
	:	boolean_term (OR boolean_term)*;

boolean_term
	:	boolean_value (AND boolean_value)*;
	
boolean_value
	:	parenthesized_boolean |
	nonparentherized_boolean;	
	
parenthesized_boolean
	: LPAREN boolean_expr RPAREN;
	
nonparentherized_boolean: unary_expr ( OPER unary_expr)*;
		
unary_expr 
	 
	: (x1=xpath_expr  | c1=constant_expr );
	
xpath_expr 
	: XPATH ;

constant_expr 
	: (INT
	 | STRING);

operand_expr 
	: OPER;
	
NOT	:	'not';
AND	:	'and';
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
