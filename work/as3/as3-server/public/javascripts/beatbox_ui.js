"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {


    
	// Setup a repeating function (every 1s)
	window.setInterval(function() {
        sendRequest('uptime')
        sendDataRequest("volume");
        sendDataRequest("tempo");
    }, 1000);


    //Handle button clicks
	$('#modeNone').click(()=>{sendDataRequest("mode 0");});
	$('#modeRock1').click(() => {sendDataRequest("mode 1");});
	$('#modeRock2').click(()=>{sendDataRequest("mode 2");});
	$('#volumeDown').click(() =>{sendDataRequest("volume down");});
	$('#volumeUp').click(()=>{sendDataRequest("volume up");});
    $('#tempoDown').click(() =>{sendDataRequest("tempo down");});
    $('#tempoUp').click(() => {	sendDataRequest("tempo up")});
	
	
	
	socket.on('commandReply', function(result) {
		console.log("Recieved: "+ result);
	});
	
});

function sendDataRequest(message) {
	console.log("Requesting '" + message + "'");
	socket.emit('data', message);
};

function sendRequest(file) {
	console.log("Requesting '" + file + "'");
	socket.emit('proc', file);
}

