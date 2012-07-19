grammar test;

start_point 
        @init{
	} : filter_expr EOF 
;
	
filter_expr 
	 @init {
	}
	@after {
	}:
	 b1=boolean_expr {
	}
	(OR b2=boolean_expr{
	})* 
	 (AND b3=boolean_expr{
	})* ;

boolean_expr
	: 
	NOT? b3=binary_expr 
	{
	}
	| b4=unary_expr {
	};
	
binary_expr 
	:	binary_noparent_expr 
	{
	} | binary_parent_expr {
	};
		
binary_noparent_expr 
@init {
}
@after {
}
	:
	  (b1=unary_expr ) o=operand_expr b2=unary_expr {
	  };

binary_parent_expr  
	: LPAREN binary_expr RPAREN {
	};
	
unary_expr 
	@init {
	}
	: (c1=constant_expr {
	} | x1=xpath_expr {
	});
	
xpath_expr 
	: XPATH {
	};

constant_expr 
	: (INT
	{
	} | STRING{
	});

operand_expr 
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
