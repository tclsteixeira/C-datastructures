################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/arraylist.c \
../src/avltree.c \
../src/binarysearch.c \
../src/binarysearchtree.c \
../src/binarytree.c \
../src/circdbllinkedlist.c \
../src/circlinkedlist.c \
../src/dbllinkedlist.c \
../src/hashtable.c \
../src/linkedlist.c \
../src/linkedlistqueue.c \
../src/linkedliststack.c \
../src/main.c \
../src/redblacktree.c 

C_DEPS += \
./src/arraylist.d \
./src/avltree.d \
./src/binarysearch.d \
./src/binarysearchtree.d \
./src/binarytree.d \
./src/circdbllinkedlist.d \
./src/circlinkedlist.d \
./src/dbllinkedlist.d \
./src/hashtable.d \
./src/linkedlist.d \
./src/linkedlistqueue.d \
./src/linkedliststack.d \
./src/main.d \
./src/redblacktree.d 

OBJS += \
./src/arraylist.o \
./src/avltree.o \
./src/binarysearch.o \
./src/binarysearchtree.o \
./src/binarytree.o \
./src/circdbllinkedlist.o \
./src/circlinkedlist.o \
./src/dbllinkedlist.o \
./src/hashtable.o \
./src/linkedlist.o \
./src/linkedlistqueue.o \
./src/linkedliststack.o \
./src/main.o \
./src/redblacktree.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/arraylist.d ./src/arraylist.o ./src/avltree.d ./src/avltree.o ./src/binarysearch.d ./src/binarysearch.o ./src/binarysearchtree.d ./src/binarysearchtree.o ./src/binarytree.d ./src/binarytree.o ./src/circdbllinkedlist.d ./src/circdbllinkedlist.o ./src/circlinkedlist.d ./src/circlinkedlist.o ./src/dbllinkedlist.d ./src/dbllinkedlist.o ./src/hashtable.d ./src/hashtable.o ./src/linkedlist.d ./src/linkedlist.o ./src/linkedlistqueue.d ./src/linkedlistqueue.o ./src/linkedliststack.d ./src/linkedliststack.o ./src/main.d ./src/main.o ./src/redblacktree.d ./src/redblacktree.o

.PHONY: clean-src

