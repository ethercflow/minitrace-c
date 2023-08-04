/*
 * Copyright 2023 Wenbo Zhang. Licensed under Apache-2.0.
 * Generated by gen_header.sh. Do not edit directly.
 */

#ifndef __MINITRACE_H
#define __MINITRACE_H

/* Generated with cbindgen:0.24.5 */

#include <stddef.h>

typedef struct mtr_coll_cfg mtr_coll_cfg;

typedef struct mtr_cons_rptr mtr_cons_rptr;

typedef struct mtr_guard mtr_guard;

typedef struct mtr_loc_coll mtr_loc_coll;

typedef struct mtr_loc_span mtr_loc_span;

typedef struct mtr_loc_spans mtr_loc_spans;

typedef struct mtr_otel_rptr mtr_otel_rptr;

typedef struct mtr_span mtr_span;

typedef struct mtr_span_ctx mtr_span_ctx;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

const char *mtr_c_ver(void);

/*
 Create a new `SpanContext` with a random trace id.
 */
mtr_span_ctx *mtr_create_rand_span_ctx(void);

/*
 Creates a `SpanContext` from the given [`Span`]. If the `Span` is a noop span,
 this function will return `None`.
 */
mtr_span_ctx *mtr_create_span_ctx(const mtr_span *span);

/*
 Creates a `SpanContext` from the current local parent span. If there is no
 local parent span, this function will return `None`.
 */
mtr_span_ctx *mtr_create_span_ctx_loc(void);

/*
 Free an unused `mtr_span_ctx *`.
 */
void mtr_free_span_ctx(mtr_span_ctx *c);

/*
 Default configuration of the behavior of the global collector.
 */
mtr_coll_cfg *mtr_create_glob_coll_def_cfg(void);

/*
 Free an unused `mtr_coll_cfg *`.
 */
void mtr_free_glob_coll_def_cfg(mtr_coll_cfg *c);

mtr_cons_rptr *mtr_create_cons_rptr(void);

void mtr_free_cons_rptr(mtr_cons_rptr *r);

void mtr_set_cons_rptr(mtr_cons_rptr *rptr, mtr_coll_cfg *cfg);

void mtr_set_otel_rptr(mtr_otel_rptr *rptr, mtr_coll_cfg *cfg);

void mtr_flush(void);

mtr_otel_rptr *mtr_create_otel_rptr(void);

void mtr_free_otel_rptr(mtr_otel_rptr *r);

mtr_loc_coll *mtr_start_loc_coll(void);

mtr_loc_spans *mtr_collect_loc_spans(mtr_loc_coll *lc);

/*
 Create a new child span associated with the current local span in the current thread, and then
 it will become the new local parent.

 If no local span is active, this function is no-op.
 */
mtr_loc_span *mtr_create_loc_span_enter(const char *name);

/*
 Add a single property to the `LocalSpan` and return the modified `LocalSpan`.

 A property is an arbitrary key-value pair associated with a span.
 */
int mtr_add_prop_to_loc_span(mtr_loc_span *ls, const char *k, const char *v);

/*
 Add multiple properties to the `LocalSpan` and return the modified `LocalSpan`.
 */
int mtr_add_props_to_loc_span(mtr_loc_span *ls, const char *const *karr, const char *const *varr, size_t len);

/*
 Free an unused `mtr_local_span *`.
 */
void mtr_free_loc_span(mtr_loc_span *ls);

/*
 Create a new trace and return its root span.

 Once dropped, the root span automatically submits all associated child spans to the reporter.
 */
mtr_span *mtr_create_root_span(const char *name, mtr_span_ctx *parent);

/*
 Create a new child span associated with the specified parent span.
 */
mtr_span *mtr_create_child_span_enter(const char *name, mtr_span *parent);

/*
 Create a new child span associated with the current local span in the current thread.

 If no local span is active, this function returns a no-op span.
 */
mtr_span *mtr_create_child_span_enter_loc(const char *name);

/*
 Sets the current `Span` as the local parent for the current thread.

 This method is used to establish a `Span` as the local parent within the current scope.

 A local parent is necessary for creating a [`LocalSpan`] using [`LocalSpan::enter_with_local_parent()`].
 If no local parent is set, `enter_with_local_parent()` will not perform any action.
 */
mtr_guard *mtr_set_loc_parent_to_span(mtr_span *s);

/*
 Free an unused `mtr_guard *`.
 */
void mtr_free_guard(mtr_guard *g);

/*
 Add a single property to the `Span` and return the modified `Span`.

 A property is an arbitrary key-value pair associated with a span.
 */
int mtr_add_prop_to_span(mtr_span *s, const char *k, const char *v);

/*
 Add multiple properties to the `Span` and return the modified `Span`.
 */
int mtr_add_props_to_span(mtr_span *s, const char *const *karr, const char *const *varr, size_t len);

/*
 Attach a collection of [`LocalSpan`] instances as child spans to the current span.

 This method allows you to associate previously collected `LocalSpan` instances with the current span.
 This is particularly useful when the `LocalSpan` instances were initiated before their parent span,
 and were collected manually using a [`LocalCollector`].
 */
void mtr_push_child_spans_to_cur(mtr_span *s, mtr_loc_spans *local_spans);

/*
 Free an unused `mtr_span *`.
 */
void mtr_free_span(mtr_span *s);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* __MINITRACE_H */