CFLAGS=`pkg-config --cflags taglib`
LIBS="`pkg-config --libs taglib` -ljsoncpp"

g++ $CFLAGS $LIBS -std=c++11 -otagsync src/tagsync.cpp
