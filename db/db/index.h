#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED

struct Index {
    char* ns;
    long pos;

    BSONObj* key;
}

#endif // INDEX_H_INCLUDED
