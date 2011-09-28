
gcc -Wall main.cpp \
-lpthread \
-lstdc++ \
-ldb \
-L../../db \
-lnetwork \
-L../../network \
-lcommand \
-L../../command \
-lfilesystem \
-L../../filesystem \
-lbson \
-L../../bson \
-lutil \
-L../../util \
-I../../filesystem \
-I../../util \
-I../../bson \
-I../../network

