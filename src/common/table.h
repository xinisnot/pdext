#ifndef _TABLE_H_
#define _TABLE_H_

/***** start of definition *******************************************************/

#include "ops.h"
#include <stdlib.h>

/***** constant ******************************************************************/

#define TABLE_INDEX 65536
#define TABLE_INDEX_HALF 32768
#define TABLE_INDEX_QUARTER 16384

/***** function prototype ********************************************************/

void callocTableSinusoid(FTYPE **_table, FTYPE _twopi);
void callocTableTriangle(FTYPE **_table);
void freeTable(FTYPE **_table);

FTYPE readTableLinear(FTYPE *_table, FTYPE _phasor);

/***** function  *****************************************************************/

inline void callocTableSinusoid(FTYPE **_table, FTYPE _twopi) {
    if(*_table) return;

    *_table = (FTYPE*)calloc(TABLE_INDEX+1, sizeof(FTYPE));

    FTYPE *pTable = *_table;

    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = sinNormed(scaleU2X(scaleX2U(i, 0, TABLE_INDEX_QUARTER), 0, 0.25), _twopi);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = cosNormed(scaleU2X(scaleX2U(i, 0, TABLE_INDEX_QUARTER), 0, 0.25), _twopi);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = -sinNormed(scaleU2X(scaleX2U(i, 0, TABLE_INDEX_QUARTER), 0, 0.25), _twopi);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = -cosNormed(scaleU2X(scaleX2U(i, 0, TABLE_INDEX_QUARTER), 0, 0.25), _twopi);
    *pTable++ = 0;
}

inline void callocTableTriangle(FTYPE **_table) {
    if(*_table) return;

    *_table = (FTYPE*)calloc(TABLE_INDEX+1, sizeof(FTYPE));

    FTYPE *pTable = *_table;

    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = scaleX2U(i, 0, TABLE_INDEX_QUARTER);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = 1-scaleX2U(i, 0, TABLE_INDEX_QUARTER);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = -scaleX2U(i, 0, TABLE_INDEX_QUARTER);
    for(int i=0; i<TABLE_INDEX_QUARTER; i++)  *pTable++ = -(1-scaleX2U(i, 0, TABLE_INDEX_QUARTER));
    *pTable++ = 0;
}

inline void freeTable(FTYPE **_table) {
    free(*_table);
    *_table = 0;
}

inline FTYPE readTableLinear(FTYPE *_table, FTYPE _phase) {
    FTYPE index  = _phase * (TABLE_INDEX+1);
    int idx0     = roundDown(index);
    int idx1     = (idx0!=TABLE_INDEX) ? idx0+1 : 0;
    FTYPE weight = index - idx0;

    return interpLinear(_table[idx0], _table[idx1], weight);
}

/***** end of definition *********************************************************/

#endif