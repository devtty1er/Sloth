CFLAGS = -pthread -g -Wall -fPIC -ldl

all : sloth

../resources/qemu/aarch64-linux-user/qemu-aarch64:
	cd ../resources/qemu && CFLAGS="-Wno-unused-command-line-argument  -Wno-unused-but-set-variable" CC=clang CXX=clang++ CXXFLAGS=-fPIC ./configure --enable-linux-user --disable-system --disable-docs --disable-bsd-user --disable-gtk --disable-sdl --disable-vnc --target-list=aarch64-linux-user && make && cd -

../resources/fuzzer/libfuzzer.a: 
	cd ../resources/fuzzer && ./build.sh && cd -

sloth.o: sloth.c
	clang sloth.c -c -o $@

sloth: ../resources/qemu/aarch64-linux-user/qemu-aarch64 ../resources/fuzzer/libfuzzer.a sloth.o
	clang++ $(CFLAGS) sloth.o ../resources/qemu/aarch64-linux-user/qemu-aarch64 ../resources/fuzzer/libFuzzer.a -o $@
	rm sloth.o

clean:
	cd ../resources/qemu && make clean && cd -
	rm sloth
