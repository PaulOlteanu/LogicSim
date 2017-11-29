# main compiler
CC := gcc

TARGET1 := Main.out

all: $(TARGET1)

$(TARGET1): 
	@echo "Compiling C program"
	#$(CC) $(CFLAGS) $(TARGET1).c -o $(TARGET1) $(LDFLAGS) -l$(LIB)
	$(CC) $(CFLAGS) $(TARGET1).c -o $(TARGET1) $(LDFLAGS) -lonionspi -loniondebug -lugpio

clean:
	@rm -rf $(TARGET1) $(TARGET2)
