// GENERATED CODE BY BUCKLESCRIPT VERSION 0.9.0 , PLEASE EDIT WITH CARE
'use strict';

var Block    = require("bs-platform/lib/js/block");
var ReactDom = require("react-dom");
var Curry    = require("bs-platform/lib/js/curry");
var Printf   = require("bs-platform/lib/js/printf");
var $$Array  = require("bs-platform/lib/js/array");
var React    = require("react");

var oldCounter = React.createClass({
      getInitialState: function () {
        return {
                count: 2
              };
      },
      render: function () {
        console.log("rendering");
        var count = (this.state.count);
        var $$this = (this);
        return React.createElement("button", {
                    onClick: function () {
                      return $$this.setState({
                                  count: count + 1 | 0
                                });
                    }
                  }, Curry._1(Printf.sprintf(/* Format */[
                            /* String_literal */Block.__(11, [
                                "Hello ",
                                /* Int */Block.__(4, [
                                    /* Int_d */0,
                                    /* No_padding */0,
                                    /* No_precision */0,
                                    /* End_of_format */0
                                  ])
                              ]),
                            "Hello %d"
                          ]), count));
      }
    });

function noop() {
  return /* () */0;
}

function setMlState($$this, state) {
  return $$this.setState({
              ml: state
            });
}

function createStatefulComponent(getInitialState, _, _$1, render) {
  var component = React.createClass({
        getInitialState: function () {
          var props = (this.props.ml);
          return {
                  ml: Curry._1(getInitialState, props)
                };
        },
        render: function () {
          var props = (this.props.ml);
          var state = (this.state.ml);
          var $$this = (this);
          return Curry._3(render, props, state, function (param) {
                      return $$this.setState({
                                  ml: param
                                });
                    });
        }
      });
  return function (props) {
    return React.createElement(component, {
                ml: props
              });
  };
}

function js_children(children) {
  if (typeof children === "number") {
    return window.identity((null));
  }
  else {
    switch (children.tag | 0) {
      case 0 : 
      case 1 : 
      case 2 : 
      case 3 : 
          return window.identity(children[0]);
      case 4 : 
          return window.identity($$Array.map(js_children, $$Array.of_list(children[0])));
      
    }
  }
}

function createDOMElement(tag, config, $staropt$star, _) {
  var children = $staropt$star ? $staropt$star[0] : /* Empty */0;
  config.children = js_children(children);
  return React.createElement(tag, config);
}

function button(param, param$1, param$2) {
  return createDOMElement("button", param, param$1, param$2);
}

var counter = createStatefulComponent(function (props) {
      return /* record */[/* count */props[/* initialCount */0]];
    }, /* None */0, /* None */0, function (_, state, setState) {
      return React.createElement("button", {
                  onClick: function () {
                    return Curry._1(setState, /* record */[/* count */state[/* count */0] + 1 | 0]);
                  }
                }, Curry._1(Printf.sprintf(/* Format */[
                          /* String_literal */Block.__(11, [
                              "Hello ",
                              /* Int */Block.__(4, [
                                  /* Int_d */0,
                                  /* No_padding */0,
                                  /* No_precision */0,
                                  /* End_of_format */0
                                ])
                            ]),
                          "Hello %d"
                        ]), state[/* count */0]));
    });

function renderExample() {
  console.log("hello reason + reactjs + bucklescript!");
  ReactDom.render(counter(/* record */[/* initialCount */10]), document.getElementById("container"));
  return /* () */0;
}

exports.oldCounter              = oldCounter;
exports.noop                    = noop;
exports.setMlState              = setMlState;
exports.createStatefulComponent = createStatefulComponent;
exports.js_children             = js_children;
exports.createDOMElement        = createDOMElement;
exports.button                  = button;
exports.counter                 = counter;
exports.renderExample           = renderExample;
/* oldCounter Not a pure module */
