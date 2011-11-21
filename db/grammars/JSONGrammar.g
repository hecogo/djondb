grammar JSONGrammar;

options {
	language = C;
}
@postinclude
 {
   struct BSONStruct {
        char* name;
        int type;
        void* value;
        struct BSONStruct* next;
   };
   struct BSONStruct* bson_root;
   struct BSONStruct* bson_current;
   
   char* str_name;
   int str_type;
   void* str_value;
 }
@parser::includes {
//#include <stdlib.h>
}

start_point returns [void* val]
        @init{
	   bson_root = NULL;
	   bson_current = NULL;
	}
		: object_expr EOF {
		$val = bson_root;
		};
	
object_expr	
	:  LBRAN pair (COMMA pair)* RBRAN 
	{
	};

array_expr
	: LBRAK value (COMMA value)* RBRAK;
	
pair
	: name COLON value {
             struct BSONStruct* element = (struct BSONStruct*)malloc(sizeof(struct BSONStruct));
             element->next = NULL;
             element->name = (char*)malloc(strlen(str_name)+1);
             memset(element->name, 0, strlen(str_name) + 1);
             memcpy(element->name, str_name, strlen(str_name));
             element->type = str_type;
             element->value = str_value;
             if (bson_root == NULL) {
                bson_root = element;
                bson_current = bson_root;
             } else {
                bson_current->next = element;
                bson_current = element;
             }
	};
	
name
	:	ID {
	     str_name = $ID.text->chars;
	};

value
	:	
	(INT 
	{ 
	  str_type = 1;
	  int* valInt = malloc(sizeof(int));
	  char* t = $INT.text->chars;
	  *valInt = atoi(t);
	  
	  str_value = valInt;
	}
	| FLOAT 
	{ 
	  str_type = 2;
	  float* valFloat = malloc(sizeof(float));
	  char* t2 = $FLOAT.text->chars;
	  *valFloat = atof(t2);
	  
	  str_value = valFloat;
	}
	| STRING 
	{ 
	  str_type = 3;
	  char* t3 = $STRING.text->chars;
	  char* text = malloc(strlen(t3) + 1);
	  memset(text, 0, strlen(t3) + 1);
	  memcpy(text, t3, strlen(t3));
	  
	  str_value = text;
	}| object_expr | array_expr);

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
    :  '\'' ( ESC_SEQ | ~('\\'|'\'') )* '\''
    ;

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
