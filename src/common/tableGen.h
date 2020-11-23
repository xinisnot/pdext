#ifndef _TABLEGEN_H_
#define _TABLEGEN_H_

/***** start of definition *******************************************************/

#include "operator.h"
#include <stdlib.h>

/***** constant ******************************************************************/

#define TABLE_INDEX 65536
#define TABLE_INDEX_HALF 32768
#define TABLE_INDEX_QUARTER 16384

/***** function prototype ********************************************************/

void generateTableSinusoid(FTYPE *_table);
void generateTableTriangle(FTYPE *_table);

/***** function  *****************************************************************/

inline void generateTableSinusoid(FTYPE *_table) {
    FTYPE *pTable = _table;

    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = sine(scaleU2X(scaleX2U(i, 0, TABLE_INDEX_QUARTER), 0, 0.25));
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = cosine(scaleU2X(scaleX2U(i, 0, TABLE_INDEX_QUARTER), 0, 0.25));
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = -sine(scaleU2X(scaleX2U(i, 0, TABLE_INDEX_QUARTER), 0, 0.25));
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = -cosine(scaleU2X(scaleX2U(i, 0, TABLE_INDEX_QUARTER), 0, 0.25));
    *pTable++ = 0;
}

inline void generateTableTriangle(FTYPE *_table) {
    FTYPE *pTable = _table;

    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = scaleX2U(i, 0, TABLE_INDEX_QUARTER);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = 1-scaleX2U(i, 0, TABLE_INDEX_QUARTER);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = -scaleX2U(i, 0, TABLE_INDEX_QUARTER);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = -(1-scaleX2U(i, 0, TABLE_INDEX_QUARTER));
    *pTable++ = 0;
}

/***** end of definition *********************************************************/

#endif