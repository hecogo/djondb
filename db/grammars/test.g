grammar test;

start_point  : filter_expr EOF
;
	
filter_expr 
	:
	boolean_expr ;

boolean_expr 
	:   (unary_expr  |  binary_expr | comparison_expr);
	

	
binary_expr 
	: (side_expr ) OPER_BINARY 	(side_expr);
	
side_expr
	: u1=unary_expr | binary_paren_expr | (LPAREN c1=comparison_expr RPAREN);
	
binary_paren_expr
:(LPAREN b2=binary_expr RPAREN
	 );

comparison_expr 
	: (LPAREN u1=unary_expr o1=OPER u2=unary_expr RPAREN)
	| (u3=unary_expr o2=OPER u4=unary_expr );
		
unary_expr 
	: (c1=constant_expr  | x1=xpath_expr );
	
xpath_expr 
	: XPATH ;

constant_expr returns [BaseExpression* val]
	: (INT  | STRING);

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
