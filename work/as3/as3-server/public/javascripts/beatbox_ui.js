"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {


    
	// Setup a repeating function (every 1s)
	window.setInterval(function() {
        sendRequest('uptime')
        sendRequest("volume");
        sendRequest("tempo");
    }, 1000);


    //Handle button clicks
	$('#modeNone').click(()=>{sendRequest("mode 0");});
	$('#modeRock1').click(() => {sendRequest("mode 1");});
	$('#modeRock2').click(()=>{sendRequest("mode 2");});
	$('#volumeDown').click(() =>{sendRequest("volume down");});
	$('#volumeUp').click(()=>{sendRequest("volume up");});
    $('#tempoDown').click(() =>{sendRequest("tempo down");});
    $('#tempoUp').click(() => {	sendRequest("tempo up")});
		
	
	socket.on('commandReply', function(result) {
        console.log("Recieved: "+ result);
        //Set the appropriate fields 
	});
	
});


function sendRequest(file) {
	console.log("Requesting '" + file + "'");
	socket.emit('update', file);
}

