/* **************************
// This answers the question:
//   What would a function-based interface to react look like?
// **************************
*/

type javascriptUnsafe;
external jj : 'a => javascriptUnsafe = "%identity";


let oelse = fun opt default =>
  switch (opt) {
    | Some x => x
    | None => default
  };

let module ReactStar = {
  type reactElement;

  type reactNode =
    | Text of string
    | Int of int
    | Float of float
    | ReactElement of reactElement
    | Children of (list reactNode)
    | Empty;

  type hw =
    | Auto
    | Int of int;

  type css = {
    paddingLeft: int,
    paddingRight: int,
    paddingTop: int,
    paddingBottom: int,

    marginTop: int,
    marginLeft: int,
    marginRight: int,
    marginBottom: int,

    height: hw,
    width: hw,

    backgroundColor: string,
    borderRadius: int,
    borderColor: string,
    borderStyle: string,
    borderWidth: int,

    flexDirection: string,
    justifyContent: string,
    alignItems: string,
    cursor: string,
  };

  type tblr = {top: int, left: int, bottom: int, right: int};
  let noBox = {top: 0, left: 0, bottom: 0, right: 0};

  let box = fun all::all=? top::top=? bottom::bottom=? left::left=? right::right=? vertical::vertical=? horizontal::horizontal=? unit => {
    {
      top: oelse top (oelse vertical (oelse all 0)),
      bottom: oelse bottom (oelse vertical (oelse all 0)),
      left: oelse left (oelse horizontal (oelse all 0)),
      right: oelse right (oelse horizontal (oelse all 0)),
    }
  };

  let cssStyle = fun
    padding::padding=noBox
    margin::margin=noBox

    backgroundColor::backgroundColor="none"
    borderRadius::borderRadius=0
    borderColor::borderColor="none"
    borderStyle::borderStyle="solid"
    borderWidth::borderWidth=0

    height::height=Auto
    width::width=Auto

    flexDirection::flexDirection="column"
    justifyContent::justifyContent="none"
    alignItems::alignItems="none"
    cursor::cursor="normal"
    unit

  =>
  {
    {
      paddingTop: padding.top,
      paddingLeft: padding.left,
      paddingRight: padding.right,
      paddingBottom: padding.bottom,

      marginTop: margin.top,
      marginLeft: margin.left,
      marginRight: margin.right,
      marginBottom: margin.bottom,

      height,
      width,

      backgroundColor,
      borderRadius,
      borderColor,
      borderStyle,
      borderWidth,

      flexDirection,
      justifyContent,
      alignItems,
      cursor,
    }
  };

  type jsStyleObj;

  external jsStyle :
    paddingTop::int =>
    paddingLeft::int =>
    paddingRight::int =>
    paddingBottom::int =>

    marginTop::int =>
    marginLeft::int =>
    marginRight::int =>
    marginBottom::int =>

    height::javascriptUnsafe =>
    width::javascriptUnsafe =>

    backgroundColor::string =>
    borderColor::string =>
    borderStyle::string =>
    borderRadius::int =>
    borderWidth::int =>

    flexDirection::string =>
    justifyContent::string =>
    alignItems::string =>
    cursor::string =>
    jsStyleObj = "" [@@bs.obj];

  let hwToJs = fun hw => switch (hw) {
    | Auto => jj "auto"
    | Int x => jj x
  };

  let makeStyle = fun {
      paddingTop,
      paddingLeft,
      paddingRight,
      paddingBottom,

      marginTop,
      marginLeft,
      marginRight,
      marginBottom,

      backgroundColor,
      borderRadius,
      borderColor,
      borderStyle,
      borderWidth,

      height,
      width,

      flexDirection,
      justifyContent,
      alignItems,
      cursor,
    } => {
    jsStyle
      paddingTop::paddingTop
      paddingLeft::paddingLeft
      paddingRight::paddingRight
      paddingBottom::paddingBottom

      marginTop::marginTop
      marginLeft::marginLeft
      marginRight::marginRight
      marginBottom::marginBottom

      height::(hwToJs height)
      width::(hwToJs width)

      backgroundColor::backgroundColor
      borderRadius::borderRadius
      borderColor::borderColor
      borderStyle::borderStyle
      borderWidth::borderWidth

      flexDirection::flexDirection
      justifyContent::justifyContent
      alignItems::alignItems
      cursor::cursor
    };

};

