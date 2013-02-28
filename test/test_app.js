var ui = require("../lib/ui");

console.log(ui.App);

var app = new ui.App();
var window = new ui.Window();

app.addWindow(window);
setTimeout(function() {
	app.removeWindow(window);
}, 1000);
