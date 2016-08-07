/*
// This answers the question:
//   What would a module-based interface to react look like?
*/


/* React interface b/c I'm too lazy to do multiple files */
type reactElement;
type reactNode =
  | Text of string
  | Int of int
  | Float of float
  | ReactElement of reactElement
  | Children of (list reactNode)
  | Empty;
type domConfig;
type domNode;

external domProps :
  onClick::(unit => unit)? =>
  style::'a? =>
  key::string? =>
  ref::(domNode => unit)? =>
  unit =>
  domConfig = "" [@@bs.obj];

/* Probably private types? */
type reactComponent;
type reactComponentConfig;
type reactThis;

external makeDomConfig : unit => domConfig = "" [@@bs.obj];
external makeMoreDomConfig : onClick::(unit => unit)? => domConfig = "" [@@bs.obj];

external createClass : reactComponentConfig => reactComponent = "createClass" [@@bs.val] [@@bs.module "react"];
external createElement : 'thing => 'props => 'contents => reactElement = "React.createElement" [@@bs.val];
external createEmptyElement : 'thing => 'props => reactElement = "React.createElement" [@@bs.val];
external render : reactElement => domNode => unit = "render" [@@bs.val] [@@bs.module "react-dom"];
external getElementById : string => domNode = "document.getElementById" [@@bs.val];
external setState : reactThis => 'obj => unit = "setState" [@@bs.send];

external class_config : (
  getInitialState::(unit => 'state)? =>
  componentDidMount::(unit => unit)? =>
  componentWillMount::(unit => unit)? =>
  render::(unit => reactElement) =>
  unit =>
  reactComponentConfig
) = "" [@@bs.obj];

type javascriptUnsafe;
external jj : 'a => javascriptUnsafe = "window.identity" [@@bs.val];
external set_props_children : domConfig => 'children => unit = "children" [@@bs.set];

let rec js_children = fun children => {
  switch children {
    | Empty => jj [%bs.raw{|null|}];
    | Children children => jj (Array.map js_children (Array.of_list children));
    | ReactElement el => jj el
    | Float value => jj value
    | Text value => jj value
    | Int value => jj value
  }
};

let createDOMElement = fun tag config children => {
  set_props_children config (js_children children);
  createEmptyElement tag config;
};

let button = createDOMElement "button";

let noop = fun _ => ();

type jsState;
type jsProps;
external makeJsState : ml::'a => jsState = "" [@@bs.obj];
external makeJsProps : ml::'a => jsProps = "" [@@bs.obj];
external setJsState : reactThis => jsState => unit = "setState" [@@bs.send];

let setMlState = fun this state => setJsState this (makeJsState state);

module type ReactComponent = {
  type props;
  type state;
  let getInitialState: props => state;
  let render: props => state => (state => unit) => reactElement;
};


module type FullReactComponent = (Component: ReactComponent) => {
  let create: Component.props => reactElement;
};

let module CreateClass = fun (Component: ReactComponent) => {
  let component = createClass(class_config
    getInitialState::(fun () => {
      let props = [%bs.raw{|this.props.ml|}];
      makeJsState (Component.getInitialState props)
    })
    render::(fun () => {
      let props = [%bs.raw{|this.props.ml|}];
      let state = [%bs.raw{|this.state.ml|}];
      let this = [%bs.raw{|this|}];
      (Component.render props state (setMlState this))
    })
    ()
  );
  let create = fun props => {
    (createEmptyElement component (makeJsProps props))
  };
};

let module Counter = CreateClass {
  type props = {initialCount: int};
  type state = {count: int};
  let getInitialState = (fun props => {
    {count: props.initialCount}
  });
  let render = fun props state setState => {
    (button
      (domProps onClick::(fun () => {
        setState {count: state.count + 1}
      }) ())
      (Children [(Text "Moduly "), (Int state.count)]))
  };
};
type hackyProps = {initialCount: int}; /* need to expose for some reason? */
let renderExample = fun () => {
  print_endline "hello reason + reactjs + bucklescript!";
  render (Counter.create {initialCount: 10}) (getElementById "container");
};
