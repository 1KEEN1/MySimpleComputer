TARGET = ./test/test1
TARGET2 = ./MySimpleComputer/libmySimpleComputer.a
TARGET3 = ./MyTerm/libMyTerm.a
TARGET4 = ./MyBigChar/libMyBigChar.a
TARGET5 = ./MyBigChar/BigCreate
TARGET6 = ./MyBigChar/BigCreateDown
CC = gcc
CFLAGS = -Wall -Wextra -O0 -g
.PHONY : clean run

$(TARGET) : ./test/test1.o $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) BUILDBIGCHAR BUILDBIGCHARDOWN
	$(CC) $(CFLAGS) -o $@ ./test/test1.o -L./MySimpleComputer -lmySimpleComputer -L./MyTerm -lMyTerm -L./MyBigChar -lMyBigChar

$(TARGET5): ./MyBigChar/BigCreate.o $(TARGET3) $(TARGET4) $(TARGET2)
	$(CC) $(CFLAGS) -o $@ $^ -L./MyTerm -lMyTerm -L./MyBigChar -lMyBigChar

$(TARGET6): ./MyBigChar/BigCreateDown.o $(TARGET3) $(TARGET4) $(TARGET2)
	$(CC) $(CFLAGS) -o $@ $^ -L./MyTerm -lMyTerm -L./MyBigChar -lMyBigChar
./MyBigChar/BigCreate.o : ./MyBigChar/BigCreate.c
	$(CC) -c $(CFLAGS) -o $@ $^

./MyBigChar/BigCreateDown.o : ./MyBigChar/BigCreateDown.c
	$(CC) -c $(CFLAGS) -o $@ $^

BUILDBIGCHAR: 
	$(TARGET5) 

BUILDBIGCHARDOWN:
	$(TARGET6)
./test/test1.o : ./test/test1.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(TARGET2) : ./MySimpleComputer/libmySimpleComputer.o
	ar rcs $@ $^

$(TARGET3) : ./MyTerm/libMyTerm.o
	ar rcs $@ $^
	
$(TARGET4) : ./MyBigChar/libMyBigChar.o
	ar rcs $@ $^

./MySimpleComputer/libmySimpleComputer.o : ./MySimpleComputer/MySimpleComputer.c
	$(CC) -c $(CFLAGS) -o $@ $<
./MyTerm/libMyTerm.o : ./MyTerm/MyTerm.c
	$(CC) -c $(CFLAGS) -o $@ $<
./MyBigChar/libMyBigChar.o : ./MyBigChar/MyBigChar.c
	$(CC) -c $(CFLAGS) -o $@ $<
run :
	./test/test1

clean :
	rm ./MySimpleComputer/libmySimpleComputer.a ./MySimpleComputer/libmySimpleComputer.o ./MyTerm/libMyTerm.a ./MyTerm/libMyTerm.o ./MyBigChar/libMyBigChar.a ./MyBigChar/libMyBigChar.o ./test/test1.o ./test/test1