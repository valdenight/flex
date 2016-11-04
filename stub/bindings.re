open LayoutSupport;

open LayoutTypes;

/* Force allocating a new node */
let cssNodeNew () => {...theNullNode, children: [||]};

let cssNodeInsertChild node child i => {
  if (Array.length node.children <= i) {
    let fill = Array.make (i - Array.length node.children + 1) theNullNode;
    node.children = Array.append node.children fill
  };
  node.children.(i) = child
};

let cssNodeStyleSetDirection node direction => node.style.direction = direction;

let cssNodeStyleGetDirection node => node.style.direction;

let _ = Callback.register "cssNodeNew" cssNodeNew;

let _ = Callback.register "cssNodeInsertChild" cssNodeInsertChild;

let _ = Callback.register "CSSNodeStyleGetDirection" cssNodeStyleGetDirection;

let _ = Callback.register "CSSNodeStyleSetDirection" cssNodeStyleSetDirection;
