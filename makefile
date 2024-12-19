CC=g++
CFLAGS= -D _DEBUG -ggdb3 -std=c++20 -O2 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat\
	    -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion\
	    -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness\
	    -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked\
		-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel\
		-Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override\
		-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros\
		-Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector\
		-fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer\
		-Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla 
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr \
		-Wl,--export-dynamic

GRAPHICS_SRC_DIR 	= ./source/Graphics/
GRAPHICS_OBJ_DIR 	= ./object/Graphics/

STANDARD_SRC_DIR 	= ./api/
STANDARD_OBJ_DIR 	= ./object/api/

MAIN_SRC = ./source/main.cpp
MAIN_OBJ = ./object/main.o

GRAPHICS_SRC = $(wildcard $(GRAPHICS_SRC_DIR)*.cpp)
GRAPHICS_OBJ = $(patsubst $(GRAPHICS_SRC_DIR)%.cpp, $(GRAPHICS_OBJ_DIR)%.o, $(GRAPHICS_SRC))

STANDARD_SRC = $(wildcard $(STANDARD_SRC_DIR)*.cpp)
STANDARD_OBJ = $(patsubst $(STANDARD_SRC_DIR)%.cpp, $(STANDARD_OBJ_DIR)%.o, $(STANDARD_SRC))

all: link

link: build_impl $(MAIN_OBJ)
	$(CC) object/main.o -o photoshop.out -L./plugins -Wl,-rpath=./plugins -lsfm_impl -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

$(MAIN_OBJ) : $(MAIN_SRC)
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

build_impl: $(GRAPHICS_OBJ) $(STANDARD_OBJ)
	$(CC) -shared $(GRAPHICS_OBJ) $(STANDARD_OBJ) -o ./plugins/libsfm_impl.so -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

$(GRAPHICS_OBJ_DIR)%.o : $(GRAPHICS_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

$(STANDARD_OBJ_DIR)%.o : $(STANDARD_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

clean:
	rm $(GRAPHICS_OBJ) $(MAIN_OBJ) $(STANDARD_OBJ)
	rm -f ./plugins/libsfm_impl.so
 
build:
	mkdir plugins					&& \
	mkdir object              		&& \
	mkdir $(GRAPHICS_OBJ_DIR)		&& \
	mkdir $(STANDARD_OBJ_DIR)