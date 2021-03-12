"use strict";
// Client-side interactions with the browser.
var bbgError;
var serverError;
// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	// $(errorbox).hide();

	// Setup a repeating function (every 1s)
	window.setInterval(function() {
		sendStatusRequest();
        sendRequest('uptime')
        sendRequest("volume");
		sendRequest("tempo");
		sendRequest("mode");
    }, 1000);

	window.setInterval(()=>{
		bbgError = setTimeout(()=>{
			$(errorbox).show();
			$("#error-text").text("Beagle bone is not responding, make sure the app is running")
		},3000);

		serverError = setTimeout(()=>{
			$(errorbox).show();
			$("#error-text").text("Server is not responding, make sure it is running")
		},3000);
	},4000);


    //Handle button clicks
	$('#modeNone').click(()=>{sendRequest("mode 0");});
	$('#modeRock1').click(() => {sendRequest("mode 1");});
	$('#modeRock2').click(()=>{sendRequest("mode 2");});
	$('#volumeDown').click(() =>{sendRequest("volume down");});
	$('#volumeUp').click(()=>{sendRequest("volume up");});
    $('#tempoDown').click(() =>{sendRequest("tempo down");});
    $('#tempoUp').click(() => {	sendRequest("tempo up")});
	$('#hihat').click(()=>{sendRequest("hihat");});
	$('#snare').click(()=>{sendRequest("snare");});
	$('#bass').click(()=>{sendRequest("bass");});
		

	socket.on('serverStatus', function(){
		console.log("Server timer cleared");
		clearTimeout(serverError);
		$(errorbox).hide();
	});
	

	socket.on('commandReply', function(result) {
		//Set the appropriate fields 
		var resp = result.split("\n")[0];
		var [tag, data] = resp.split(":");
		console.log(tag, data);

		clearTimeout(bbgError);
		$(errorbox).hide();
		// clearTimeout(timeout);
		switch (tag) {
			case "volume":
				$(volumeid).val(data)
				break;
			case "uptime":
				data = data.split(' ')[0];
				var hour = Math.floor(data/ 3600);
				var minute = Math.floor((data - (hour * 3600)) / 60);
				var second = (data - (hour * 3600) - (minute * 60)).toFixed(2);

				hour = hour < 10 ? "0" + hour : hour;
				minute = minute < 10 ? "0" + minute: minute;
				second = second < 10 ? "0" + second: second;
			
				var time = hour + ":" + minute +":" + second+"(H:M:S:ms)"
				console.log(time)
				$(uptime).text(time)
				break
			case "mode":
				var mode = "None"
				if (data === "1"){
					mode = "Rock #1"
				}
				if (data === "2"){
					mode = "Custom Mode"
				}
				$(modeid).text(mode)
				break
			case "tempo":
				$(tempoid).val(data)
				break;
		}
	});
});


function sendStatusRequest(){
	socket.emit("status","server status");
}

function sendRequest(file) {
	// console.log("Requesting '" + file + "'");
	socket.emit('update', file);
}

