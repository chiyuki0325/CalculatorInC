objects = main.o lexer.o parser.o evaluator.o
CFLAGS = -Wall -O2

calculator : $(objects)
	$(CC) $(CFLAGS) -o calculator $(objects) -lm
	rm $(objects)

main.o : main.c lexer.h parser.h evaluator.h types.h
lexer.o : lexer.c lexer.h types.h
parser.o : parser.c parser.h types.h
evaluator.o : evaluator.c evaluator.h types.h

.PHONY : clean

clean :
	-rm calculator $(objects)