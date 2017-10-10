# GNUmakefile
#		(c) S.Suzuki 2017.1.16 ————— patch 2017.9.14

NAME    := RayTrace2D

SUFFIX  := .cpp

SRC_DIR := ./src
INC_DIR := ./include
OBJ_DIR := ./obj
EXE_DIR := ./bin

COMPILER:= g++

#==============================================#

# cross platform make
UNAME   := $(shell uname)
ifeq ($(UNAME), Darwin)
CFLAGS  := -Wall -O2 -std=c++11
FRAME   := -framework GLUT -framework OpenGL 
endif
ifeq ($(UNAME), Linux)
CFLAGS  := -w -O2 -I/usr/X11R6/include -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm -lpthread
endif

SOURCES := $(wildcard $(SRC_DIR)/*$(SUFFIX))
HEADERS := $(wildcard $(INC_DIR)/*.h)
OBJECTS := $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:%$(SUFFIX)=%.o)))
TARGETS := $(notdir $(basename $(SOURCES)))

OPTIONS := $(FRAME) $(addprefix -I,$(INC_DIR)) $(CFLAGS) $(addprefix -L,$(LIB_DIR)) $(LIBRARY)

TAR     := 0
TARNUM  := $(words $(TARGETS))

# make commands
.PHONY:all info build run clean
all: build 
	@echo "\t————————————————————————————————————————————— "
	@echo "\t  Complete to create $(NAME) into $(EXE_DIR)  "
	@echo "\t     Let's try doing $(EXE_DIR)/$(NAME) !     "
	@echo "\t————————————————————————————————————————————— "

build: info  $(NAME)

run:
	@echo " —— running $(NAME)"
	@$(EXE_DIR)/$(NAME)

info:
	@echo " Project : $(NAME)"
	@echo " Targets : $(TARGETS)"
	@echo " Library : $(LIBRARY)"

clean: 
	@echo " —— clean up objects"
	@$(RM) $(OBJECTS)

# create execute file 
$(NAME): $(OBJECTS)
	-@mkdir -p ./data/image
	-@mkdir -p $(EXE_DIR)
	@echo " —— linking objects & create $(NAME)"
	@$(COMPILER) $(OPTIONS) -o $(EXE_DIR)/$@ $?

# pattern rule of objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%$(SUFFIX) $(HEADERS)
	-@mkdir -p $(OBJ_DIR)
	$(eval TAR := $(shell python -c "print($(TAR)+1)"))
	@echo "[$(TAR)/$(TARNUM)]\t$(notdir $(basename $@))"
	@$(COMPILER) $(OPTIONS) -o $@ -c $<

