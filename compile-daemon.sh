#!/bin/sh

# Let's compile Buysell daemon


cd src/leveldb
make libleveldb.a libmemenv.a
cd ..
make -f makefile.osx
strip buyselld
