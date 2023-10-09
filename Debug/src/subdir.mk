################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adjlgraph.c \
../src/arraydeque.c \
../src/arraylist.c \
../src/avltree.c \
../src/bfsalg.c \
../src/binarysearch.c \
../src/binarysearchtree.c \
../src/binarytree.c \
../src/circdbllinkedlist.c \
../src/circlinkedlist.c \
../src/dbllinkedlist.c \
../src/dbllinkedlistdeque.c \
../src/dijkstrasp.c \
../src/fibonacciheap.c \
../src/hashset.c \
../src/hashtable.c \
../src/hashtable_lp.c \
../src/indminbinaryheap.c \
../src/indmindaryheap.c \
../src/linkedlist.c \
../src/linkedlistqueue.c \
../src/linkedliststack.c \
../src/main.c \
../src/maxbinaryheap.c \
../src/minbinaryheap.c \
../src/redblacktree.c \
../src/treeset.c 

C_DEPS += \
./src/adjlgraph.d \
./src/arraydeque.d \
./src/arraylist.d \
./src/avltree.d \
./src/bfsalg.d \
./src/binarysearch.d \
./src/binarysearchtree.d \
./src/binarytree.d \
./src/circdbllinkedlist.d \
./src/circlinkedlist.d \
./src/dbllinkedlist.d \
./src/dbllinkedlistdeque.d \
./src/dijkstrasp.d \
./src/fibonacciheap.d \
./src/hashset.d \
./src/hashtable.d \
./src/hashtable_lp.d \
./src/indminbinaryheap.d \
./src/indmindaryheap.d \
./src/linkedlist.d \
./src/linkedlistqueue.d \
./src/linkedliststack.d \
./src/main.d \
./src/maxbinaryheap.d \
./src/minbinaryheap.d \
./src/redblacktree.d \
./src/treeset.d 

OBJS += \
./src/adjlgraph.o \
./src/arraydeque.o \
./src/arraylist.o \
./src/avltree.o \
./src/bfsalg.o \
./src/binarysearch.o \
./src/binarysearchtree.o \
./src/binarytree.o \
./src/circdbllinkedlist.o \
./src/circlinkedlist.o \
./src/dbllinkedlist.o \
./src/dbllinkedlistdeque.o \
./src/dijkstrasp.o \
./src/fibonacciheap.o \
./src/hashset.o \
./src/hashtable.o \
./src/hashtable_lp.o \
./src/indminbinaryheap.o \
./src/indmindaryheap.o \
./src/linkedlist.o \
./src/linkedlistqueue.o \
./src/linkedliststack.o \
./src/main.o \
./src/maxbinaryheap.o \
./src/minbinaryheap.o \
./src/redblacktree.o \
./src/treeset.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/adjlgraph.d ./src/adjlgraph.o ./src/arraydeque.d ./src/arraydeque.o ./src/arraylist.d ./src/arraylist.o ./src/avltree.d ./src/avltree.o ./src/bfsalg.d ./src/bfsalg.o ./src/binarysearch.d ./src/binarysearch.o ./src/binarysearchtree.d ./src/binarysearchtree.o ./src/binarytree.d ./src/binarytree.o ./src/circdbllinkedlist.d ./src/circdbllinkedlist.o ./src/circlinkedlist.d ./src/circlinkedlist.o ./src/dbllinkedlist.d ./src/dbllinkedlist.o ./src/dbllinkedlistdeque.d ./src/dbllinkedlistdeque.o ./src/dijkstrasp.d ./src/dijkstrasp.o ./src/fibonacciheap.d ./src/fibonacciheap.o ./src/hashset.d ./src/hashset.o ./src/hashtable.d ./src/hashtable.o ./src/hashtable_lp.d ./src/hashtable_lp.o ./src/indminbinaryheap.d ./src/indminbinaryheap.o ./src/indmindaryheap.d ./src/indmindaryheap.o ./src/linkedlist.d ./src/linkedlist.o ./src/linkedlistqueue.d ./src/linkedlistqueue.o ./src/linkedliststack.d ./src/linkedliststack.o ./src/main.d ./src/main.o ./src/maxbinaryheap.d ./src/maxbinaryheap.o ./src/minbinaryheap.d ./src/minbinaryheap.o ./src/redblacktree.d ./src/redblacktree.o ./src/treeset.d ./src/treeset.o

.PHONY: clean-src

