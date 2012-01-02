#ifndef BSONCONTENT_H_INCLUDED
#define BSONCONTENT_H_INCLUDED

#include "defs.h"
#include <string>

class BSONContent {
    public:
        BSONContent() {}
        virtual ~BSONContent();

        BSONContent(const BSONContent& orig);
        void* _element;

		  BSONTYPE type() const {
			  return _type;
		  };

		  void setType(BSONTYPE type) {
			  _type = type;
		  }

		  bool operator ==(const BSONContent& content);
	protected:
        BSONTYPE _type;
};

#endif // BSONCONTENT_H_INCLUDED
