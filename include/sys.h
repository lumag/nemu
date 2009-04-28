/*
 * sys.h
 *
 *  Created on: 24.04.2009
 *      Author: lumag
 */

#ifndef SYS_H_
#define SYS_H_

#undef offsetof
#ifndef offsetof
//#define offsetof(TYPE, MEMBER)	__builtin_offsetof(TYPE, MEMBER)
#define offsetof(TYPE, MEMBER)		((size_t) &((TYPE *)0)->MEMBER)
#endif

#endif /* SYS_H_ */
