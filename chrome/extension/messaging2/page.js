/**
 * 
 */

chrome.runtime.onConnect.addListener(function(port){
    port.onMessage.addListener(function(msg){
        port.postMessage({counter: msg.counter + 1});
    });
});

chrome.runtime.onMessage.addListener(function(request, sender, response){
    response({counter: request.counter+1});
});

window.addEventListener("message", function(event) {
    // only accept messages from ourselves
    if(event.source !== window) {
        return;
    }
    if(event.data.type && event.data.type === 'novemberizing') {
        console.log('content received ' + event.data.text);
    }
});