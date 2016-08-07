/* **************************
// This answers the question:
//   What would a function-based interface to react look like?
// **************************
*/
type reactElement;
type reactComponent;
type reactComponentConfig;
type domNode;
type domConfig;
type reactThis;

external domProps :
  onClick::(unit => unit)? =>
  style::'a? =>
  key::string? =>
  ref::(domNode => unit)? =>
  unit =>
  domConfig = "" [@@bs.obj];

external makeDomConfig : unit => domConfig = "" [@@bs.obj];
external makeMoreDomConfig : onClick::(unit => unit)? => domConfig = "" [@@bs.obj];

type reactNode =
  | Text of string
  | Int of int
  | Float of float
  | ReactElement of reactElement
  | Children of (list reactNode)
  | Empty;

external div : unit => reactElement = "ReactDOM.div" [@@bs.val];
external createClass : reactComponentConfig => reactComponent = "createClass" [@@bs.val] [@@bs.module "react"];
external createElement : 'thing => 'props => 'contents => reactElement = "React.createElement" [@@bs.val];
external createEmptyElement : 'thing => 'props => reactElement = "React.createElement" [@@bs.val];
external render : reactElement => domNode => unit = "render" [@@bs.val] [@@bs.module "react-dom"];
external getElementById : string => domNode = "document.getElementById" [@@bs.val];
external setState : reactThis => 'obj => unit = "setState" [@@bs.send];

type jsState;

external makeState : count::int => jsState = "" [@@bs.obj];

external class_config : (
  getInitialState::(unit => 'state)? =>
  componentDidMount::(unit => unit)? =>
  componentWillMount::(unit => unit)? =>
  render::(unit => reactElement) =>
  unit =>
  reactComponentConfig
) = "" [@@bs.obj];

let oldCounter = createClass(class_config
  getInitialState::(fun () => {
    makeState 2
  })
  render::(fun () => {
    print_endline "rendering";
    let count : int = [%bs.raw{|this.state.count|}];
    let this = [%bs.raw{|this|}];
    createElement "button" (makeMoreDomConfig onClick::(fun () => {
      (setState this (makeState (count + 1)))
    })) (Printf.sprintf "Hello %d" count)
  })
  ()
);

let noop = fun _ => ();
external makeJsState : ml::'a => jsState = "" [@@bs.obj];
external makeJsProps : ml::'a => jsState = "" [@@bs.obj];
external setJsState : reactThis => jsState => unit = "setState" [@@bs.send];

let setMlState = fun this state => setJsState this (makeJsState state);

/*
val createStatefulClass : (
  getInitialState::('props => 'state) =>
  componentDidMount::('props => 'state => unit)? =>
  componentWillMount::('props => 'state => unit)? =>
  ('props => 'state => ('state => unit) => reactElement) =>
  ('props => reactElement)
);
*/

let createStatefulComponent = fun
  getInitialState::getInitialState
  componentDidMount::componentDidMount=noop
  componentWillMount::componentWillMount=noop
  render => {
    let component = createClass(class_config
      getInitialState::(fun () => {
        let props = [%bs.raw{|this.props.ml|}];
        makeJsState (getInitialState props)
      })
      render::(fun () => {
        let props = [%bs.raw{|this.props.ml|}];
        let state = [%bs.raw{|this.state.ml|}];
        let this = [%bs.raw{|this|}];
        (render props state (setMlState this))
      })
      ()
    );
    fun props => (createEmptyElement component (makeJsProps props))
  };

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

type myProps = {initialCount: int};
type myState = {count: int};

let counter = (createStatefulComponent
  getInitialState::(fun props => {
    {count: props.initialCount}
  })
  (fun props state setState => {
    (button
      (domProps onClick::(fun () => {
        setState {count: state.count + 1}
      }) ())
      (Children [(Text "Hello "), (Int state.count)]))
  })
);

let renderExample = fun () => {
  print_endline "hello reason + reactjs + bucklescript!";
  render (counter {initialCount: 10}) (getElementById "container");
};
