# $Id: Exp $
# 
# dlchess - A free chess program
#
# François DESCOUENS
#        <fdescoue@etudiant.univ-mlv.fr>
# Gautier LOYAUTE:
#        <gloyaute@etudiant.univ-mlv.fr>
# 
# Année Universitaire 2003 - 2004
# 
# Name of file: Makefile
#
CC        = gcc 
CFLAGS    = -Wall -ansi -Werror -c -I ./
PFLAGS    = -Wall -ansi -I ./ -o 

HEA_FILES = bishop.h board.h castle.h color.h coordinate.h draw.h ia.h king.h knight.h move.h parser.h pawn.h piece.h queen.h referee.h score.h slist.h
OBJ_FILES = bishop.o board.o castle.o color.o coordinate.o draw.o ia.o king.o knight.o move.o parser.o pawn.o piece.o queen.o referee.o score.o slist.o
SRC_FILES = bishop.c board.c castle.c color.c coordinate.c draw.c ia.c king.c knight.c move.c parser.c pawn.c piece.c queen.c referee.c score.c slist.c
EXE_FILE  = dlchess

all:dlchess

dlchess: dlchess.c $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $< $(PFLAGS) $(EXE_FILE)

bishop.o: bishop.c bishop.h piece.o slist.o
	$(CC) $(CFLAGS) $<

board.o: board.c board.h coordinate.o 
	$(CC) $(CFLAGS) $<

castle.o: castle.c castle.h piece.o slist.o
	$(CC) $(CFLAGS) $<

color.o: color.c color.h
	$(CC) $(CFLAGS) $<

coordinate.o: coordinate.c coordinate.h
	$(CC) $(CFLAGS) $<

draw.o: draw.c draw.h
	$(CC) $(CFLAGS) $<

ia.o: ia.c ia.h board.o coordinate.o
	$(CC) $(CFLAGS) $<

king.o: king.c king.h piece.o slist.o
	$(CC) $(CFLAGS) $<

knight.o: knight.c knight.h piece.o slist.o
	$(CC) $(CFLAGS) $<

move.o: move.c move.h
	$(CC) $(CFLAGS) $<

parser.o: parser.c parser.h board.o coordinate.o
	$(CC) $(CFLAGS) $<

pawn.o: pawn.c pawn.h piece.o slist.o
	$(CC) $(CFLAGS) $<

piece.o: piece.c piece.h board.o color.o coordinate.o draw.o move.o score.o
	$(CC) $(CFLAGS) $<

queen.o: queen.c queen.h piece.o slist.o
	$(CC) $(CFLAGS) $<

referee.o: referee.c referee.h board.o parser.o ia.o
	$(CC) $(CFLAGS) $<

score.o: score.c score.h
	$(CC) $(CFLAGS) $<

slist.o: slist.c slist.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o *~

clean-all:
	rm *.o *~ $(EXE_FILE)