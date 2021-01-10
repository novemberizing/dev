
console.log("send runtime id");

chrome.runtime.onConnect.addListener(function(port){
    console.log("page", "connect");
    port.onMessage.addListener(function(message){
        console.log(message);
    });
});

chrome.runtime.onMessage.addListener(function(request, sender, response){
    console.log(request);
    response("world");
});

window.postMessage({id: chrome.runtime.id}, '*');
