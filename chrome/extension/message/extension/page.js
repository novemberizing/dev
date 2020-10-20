
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

// window.addEventListener("message", function(event){
//     console.log("receive runtime id");
//     console.log(event);
//     console.log(event.data.id);
//     if(event.data.id) {
//         chrome.runtime.sendMessage(event.data.id, "hello", function(response){
//             console.log(response);
//         });
//     }
// }, false);

window.postMessage({id: chrome.runtime.id}, '*');
