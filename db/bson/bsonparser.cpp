#include "bsonparser.h"

#include "bsonobj.h"
#include "JSONGrammarParser.h"
#include "JSONGrammarLexer.h"
#include <antlr3.h>
#include <antlr3stringstream.h>
#include <antlr3filestream.h>


struct BSONStruct {
	char* name;
	int type;
	void* value;
	struct BSONStruct* next;
};

BSONParser::BSONParser()
{
	//ctor
}

BSONParser::~BSONParser()
{
	//dtor
}

void freeMemory(struct BSONStruct* s) {
	while (s != NULL) {
		BSONStruct* temp = s->next;
		free(s->name);
		if (s->type == 4) { //BSONStruct
			freeMemory((struct BSONStruct*)s->value);
		} else {
			free(s->value);
		}
		free(s);
		s = temp;
	}
}

BSONObj* convertStruct(struct BSONStruct* param) {
	BSONObj* obj = new BSONObj();
	struct BSONStruct* s = param;
	BSONStruct* head = s;
	while (s != NULL) {
		std::string name(s->name);
		int type = s->type;
		void* value = s->value;
		int* val;
		float* val2;
		char* val3;
		BSONObj* inner;
		switch (type) {
			case 1:
				val = (int*)value;
				obj->add(name, *val);
				break;
			case 2:
				val2 = (float*)value;
				obj->add(name, *val2);
				break;
			case 3:
				val3 = (char*)value;
				obj->add(name, val3);
				break;
			case 4:
				struct BSONStruct* str = (struct BSONStruct*)value;
				inner = convertStruct(str);
				obj->add(name, *inner);
				delete inner;
		}
		s = s->next;
	}

	return obj;
}

BSONObj* BSONParser::parseBSON(const char* c, int& pos) {
	BSONObj* res = new BSONObj();
	int state = 0; // 0 - nothing, 1 - name, 2- value
	char buffer[256];
	char* name = NULL;
	void* value = NULL;
	int len = 0;
	BSONTYPE type;
	int stringOpen = 0; // 0 - closed
	// 1 - Single quote opened
	// 2 - Double quote opened	
	int x;
	for (x= pos; x < strlen(c); x++) {
		if (c[x] == '{') {
			if (state == 2) {
				value = parseBSON(c, x);
				type = BSON_TYPE;
			} else if (state == 0) {
				memset(buffer, 0, 256);
				state = 1;// name
				type = INT_TYPE;
			} else { // state == 1
				throw "json value is not allowed as name";
			}
			continue;
		}
		if (c[x] == '}' || c[x] == ',') {
			if (name != NULL) {
				if (type != BSON_TYPE) {
					value = (char*)malloc(len+1); 
					memset(value, 0, len + 1);
					strcpy((char*)value, buffer);
				}
				len = 0;
				memset(buffer, 0, 256);
				switch (type) {
					case INT_TYPE:{
										  int iVal = atoi((char*)value);
										  res->add(name, iVal);
										  break;
									  }
					case DOUBLE_TYPE: {
												double dVal = atof((char*)value);
												res->add(name, dVal);
												break;
											}
					case STRING_TYPE:
											{
												res->add(name, (char*)value);
												break;
											}
					case BSON_TYPE:
											{
												res->add(name, *((BSONObj*)value));
												delete (BSONObj*)value;
											}

				}
				free(name);
				name = NULL;
				if (type != BSON_TYPE) {
					free(value);
					value = NULL;
				}
				if (c[x] == '}')
					break;
				else {
					state = 1; // name
					type = INT_TYPE;
					continue;
				}
			}
		}
		if (c[x] == ':') {
			name = (char*)malloc(len+1);
			memset(name, 0, len + 1);
			strcpy(name, buffer);
			len = 0;
			memset(buffer, 0, 256);
			state = 2; //value
		} else {
			if (c[x] == '\'') {
				if (stringOpen == 1) {
					stringOpen = 0;
					continue;
				}
				if (stringOpen == 0) {
					stringOpen = 1;
					if (state == 2) {
						type = STRING_TYPE;
					}
					continue;
				}
			}
			if (c[x] == '\"') {
				if (stringOpen == 2) {
					stringOpen = 0;
					continue;
				}
				if (stringOpen == 0) {
					stringOpen = 2;
					if (state == 2) {
						type = STRING_TYPE;
					}
					continue;
				}
			}
			if (c[x] == ' ' && stringOpen == 0) {
				continue;
			}
			if (c[x] == '\r' || c[x] == '\n') {
				continue;
			}
			if (c[x] == '.' && state == 2) {
				type = DOUBLE_TYPE;
			}
			buffer[len] = c[x];
			len++;
		}

	}
	pos = x;
	return res;
}

BSONObj* BSONParser::parse(const std::string& sbson) {

	const char* c = sbson.c_str();

	BSONObj* res = NULL;
	for (int x= 0; x < strlen(c); x++) {
		if (c[x] == '{') {
			res = parseBSON(c, x);
			break;
		}

	}
	return res;
}
