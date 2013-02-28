var View = require("./View");

/**
 * Represents a top level window.
 * 
 * @class Button
 * @extends View
 * @constructor
 */
function Button() {
	View.call(this, "Button");
}

Button.prototype.__proto__ = View.prototype;

module.exports = Button;