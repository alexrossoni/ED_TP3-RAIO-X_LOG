CC = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = main.o simulacao.o fila.o paciente.o exame.o radiologista.o

all: simulacao_raio_x

simulacao_raio_x: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o simulacao_raio_x

main.o: main.c simulacao.h
	$(CC) $(CFLAGS) -c main.c

simulacao.o: simulacao.c simulacao.h fila.h exame.h radiologista.h
	$(CC) $(CFLAGS) -c simulacao.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

paciente.o: paciente.c paciente.h
	$(CC) $(CFLAGS) -c paciente.c

exame.o: exame.c exame.h
	$(CC) $(CFLAGS) -c exame.c

radiologista.o: radiologista.c radiologista.h
	$(CC) $(CFLAGS) -c radiologista.c

clean:
	rm -f simulacao_raio_x $(OBJS)
