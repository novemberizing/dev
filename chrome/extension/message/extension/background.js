console.log("background");

console.log(chrome.runtime.connectNative);

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

console.log("hello world");
port = chrome.runtime.connectNative('com.google.chrome.example.echo');

console.log(port);

port.postMessage('hello');

// chrome.runtime.sendNativeMessage('com.google.chrome.example.echo', "message", function(response){
//     console.log(response);
// });

/**
let connection = chrome.runtime.connectNative('com.google.chrome.example.echo');
console.log(connection);

connection.onMessage.addListener(function(message){
    console.log(message);
});

connection.onDisconnect.addListener(function(){
    console.log("disconnected");
});
*/
