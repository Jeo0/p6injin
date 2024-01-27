CFLAGS = -Wall -Wno-missing-braces -std=c++17 
# static libraylib.a
LINKFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm 
BUILD_MODE ?= DEBUG
ifeq ($(BUILD_MODE), DEBUG)
    CFLAGS += -g -O0 
else
	CFLAGS += -s -O1
endif

#all: objs


#build_me:
	#g++ "src/*.cpp" -c -o obj/main_debug.o\
		#$(CFLAGS) \
		#-I include \
#
#objs: build_me
	#g++ "obj/*.o" -o build/main_debug.exe\
		#-L lib \
		#$(LINKFLAGS)
	#./build/main_debug.exe




default: 
	g++ "src/*.cpp" -o build/main_debug.exe\
		$(CFLAGS) \
		-I include \
		-L lib \
		$(LINKFLAGS)
	./build/main_debug.exe


run:
	./build/main_debug.exe