CORE_DIR = $(CORELPC_DIR)

CORE_SRC_DIRS = cores libraries system variants
CORE_SRC = $(addprefix $(CORE_DIR)/, $(CORE_SRC_DIRS))


#Find all c and c++ files for Core
CORE_OBJ_SRC_C    += $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.c $(src)/*/*.c $(src)/*/*/*.c $(src)/*/*/*/*.c) )
CORE_OBJ_SRC_CXX    += $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.cpp $(src)/*/*.cpp $(src)/*/*/*.cpp $(src)/*/*/*/*.cpp) )

#all object files for core
CORE_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(CORE_OBJ_SRC_C)) $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CORE_OBJ_SRC_CXX))

#Find all headers
CORE_HEADERS = $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.h $(src)/*/*.h $(src)/*/*/*.h $(src)/*/*/*/*.h $(src)/*/*/*/*/*.h) )
#generate the paths that have headers files to include
CORE_HEADERS += $(CORE_DIR)/cores/mbed/

CORE_HEADERS_DIRS = $(call uniq,$(dir $(CORE_HEADERS)))
CORE_INCLUDES = $(addprefix -I, $(CORE_HEADERS_DIRS))
