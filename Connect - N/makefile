connectn.out: connectn.o setting_up.o play_game.o win.o
	gcc -g -Wall -Werror -o connectn.out *.c

connectn.o: connectn.c setting_up.h play_game.h win.h
	gcc -g -Wall -Werror -c connectn.c

setting_up.o: setting_up.c
	gcc -g -Wall -Werror -c setting_up.c

play_game.o: play_game.c win.h
	gcc -g -Wall -Werror -c play_game.c

win.o: win.c play_game.h
	gcc -g -Wall -Werror -c win.c

clean:
	rm -fr *.o *.out

run: connectn.out
	./connectn.out