var aphrodite = require('aphrodite');
window.createStyle = (name, defn) => {
  var obj = {}
  obj[name] = defn
  return aphrodite.StyleSheet.create(obj)[name]
}

window.identity = x => x;
window.convertProps = props => {
  if (!props._type) return props;
  props.type = props._type
  delete props._type
  return props
}
window.fixKey = props => {
  if (props.key === "") {
    delete props.key
  }
  return props
}
require('./moreact').renderExample();
