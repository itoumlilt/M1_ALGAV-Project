/**
 * ALGAV Project
 * Errno
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#ifndef __BRDERRNO_H__
#define __BRDERRNO_H__

#define ERR_SIZE 256

#define BRDERRNO_NUL_POINTER 1


/******************************************************************************
 * Errno Str
 *****************************************************************************/
char BRDerrorMsg[ERR_SIZE];

/******************************************************************************
 * Getter / Setter
 *****************************************************************************/
void BRDsetErrorMsg(int errno);
char* BRDgetErrorMsg();
char* BRDsetAndGetErrorMsg(int errno);

#endif
