grammar JSONGrammar;

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
	}
		: filter_expr EOF {
		};
	
filter_expr returns [char* val]
	: path_expr {
	};

path_expr returns [char* val]
	: XPATH {
	};

element returns [void* val, int type]
	:	
	(INT 
	{ 
	  $type = 1;
	  $val = malloc(sizeof(int));
	  char* t = $INT.text->chars;
	  *(int*)$val = atoi(t);
	}
	| FLOAT 
	{ 
	  $type = 2;
	  $val = malloc(sizeof(float));
	  char* t2 = $FLOAT.text->chars;
	  *(float*)$val = atof(t2);
	}
	| STRING 
	{ 
	  $type = 3;
	  char* t3 = $STRING.text->chars;
	  // Dont copy the quotes
	  char* temp = malloc(strlen(t3)-1);
	  memset(temp, 0, strlen(t3) -1);
	  strncpy(temp, t3+1, strlen(t3)-2); //, strlen(t3)
	  $val = temp;
	});

ID  :	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
    ;

INT :	'0'..'9'+
    ;

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
LBRAN
	:	'{';
RBRAN
	:	'}';
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
