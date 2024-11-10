#opciones de compilacion, muestra todos los warnings (-Wall)
CC = gcc -Wall

#librerias adicionales, en este caso la matemática
#LIBS = -lm

#carpeta de las cabeceras (si estan en la actual, ponemos .)
HEADER_FILES_DIR = .

#opciones de compilacion, indica donde estan los archivos .h
INCLUDES = -I $(HEADER_FILES_DIR)

#nombre del ejecutable o archivo de salida
OUTPUT = ejecutable

#ficheros .h. Si hay varios, se precede cada uno con $(HEADER_FILES_DIR)/
HEADERS = $(HEADER_FILES_DIR)/colors.h $(HEADER_FILES_DIR)/grafo.h $(HEADER_FILES_DIR)/GoTMap.h

#FUENTES: todos los archivos .c necesarios
SRCS = main.c grafo.c GoTMap.c

#ficheros .o: todos los .o con un analogo .c en SRCS
OBJS = $(SRCS:.c=.o)

#REGLA 1: genera el ejecutable, dependencia de los .o
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)

#REGLA 2: genera los .o cuando es necesario, dependencia de los .c y .h
%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

# REGLA 3: borra el ejecutable (prerrequisito: clean)
cleanall: clean
	rm -f $(OUTPUT)

# REGLA 4: borra los ficheros .o y los de backup (terminan en ~
clean:
	rm -f *.o *~