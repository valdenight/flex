#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/callback.h>
#include <assert.h>
#include <stdio.h>
#include "relayout.h"

value *CSSNodeNew(void) {
    CAMLparam0();
    CAMLlocal1(v);
    value *valp;
    static value * closure = NULL;
    if (closure == NULL) closure = caml_named_value("cssNodeNew");
    assert(closure);
    v = caml_callback(*closure, Val_unit);
    valp = (value *) malloc(sizeof *valp);
    *valp = v;
    // Register the value with global heap
    caml_register_global_root(valp);
    CAMLreturnT(value *, valp);
}

void CSSNodeInit(const CSSNodeRef node) {
    // all objects from ocaml are already inited. This is an noop
    return;
}

void CSSNodeFree(const CSSNodeRef node) {
    // deregister the value with global heap
    caml_remove_global_root(node);
    free(node);
}

void CSSNodeInsertChild(const CSSNodeRef node,
                        const CSSNodeRef child,
                        const uint32_t index) {
    // We have no local ocaml allocation here, so no need for CAMLparam/CAMLreturn/etc
    static value * closure = NULL;
    if (closure == NULL) closure = caml_named_value("cssNodeInsertChild");
    assert(closure);
    caml_callback3(*closure, *node, *child, Val_int(index));
    return;
}

void CSSNodeStyleSetDirection(const CSSNodeRef node, const CSSDirection direction) {
    // We have no local ocaml allocation here, so no need for CAMLparam/CAMLreturn/etc
    static value * closure = NULL;
    if (closure == NULL) closure = caml_named_value("CSSNodeStyleSetDirection");
    assert(closure);
    caml_callback2(*closure, *node, Val_int(direction));
    return;
}

CSSDirection CSSNodeStyleGetDirection(const CSSNodeRef node) {
    static value * closure = NULL;
    if (closure == NULL) closure = caml_named_value("CSSNodeStyleGetDirection");
    assert(closure);
    value v = caml_callback(*closure, *node);
    return Int_val(v);
}
