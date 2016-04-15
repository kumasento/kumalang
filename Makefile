
# Directories
NAME=kuma
SRCDIR=src/
OBJDIR=obj/

# Tools and flags
CFLAGS=
# LEX
LEX=lex
LEX_FILE=$(SRCDIR)$(NAME)_lex.l
LEX_SOURCE=lex.yy.c
# YACC
YACC_FLAGS=-dvyt
YACC=yacc $(YACC_FLAGS)
YACC_FILE=$(SRCDIR)$(NAME)_yacc.y
YACC_HEADER=y.tab.h
YACC_SOURCE=$(NAME)_yacc.c
YACC_OUTPUT=y.output

# Program sources definition
OBJ=kuma_yacc.o kuma_lex.o kuma.o kuma_ast.o kuma_interpreter.o
EXEC=kuma
OBJS=$(addprefix $(OBJDIR), $(OBJ))
DEPS=$(wildcard $(SRCDIR)*.h) Makefile 
# include lex and yacc
DEPS+=$(SRCDIR)$(LEX_SOURCE) $(SRCDIR)$(YACC_SOURCE)

all: obj $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile lex and move
$(SRCDIR)$(LEX_SOURCE): $(LEX_FILE)

# Compile yacc and move
$(SRCDIR)$(YACC_SOURCE): $(YACC_FILE)

obj:
	mkdir -p $(OBJDIR)

.PHONY: clean

clean:
	# Remove YACC's intermediate files
	rm -f $(YACC_HEADER) $(SRCDIR)$(YACC_SOURCE) $(YACC_OUTPUT)
	# Remove lex intermediate files
	rm -f $(SRCDIR)$(LEX_SOURCE)	
	# Remove all objects
	rm -rf $(OBJDIR)
