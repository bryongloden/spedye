/*
 * Spdylay - SPDY Library
 *
 * Copyright (c) 2012 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "spdylay_pq_test.h"

#include <CUnit/CUnit.h>

#include "spdylay_pq.h"

static int pq_compar(const void *lhs, const void *rhs)
{
  return strcmp(lhs, rhs);
}

void test_spdylay_pq()
{
  spdylay_pq pq;
  spdylay_pq_init(&pq, pq_compar);
  CU_ASSERT(spdylay_pq_empty(&pq));
  CU_ASSERT(0 == spdylay_pq_size(&pq));
  CU_ASSERT(0 == spdylay_pq_push(&pq, "foo"));
  CU_ASSERT(0 == spdylay_pq_empty(&pq));
  CU_ASSERT(1 == spdylay_pq_size(&pq));
  CU_ASSERT(strcmp("foo", spdylay_pq_top(&pq)) == 0);
  CU_ASSERT(0 == spdylay_pq_push(&pq, "bar"));
  CU_ASSERT(strcmp("bar", spdylay_pq_top(&pq)) == 0);
  CU_ASSERT(0 == spdylay_pq_push(&pq, "baz"));
  CU_ASSERT(strcmp("bar", spdylay_pq_top(&pq)) == 0);
  CU_ASSERT(0 == spdylay_pq_push(&pq, "C"));
  CU_ASSERT(4 == spdylay_pq_size(&pq));
  CU_ASSERT(strcmp("C", spdylay_pq_top(&pq)) == 0);  
  spdylay_pq_pop(&pq);
  CU_ASSERT(3 == spdylay_pq_size(&pq));
  CU_ASSERT(strcmp("bar", spdylay_pq_top(&pq)) == 0);
  spdylay_pq_pop(&pq);
  CU_ASSERT(strcmp("baz", spdylay_pq_top(&pq)) == 0);
  spdylay_pq_pop(&pq);
  CU_ASSERT(strcmp("foo", spdylay_pq_top(&pq)) == 0);
  spdylay_pq_pop(&pq);
  CU_ASSERT(spdylay_pq_empty(&pq));
  CU_ASSERT(0 == spdylay_pq_size(&pq));
  CU_ASSERT(0 == spdylay_pq_top(&pq));
  spdylay_pq_free(&pq);
}