let module React = {
  open ReactStar;

  type reactComponent;
  type reactComponentConfig;
  type domConfig;
  type reactThis;
  type domNode;
  external getElementById : string => domNode = "document.getElementById" [@@bs.val];

  external domProps :
    _type::string? =>
    value::string? =>
    checked::bool? =>
    href::string? =>
    className::string? =>
    onChange::(unit => unit)? =>
    onClick::(unit => unit)? =>
    ref::(domNode => unit)? =>
    style::jsStyleObj? =>
    key::string? =>
    unit =>
    domConfig = "" [@@bs.obj];

  external convertProps : domConfig => domConfig = "window.convertProps"[@@bs.val];

  external makeDomConfig : unit => domConfig = "" [@@bs.obj];
  external makeMoreDomConfig : onClick::(unit => unit)? => domConfig = "" [@@bs.obj];

  external div : unit => reactElement = "ReactDOM.div" [@@bs.val];
  external createClass : reactComponentConfig => reactComponent = "createClass" [@@bs.val] [@@bs.module "react"];
  external createElement : 'thing => 'props => 'contents => reactElement = "React.createElement" [@@bs.val];
  external createEmptyElement : 'thing => 'props => reactElement = "React.createElement" [@@bs.val];
  external render : reactElement => domNode => unit = "render" [@@bs.val] [@@bs.module "react-dom"];
  external setState : reactThis => 'obj => unit = "setState" [@@bs.send];

  type jsState;

  external makeState : count::int => jsState = "" [@@bs.obj];

  external class_config : (
    getInitialState::(unit => 'state)? =>
    componentDidMount::(unit => unit)? =>
    componentWillMount::(unit => unit)? =>
    shouldComponentUpdate::('props => 'state => bool)? =>
    render::(unit => reactElement) =>
    unit =>
    reactComponentConfig
  ) = "" [@@bs.obj];

  let noop = fun _ => ();
  external makeJsState : ml::'a => jsState = "" [@@bs.obj];
  external makeJsProps : key::string? => ml::'a => unit => jsState = "" [@@bs.obj];
  external setJsState : reactThis => jsState => unit = "setState" [@@bs.send];
  external fixKey : jsState => jsState = "window.fixKey"[@@bs.val];

  let setMlState = fun this state => setJsState this (makeJsState state);

  external getMl : 'a => 'b = "ml" [@@bs.get];

  type createComponent 'props = (
    componentWillMount::('props => unit)? =>
    componentDidMount::('props => unit)? =>
    shouldComponentUpdate::('props => 'props => bool)? =>
    ('props => reactElement) =>
    (key::string? => 'props => reactElement)
  );

  let createComponent: createComponent 'props = fun
    componentWillMount::componentWillMount=noop
    componentDidMount::componentDidMount=noop
    shouldComponentUpdate::shouldComponentUpdate=(fun _ _ => true)
    render
    => {
      let component = createClass(class_config
        componentWillMount::(fun () => {
          let props = [%bs.raw{|this.props.ml|}];
          (componentWillMount props)
        })
        componentDidMount::(fun () => {
          let props = [%bs.raw{|this.props.ml|}];
          (componentDidMount props)
        })
        shouldComponentUpdate::(fun nextProps _ => {
          let mlProps = getMl nextProps;
          let props = [%bs.raw{|this.props.ml|}];
          (shouldComponentUpdate mlProps props)
        } [@bs])
        render::(fun () => {
          let props = [%bs.raw{|this.props.ml|}];
          (render props)
        })
        ()
      );
      fun key::key=? props => (createEmptyElement component (
        switch key {
          | Some x => (makeJsProps key::x ml::props ())
          | None => (makeJsProps ml::props ())
        }
      ))
    };

  type createStatefulComponent 'props 'state = (
    getInitialState::('props => 'state) =>
    componentDidMount::('props => unit)? =>
    componentWillMount::('props => unit)? =>
    shouldComponentUpdate::('props => 'state => 'props => 'state => bool)? =>
    ('props => 'state => ('state => unit) => reactElement) =>
    (key::string? => 'props => reactElement)
  );

  let createStatefulComponent: createStatefulComponent 'props 'state = fun
    getInitialState::getInitialState
    componentDidMount::componentDidMount=noop
    componentWillMount::componentWillMount=noop
    shouldComponentUpdate::shouldComponentUpdate=(fun _ _ _ _ => true)
    render => {
      let component = createClass(class_config
        getInitialState::(fun () => {
          let props = [%bs.raw{|this.props.ml|}];
          makeJsState (getInitialState props)
        })
        componentWillMount::(fun () => {
          let props = [%bs.raw{|this.props.ml|}];
          (componentWillMount props)
        })
        componentDidMount::(fun () => {
          let props = [%bs.raw{|this.props.ml|}];
          (componentDidMount props)
        })
        shouldComponentUpdate::(fun nextProps nextState => {
          let mlProps = getMl nextProps;
          let mlState = getMl nextState;
          let props = [%bs.raw{|this.props.ml|}];
          let state = [%bs.raw{|this.state.ml|}];
          (shouldComponentUpdate mlProps mlState props state)
        } [@bs])
        render::(fun () => {
          let props = [%bs.raw{|this.props.ml|}];
          let state = [%bs.raw{|this.state.ml|}];
          let this = [%bs.raw{|this|}];
          (render props state (setMlState this))
        })
        ()
      );
      fun key::key=? props => (createEmptyElement component (
        switch key {
          | Some x => (makeJsProps key::x ml::props ())
          | None => (makeJsProps ml::props ())
        }
      ))
    };

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

  external set_props_children : domConfig => 'children => unit = "children" [@@bs.set];
  let createDOMElement = fun tag config children => {
    set_props_children config (js_children children);
    createEmptyElement tag (convertProps config);
  };

  let button = createDOMElement "button";
  let div = createDOMElement "div";
  let span = createDOMElement "span";
  let input = createDOMElement "input";

};

let module Aphrodite = {
  type style;
  external _t: string => ReactStar.jsStyleObj => style = "window.createStyle" [@@bs.val];
  external css: style => string = "css" [@@bs.val] [@@bs.module "aphrodite"];
  let style = fun name css => _t name (ReactStar.makeStyle css);
};

let module Styles = {
  let style = Aphrodite.style;
  let cssStyle = ReactStar.cssStyle;
  let box = ReactStar.box;

  let button = style "button" (cssStyle
    padding::(box all::10 ())
  ());
  let container = style "container" (cssStyle
    padding::(box all::10 ())
  ());
  let counter = style "counter" (cssStyle
    padding::(box all::10 ())
    backgroundColor::"#eee"
  ());
  let todoView = style "todoView" (cssStyle
    flexDirection::"row"
    padding::(box horizontal::10 vertical::5 ())
  ());
  let filterView = style "filterView" (cssStyle
    flexDirection::"row"
    justifyContent::"center"
  ());
  let filter = style "filter" (cssStyle
    padding::(box horizontal::10 vertical::5 ())
    cursor::"pointer"
  ());
};

open ReactStar;
let css = Aphrodite.css;

type myProps = {initialCount: int};
type myState = {count: int};

let counter = (React.createStatefulComponent
  getInitialState::(fun props => {
    {count: props.initialCount}
  })
  (fun props state setState => {
    (React.button
      (React.domProps
        className::(css Styles.counter)
        onClick::(fun () => {
          setState {count: state.count + 1}
        })
        style::(makeStyle(cssStyle
          backgroundColor::"red"
          ()
        ))
        ()
      )
      (Children [(Text "Hello things "), (Int state.count)]))
  })
);

type filter =
  | All
  | NotDone
  | Done;
type todo = {title: string, completed: bool, id: int};

type todoViewProps = {todo: todo, onToggleCompleted: unit => unit};
type todoViewState = {editing: bool, editText: string};
let todoView = (React.createStatefulComponent
  getInitialState::(fun props => {
    {editing: false, editText: props.todo.title}
  })
  (fun props state setState => {
    (React.div
      (React.domProps
        className::(css Styles.todoView)
        ()
      )
      (Children
        [
          (ReactElement (React.input
            (React.domProps
              _type::"checkbox"
              checked::(props.todo.completed)
              onChange::(fun () => props.onToggleCompleted())
              ()
            )
            Empty
          )),
          (Text props.todo.title)
        ]
      )
    )
  })
);

let toggleTodo = fun todos id =>
  List.map
  (fun todo =>
    if (id == todo.id) {
      {...todo, completed: not todo.completed}
    } else {
      todo
    }
  )
  todos;

type todoListViewProps = {todos: list todo, onToggle: int => unit};
let todoListView = (React.createComponent
  (fun props => {
    (React.div
      (React.domProps
      ())
      (Children
        (List.map
          (fun todo =>
            (ReactElement
              (todoView key::(Printf.sprintf "todo-%d" todo.id) {
                todo: todo,
                onToggleCompleted: fun () =>
                  props.onToggle todo.id
              })))
          props.todos
        )
      )
    )
  })
);

let filterName = fun filter =>
switch (filter) {
  | All => "All"
  | Done => "Done"
  | NotDone => "Not Done";
};

type filterViewProps = {filter: filter, onChange: filter => unit};
let filterView = (React.createComponent
  (fun props => {
    (React.div
      (React.domProps
        className::(css Styles.filterView)
      ())
      (Children
        (List.map
        (fun filter =>
          ReactElement (React.div
            (React.domProps
              className::(css Styles.filter)
              onClick::(fun () => props.onChange filter)
              style::(makeStyle(cssStyle
                backgroundColor::(filter === props.filter ? "red" : "white")
              ()))
            ())
            (Text (filterName filter))
          )
        )
        [All, Done, NotDone])
      )
    )
  })
);

type todoListProps = {initialTodos: list todo};
type todoListState = {todos: list todo, filter: filter};
let todoList = (React.createStatefulComponent
  getInitialState::(fun props => {
    {todos: props.initialTodos, filter: All}
  })
  (fun props state setState => {
    (React.div
      (React.domProps
        className::(css Styles.container)
        ()
      )
      (Children
      [
        ReactElement (todoListView {
          todos:
            (switch (state.filter) {
              | All => state.todos
              | Done => (List.filter (fun todo => todo.completed) state.todos)
              | NotDone => (List.filter (fun todo => not todo.completed) state.todos)
            }),
          onToggle: fun id =>
            setState {...state, todos: toggleTodo state.todos id}
        }),
        ReactElement (filterView {
          filter: state.filter,
          onChange: fun filter => setState {...state, filter},
        })
      ])
    )
  })
);

let renderExample = fun () => {
  print_endline "hello reason + reactjs + bucklescript!";
  React.render
  (React.div
    (React.domProps ())
    (Children
    [
      (Text "Hello reason + reactjs + bucklescript!"),
      (ReactElement (counter {initialCount: 10})),
      (ReactElement
        (todoList {
          initialTodos: [
            {id: 0, title: "Use reason", completed: true},
            {id: 1, title: "Use react", completed: true},
            {id: 2, title: "Use bucklescript", completed: true},
            {id: 3, title: "Profit", completed: false},
          ]
        })
      )
    ])
  )
  (React.getElementById "container");
};
