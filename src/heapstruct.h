/*
 * heapstruct.h
 *
 *  Created on: 09/07/2023
 *      Author: Tiago C. Teixeira
 * Description: Declares the heap structure.
 */

#ifndef HEAPSTRUCT_H_
	#define HEAPSTRUCT_H_

	// callback function to calculate size of data in bytes
//	typedef size_t (*heap_calcdatasize)(const void* data);
	typedef int (*heap_cmp)(const void* data, const void* key);
	typedef void (*heap_freedata)(void* data);
//	typedef void* (*heap_minlimitkey)();	// get minimum possible limit value (ex: INT_MIN)
//	typedef void* (*heap_maxlimitkey)();	// get maximum possible limit value (ex: INT_MAX)
	typedef void (*heap_printdata)(void* data);

	// Declare a heap structure
	struct heap {
//		heap_calcdatasize calcdatasize;
		heap_cmp compare;
//		heap_minlimitkey minlimit;
//		heap_maxlimitkey maxlimit;
		heap_freedata freedata;
		heap_printdata printdata;
		int size;
		int capacity;
		void* MAXVALUE;
		void* MINVALUE;
		void** arr;
	};

#endif /* HEAPSTRUCT_H_ */
