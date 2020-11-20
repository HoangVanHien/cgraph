#include <stdlib.h>

#include "cgraph_vector.h"

CGRAPH_INTEGER cgraph_ivec_max(const cgraph_ivec_t v) {
  CGRAPH_INTEGER max = v[0];
  for (CGRAPH_INTEGER i = 1; i < cvector_size(v); ++i) {
    if (v[i] > max) {
      max = v[i];
    }
  }
  return max;
}

bool cgraph_ivec_isininterval(const cgraph_ivec_t v, CGRAPH_INTEGER low, CGRAPH_INTEGER high) {
  for (CGRAPH_INTEGER i = 0; i < cvector_size(v); ++i) {
    if (v[i] < low || v[i] > high) {
      return false;
    }
  }
  return true;
}

bool cgraph_ivec_grow(cgraph_ivec_t *v, CGRAPH_INTEGER newcapacity) {
  cgraph_ivec_t _v = *v;
  CGRAPH_INTEGER capacity = (CGRAPH_INTEGER) cvector_capacity(_v);
  if (capacity < newcapacity) {
    cvector_grow(_v, newcapacity);
  }
  *v = _v;
  return _v != NULL;
}

bool cgraph_ivec_setsize(cgraph_ivec_t v, CGRAPH_INTEGER newsize) {
  CGRAPH_INTEGER capacity = (CGRAPH_INTEGER) cvector_capacity(v);
  if (newsize <= capacity) {
    cvector_set_size(v, newsize);
  }
  return true;
}

bool cgraph_ivec_init(cgraph_ivec_t *v, CGRAPH_INTEGER size) {
  cgraph_ivec_grow(v, size);
  cgraph_ivec_setsize(*v, size);
  return true;
}

static cgraph_ivec_t _v;
static cgraph_ivec_t _v2;
int ref_cmp(const void *o1, const void *o2) {
  CGRAPH_INTEGER i1 = *((CGRAPH_INTEGER*)o1),
                i2 = *((CGRAPH_INTEGER*)o2);
  if (_v[i1] < _v[i2]) {
    return -1;
  } else if (_v[i1] > _v[i2]) {
    return 1;
  }
  return _v2[i1] - _v2[i2];
}

int cgraph_ivec_order(const cgraph_ivec_t v, const cgraph_ivec_t v2,
                        cgraph_ivec_t res) {
  _v = v;
  _v2 = v2;
  CGRAPH_INTEGER n = cvector_size(v);
  for (int i = 0; i < n; ++i) {
    res[i] = i;
  }
  qsort(res, n, sizeof(CGRAPH_INTEGER), ref_cmp);
}

int cgraph_ivec_null(cgraph_ivec_t v) {
  for (CGRAPH_INTEGER i = 0; i < cvector_size(v); ++i) {
    v[i] = 0;
  }
}