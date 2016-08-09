# Reasonml + Reactjs experimentation

I tried three different ways of using react from reason.

1. direct port, lots of js munging
2. functional style






## Two options: jsoo & bucklescript

- js_of_ocaml is the more established player, and more things know about &
  support it (such as the `jengaboot` build system)
- bucklescript is newer, more shiny, generates dramatically better javascript,
  and has much prettier documentation :)

I present both for comparison, but I'll mostly be investing in bucklescript
for the moment.

## General setup

I recommend starting a new opam switch, via ex `opam switch -A system reason`
(reason is the name of our new environment).

Then run `./install_reason.sh` to install the opam packages for reason.

> NOTE: I think there's a better way to do this (there's an npm package?) but
> I haven't gotten there yet.

Other dependencies:

- `npm install -g watch`
- `opam pin add -y BetterErrors https://github.com/chenglou/BetterErrors.git`

## Bucklescript

`cd buckle && npm install`

## JS_OF_OCAML

`cd jsoo && ./setup_opam.sh && npm install`

## Hacking
Go to the subdirectory of your choice

- `webpack --watch`
- `watch make src --wait=.1 --interval=.1`

Now it will recompile js + webpack whenever you change things!

Go ahead and open `index.html` in your favorite browser to see the fruits of
your labors!
