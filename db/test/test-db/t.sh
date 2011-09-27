gcc -Wall main.cpp \
-lpthread \
-lstdc++ \
-lutil \
-L../../util \
-lbson \
-L../../bson \
-lfilesystem \
-L../../filesystem \
-lcommand \
-L../../command \
-ldb \
-L../../db \
-lnetwork \
-L../../network \
-I../../network \
-I../../filesystem \
-I../../util \
-I../../bson

