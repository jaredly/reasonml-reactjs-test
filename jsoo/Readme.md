# Reasonml + Reactjs experimentation

## Opam setup

If you haven't setup opam w/ everything yet, do this:
```
# Create a new opam environment because packaging is hard
opam switch -A system reason
eval `opam config env`
# Install all the ocaml things we need
./setup_opam.sh
```

## Install requried node packages

```
# Install the node stuff!
npm install
```

## Hacking

- run `webpack --watch`

get the watch utility (`npm i -g watch`) and then:

- `watch ./node_modules/.bin/compile src --wait=.1 --interval=.1`

Now it will recompile js + webpack whenever you change things!

Go ahead and open `index.html` in your favorite browser to see the fruits of
your labors!

