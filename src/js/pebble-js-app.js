/*global window */
var CONSOLELOG = 0;
var config_url = "http://lennynero.github.io/pebble/sortrevolution-conf-2.0.2.html?v=2.0.2";

Pebble.addEventListener("ready", function (e) {
	if(CONSOLELOG){console.log("Connect to PebbleKit JS! " + e.ready);}
	//Pebble.sendAppMessage({"message": "PebbleKit JS ready"});
});

Pebble.addEventListener("showConfiguration", function () {
	var url = config_url;
       
	/*if(typeof(Storage) !== "undefined"){
      var sortrevolution = window.localStorage.getItem("sortrevolution");
      if(sortrevolution !== null) {
        var localOptions = JSON.parse(sortrevolution);
        
		for(var key in localOptions) {
          var val = localOptions[key];
			
            if(val !== null) {
              url += "&" + encodeURIComponent(key) + "=" + encodeURIComponent(val);
           }
        }
      }
	}*/
	Pebble.openURL(url);
});

Pebble.addEventListener("appmessage",
  function(e) {
    console.log("Received message: " + e.payload);
  }
);

Pebble.addEventListener("webviewclosed", function (e) {
    if (e.response) { // user clicked Save/Submit, not Cancel/Done
        var newOptions = JSON.parse(decodeURIComponent(e.response));
		//newOptions = {"0" : 1, "1" : 1, "2" : 1};
		if(CONSOLELOG){console.log("New Options = " + JSON.stringify(newOptions));}
		
		if(typeof(Storage) !== "undefined"){
          window.localStorage.setItem("sortrevolution", JSON.stringify(newOptions));
		}
		Pebble.sendAppMessage(newOptions,
            function (e) {
				if(CONSOLELOG){console.log("Successfully delivered message with transactionId=" + e.data.transactionId);}
            },
            function (e) {
				if(CONSOLELOG){console.log("Unable to deliver message with transactionId=" + e.data.transactionId + " Error is: " + e.data.error.message);}
            }
        );
    }
});