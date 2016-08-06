set -e
echo "start"
# opam switch remove reason
# opam switch -A system reason
opam update

opam pin add -y merlin 'https://github.com/the-lambda-church/merlin.git#reason-0.0.1'
opam pin add -y merlin_extend 'https://github.com/let-def/merlin-extend.git#reason-0.0.1'
opam pin add -y jenga https://github.com/chenglou/jenga.git#5014bf62bb15fc9649debf214c4f5c3ef54f4682
opam pin add -y reason 'https://github.com/facebook/reason.git#0.0.6'
opam install -y js_of_ocaml
opam install -y yojson
opam install -y ocamlfind
opam pin add -y reactjs git@github.com:fxfactorial/ocaml-reactjs.git
echo "done"
