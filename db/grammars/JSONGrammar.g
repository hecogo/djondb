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
   struct BSONStruct {
        char* name;
        int type;
        void* value;
        struct BSONStruct* next;
   };
   struct BSONStruct* bson_root;
   struct BSONStruct* bson_current;
   
   struct Stack {
       struct Stack* _last;
       struct BSONStruct* _element;
   };
   
   struct Stack* _stack;
//   char* str_name;
//   int str_type;
//   void* str_value;
   int _temp;
   
   void push(struct BSONStruct* element) {
   	_stack->_element = element;
   	struct Stack* lastElement = (struct Stack*)malloc(sizeof(struct Stack));
   	lastElement->_last = _stack;
   	_stack = lastElement;
   }
   
   struct BSONStruct* pop() {
        struct Stack* stack = _stack->_last;
        free(_stack);
        _stack = stack;
        if (_stack != NULL) {
            return _stack->_element;
        } else {
            return NULL;
        }
   }
 }

start_point returns [void* val]
        @init{
           _temp = 0;
	   bson_root = NULL;
	   bson_current = NULL;
	   _stack = (struct Stack*)malloc(sizeof(struct Stack));
	   _stack->_last = NULL;
	   _stack->_element = NULL;
	}
		: object_expr EOF {
		$val = bson_root;
		};
	
object_expr returns [struct BSONStruct* val]
@init{
	  if (bson_root != NULL) {
	   	push(bson_root);
	   	bson_root = NULL;
	   }
}	
	:  LBRAN pair (COMMA pair)* RBRAN 
	{
	    $val = bson_root;
	    struct BSONStruct* temp = pop();
	    if (temp != NULL) {
	       bson_root = temp;
	       bson_current = bson_root;
	       while (bson_current->next != NULL) {
	          bson_current =bson_current->next ;
	       }
	     }
	};

array_expr
	: LBRAK value (COMMA value)* RBRAK;
	
pair
	: name COLON value {
             struct BSONStruct* element = (struct BSONStruct*)malloc(sizeof(struct BSONStruct));
             element->next = NULL;
             element->name = (char*)malloc(strlen($name.val)+1);
             memset(element->name, 0, strlen($name.val) + 1);
             memcpy(element->name, $name.val, strlen($name.val));
             element->type = $value.type;
             element->value = $value.val;
             if (bson_root == NULL) {
                bson_root = element;
                bson_current = bson_root;
             } else {
                bson_current->next = element;
                bson_current = element;
             }
	};
	
name returns [char* val]
	:	ID {
	     $val = $ID.text->chars;
	};

value returns [void* val, int type]
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
	}
	| object_expr 
	{
	  $type = 4;
	  $val = $object_expr.val;
	}
	| array_expr);

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
