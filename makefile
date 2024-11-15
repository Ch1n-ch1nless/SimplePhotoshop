CC=g++
CFLAGS= -D _DEBUG -ggdb3 -std=c++17 -O2 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat\
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

GRAPHICS_SRC_DIR = ./source/Graphics/
GRAPHICS_OBJ_DIR = ./object/Graphics/

STANDARD_SRC_DIR 	= ./source/Standard/
STANDARD_OBJ_DIR 	= ./object/Standard/

VIEW_SRC_DIR		= ./source/View/
VIEW_OBJ_DIR 		= ./object/View/

MAIN_SRC = ./source/main.cpp
MAIN_OBJ = ./object/main.o

PLUGINS_DIR = ./Plugins/

PLUGINS = $(wildcard $(PLUGINS_DIR)*.so)

SYSTEM_PLUGINS_SRC_DIR = ./source/SystemPlugins/
SYSTEM_PLUGINS_OBJ_DIR = ./object/SystemPlugins/

GRAPHICS_SRC = $(wildcard $(GRAPHICS_SRC_DIR)*.cpp)
GRAPHICS_OBJ = $(patsubst $(GRAPHICS_SRC_DIR)%.cpp, $(GRAPHICS_OBJ_DIR)%.o, $(GRAPHICS_SRC))

STANDARD_SRC = $(wildcard $(STANDARD_SRC_DIR)*.cpp)
STANDARD_OBJ = $(patsubst $(STANDARD_SRC_DIR)%.cpp, $(STANDARD_OBJ_DIR)%.o, $(STANDARD_SRC))

VIEW_SRC	 = $(wildcard $(VIEW_SRC_DIR)*.cpp)
VIEW_OBJ	 = $(patsubst $(VIEW_SRC_DIR)%.cpp, $(VIEW_OBJ_DIR)%.o, $(VIEW_SRC))

SYSTEM_PLUGINS_SRC	 = $(wildcard $(SYSTEM_PLUGINS_SRC_DIR)*.cpp)
SYSTEM_PLUGINS_OBJ	 = $(patsubst $(SYSTEM_PLUGINS_SRC_DIR)%.cpp, $(SYSTEM_PLUGINS_OBJ_DIR)%.o, $(SYSTEM_PLUGINS_SRC))

all: link

link: build_sys_plugins
	$(CC) object/main.o -o photoshop.out -L./Plugins/ -Wl,-rpath=./Plugins -lapi_impl -L./Plugins/ -ltool_bar -L./Plugins/ -lpencil_button -L./Plugins/ -lcat_button -L./Plugins/ -lbrush_button -L./Plugins/ -leraser_button -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

build_sys_plugins: $(GRAPHICS_OBJ) $(STANDARD_OBJ) $(VIEW_OBJ) $(SYSTEM_PLUGINS_OBJ) $(MAIN_OBJ)
	$(CC) -shared -o Plugins/libapi_impl.so $(GRAPHICS_OBJ) $(VIEW_OBJ) $(STANDARD_OBJ) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
	$(CC) -shared -o Plugins/libpencil_button.so object/SystemPlugins/pencil_button.o -L./Plugins/ -lapi_impl
	$(CC) -shared -o Plugins/libtool_bar.so object/SystemPlugins/tool_bar.o -L./Plugins/ -lapi_impl
	$(CC) -shared -o Plugins/libcat_button.so object/SystemPlugins/cat_button.o -L./Plugins/ -lapi_impl
	$(CC) -shared -o Plugins/libbrush_button.so object/SystemPlugins/brush_button.o -L./Plugins/ -lapi_impl
	$(CC) -shared -o Plugins/liberaser_button.so object/SystemPlugins/eraser_button.o -L./Plugins/ -lapi_impl
	$(CC) -shared -o Plugins/libnegative_filter.so object/SystemPlugins/negative_filter.o -L./Plugins/ -lapi_impl
	$(CC) -shared -o Plugins/libbump_filter.so object/SystemPlugins/bump_filter.o -L./Plugins/ -lapi_impl

$(GRAPHICS_OBJ_DIR)%.o : $(GRAPHICS_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

$(STANDARD_OBJ_DIR)%.o : $(STANDARD_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

$(VIEW_OBJ_DIR)%.o : $(VIEW_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

$(SYSTEM_PLUGINS_OBJ_DIR)%.o : $(SYSTEM_PLUGINS_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

$(MAIN_OBJ) : $(MAIN_SRC)
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

clean:
	rm $(GRAPHICS_OBJ) $(MAIN_OBJ) $(VIEW_OBJ) $(STANDARD_OBJ) $(SYSTEM_PLUGINS_OBJ)
 
build:
	mkdir object              		&& \
	mkdir $(GRAPHICS_OBJ_DIR) 		&& \
	mkdir $(STANDARD_OBJ_DIR) 		&& \
	mkdir $(VIEW_OBJ_DIR)	  		&& \
	mkdir $(SYSTEM_PLUGINS_OBJ_DIR)