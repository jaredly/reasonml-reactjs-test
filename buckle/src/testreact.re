type reactElement;

type reactComponent;
type reactComponentConfig;
type domNode;
type domConfig;
type reactThis;
type jsState;

external makeDomConfig : unit => domConfig = "" [@@bs.obj];
external makeMoreDomConfig : onClick::(unit => unit)? => domConfig = "" [@@bs.obj];

external div : unit => reactElement = "ReactDOM.div" [@@bs.val];
external createClass : reactComponentConfig => reactComponent = "createClass" [@@bs.val] [@@bs.module "react"];
external createElement : 'component => 'props => 'contents => reactElement = "React.createElement" [@@bs.val];
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

/*
React.createClass({
  getInitialState() {
    return {count: 2}
  },
  render() {
    return (
      <button
        onClick={() => this.setState({count: 10})}
      >
        Hello more button
      </button>
    )
  }
})
*/

external makeState : count::int => jsState = "" [@@bs.obj];

let counter = createClass(class_config
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

let renderExample = fun () => {
  print_endline "hello reason + reactjs + bucklescript!";
  render (createElement counter () "hello") (getElementById "container");
};
