set -e
echo "start"
opam pin add -y jenga https://github.com/chenglou/jenga.git#5014bf62bb15fc9649debf214c4f5c3ef54f4682
opam install -y js_of_ocaml
opam install -y yojson
opam install -y ocamlfind
opam pin add -y reactjs git@github.com:fxfactorial/ocaml-reactjs.git
echo "done"
