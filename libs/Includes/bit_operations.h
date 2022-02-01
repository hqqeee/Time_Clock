/*
 *	This file contains some macros for working with registers.
 *		1. SET_BIT(REG, BIT) sets BIT to REG, logical OR.
 *			Exmaple: REG = 01010
 *					 BIT = 00100
 *					 REG = 01110
 *		2. СLEAR_BIT(REG, BIT) sets BIT in REG to 0, logical AND NOT.
 *			Examble: REG = 01010
 *					 BIT = 01000
 *					~BIT = 10111
 *					 REG = 00010
 *		3. READ_BIT(REG, BIT) equals to BIT in REG, logical AND.
 *			Example: REG = 01010
 *					 BIT = 01000
 *					 RES = 01000
 *		4. CLEAR_REG(REG) sets all bits in REG to 0, logical AND.
 *			Example: REG = 01010
 *					 REG = 00000
 *		5. WRITE_REG(REG, VAL) sets all bits in REG to VAL.
 *			Example: REG = 01010
 *					 VAL = 10101
 *					 REG = 10101
 *		6. READ_REG(REG) equals to REG.
 *			Example: REG = 01010
 *					 RES = 01010
 *		7. MODIFY_REG sets (first) bits in CMASK to 0, (then) bits in SMASK to 1.
 *			Examble: REG = 01010
 *				   CMASK = 11000
 *				   SMASK = 01111
 *				   	 REG = 01111
 *		8. REV_MODIFY_REG(Reversed modify reg) sets (first) bits in SMASK to 1, (then) bits in CMASK to 0.
 *			Example: REG = 01010
 *			       CMASK = 11000
 *			       SMASK = 01111
 *			       	 REG = 00111
 *
 */

#ifndef __BIT_OPERATIONS_H
#define __BIT_OPERATIONS_H

#define SET_BIT(REG,BIT) 				 ((REG) |= (BIT))
#define CLEAR_BIT(REG,BIT) 				 ((REG) &= ~(BIT))
#define READ_BIT(REG,BIT)		 		 ((REG) & (BIT))
#define CLEAR_REG(REG)					 ((REG) &= 0x0)
#define WRITE_REG(REG,VAL)  			 ((REG) = (VAL))
#define MODIFY_REG(REG,CMASK,SMASK) 	 ((REG) = ((CLEAR_REG((REG),(CMASK))) | (MASK)))
#define REV_MODIFY_REG(REG,CMASK,SMASK)  ((REG) = ((SET_BIT((REG),(SMASK))) & (~(MASK))) 

#endif /*__BIT_OPERATIONS_H */
