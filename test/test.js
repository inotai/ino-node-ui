var ui = require("../lib/ui");

var window1 = new ui.Window();
window1.setBounds(100, 100, 200, 200);

var window2 = new ui.Window();
window2.setBounds(200, 200, 300, 300);

var button = new ui.Button();
button.setBounds(10, 10, 90, 40);


window1.addChild(button);
window1.wake();
window2.wake();
window2.addChild(button);

// window.setBounds(0,0,100,100);
// // var button = window.addChild(new ui.Button("Button"));
// // button.setBounds(0,0,50,30);
// window.on("close", function() {
// 	return true;
// });
// console.log("wake");
// window.wake();
// console.log("close");
// window.close();
// setTimeout(function() {
// 	console.log("wake timeout");
// 	window.wake();
// }, 1000);