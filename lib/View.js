var n = require("../build/Debug/ui_native");

/**
 * @class ui.View
 * @constructor
 * @param {Handle} handle
 */
function View(class_name) {
	this.handle = n.view.create(class_name);
}

/**
 * Wakes up the view.
 * 
 * @method wake
 * @return {Boolean} True if successful. 
 */
View.prototype.wake = function() {
	return n.view.wake(this.handle);
}

/**
 * Sleeps the view.
 * 
 * @method wake
 * @return {Boolean} True if successful. 
 */
View.prototype.sleep = function() {
	return n.view.sleep(this.handle);
}

/**
 * Sets bounds of the view.
 * 
 * @param {Number} left
 * @param {Number} top
 * @param {Number} right
 * @param {Number} bottom
 * @return {Boolean} True if successful.
 */
View.prototype.setBounds = function(left, top, right, bottom) {
	return n.view.setBounds(this.handle, left, top, right, bottom);
}


/**
 * Adds a child view to this view.
 * 
 * @param {ui.View} child
 * @return {ui.View} Returns the same child.
 */
View.prototype.addChild = function(child) {
	n.view.addChild(this.handle, child.handle);
	return child;
}

/**
 * Attachs event listener to the view.
 * 
 * @method on
 * @param {String} event Name of the event to listen for.
 * @param {Function} callback Callback to call.
 */
View.prototype.on = function(event, callback) {
	throw "Not implemented";
}

module.exports = View;