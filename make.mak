

exec : main.o fonction_liste.o fonction_ABR.o fonction_AVL.o affichage_ABR_AVL.o
		gcc $^ -o bin/$@

main.o : src/main.c src/Headers.h
		gcc -c $< -o $@

fonction_liste.o : src/fonction_liste.c src/Headers.h
		gcc -c $< -o $@

fonction_ABR.o : src/fonction_ABR.c src/Headers.h
		gcc -c $< -o $@

fonction_AVL.o : src/fonction_AVL.c src/Headers.h
		gcc -c $< -o $@

affichage_ABR_AVL.o : src/affichage_ABR_AVL.c src/Headers.h
		gcc -c $< -o $@


clear :
	rm -f *.o
	rm -f bin/exec