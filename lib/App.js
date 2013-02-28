function App() {
	this.windows = [];
}

App.prototype.addWindow = function(window) {
	this.windows.push(window);
	console.log(this.windows);
	window.wake();
	return window;
}

App.prototype.removeWindow = function(window) {
	var i = this.windows.indexOf(window);
	this.windows.splice(i, 1);
	console.log(this.windows, window);
	window.sleep();
	return window; 
}

module.exports = App;