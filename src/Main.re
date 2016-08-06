
let obj = fun stuff => {
  let arr = (Array.of_list stuff);
  let conv = fun (key, value) => (key, Js.Unsafe.inject value);
  Js.Unsafe.obj (Array.map conv arr)
};

let set_state = fun this state => Js.Unsafe.meth_call this "setState" (Array.of_list [state]);

let get_state = fun this name => Js.Unsafe.get (Js.Unsafe.get this "state") (Js.string name);

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

let counter =
(Reactjs.make_class_spec
  initial_state::(fun this::this =>
    obj [("count", 2)])
  (fun this::this => {
    (Reactjs.DOM.make
      tag::`button
      elem_spec::(obj [
        ("onClick", fun () => set_state this (obj [("count", 1 + (get_state this "count"))]))
      ])
      [Text (Printf.sprintf "Hello more button: %d" (get_state this "count"))])
    })
  ) |> Reactjs.create_class;

Reactjs.(
  render
    react_elem::(create_element_from_class counter)
    (get_elem id::"container")
);

print_endline "Hello reason + jenga + dom";
