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