var View = require("./View");

/**
 * Represents a top level window.
 * 
 * @class Window
 * @extends View
 * @constructor
 */
function Window() {
	View.call(this, "Window");
}

Window.prototype.__proto__ = View.prototype;

module.exports = Window;