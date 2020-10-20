console.log("background");

chrome.runtime.onConnectExternal.addListener(function(port){
    console.log("webpage connect");
    port.onMessage.addListener(function(request, sender, response){
        console.log(request);
    });
});

chrome.runtime.onMessageExternal.addListener(function(request, sender, response){
    console.log(request);
    response("world");
});


