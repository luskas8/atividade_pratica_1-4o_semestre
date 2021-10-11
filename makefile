MAIN_FILES=main.o avl.o utils.o
atividade_pratica: $(MAIN_FILES)
	gcc -o atividade_pratica $(MAIN_FILES)

main.o: main.c avl.h utils.h
	gcc -c main.c

avl.o: avl.c avl.h
	gcc -c avl.c

utls.o: utils.c utils.h avl.h
	gcc -c utils.c