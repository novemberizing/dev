function setChildTextNode(elementId, text) {
    document.getElementById(elementId).innerText = text;
}

function testMessage() {
    setChildTextNode("resultsRequest", "running...");

    chrome.tabs.query({ active: true, currentWindow: true}, function(tabs) {
        var tab = tabs[0];
        chrome.tabs.sendMessage(tab.id, {counter:1}, function handler(response){
            if(response.counter < 1000) {
                chrome.tabs.sendMessage(tab.id, {counter: response.counter}, handler);
            } else {
                setChildTextNode("resultsRequest", " usec");
            }
        });
    });
}

function testConnect() {
    setChildTextNode("resultsConnect", "running...");

    chrome.tabs.query({active: true, currentWindow: true}, function(tabs){
        var port = chrome.tabs.connect(tabs[0].id);
        port.postMessage({counter: 1});
        port.onMessage.addListener(function getResp(response){
            if(response.counter < 1000) {
                port.postMessage({counter: response.counter});
            } else {
                setChildTextNode("resultsConnect", "usec");
            }
        });
    });
}

(function(){
    // if (!chrome.benchmarking) {
    //   alert("Warning:  Looks like you forgot to run chrome with " +
    //         " --enable-benchmarking set.");
    //   return;
    // }
    document.addEventListener('DOMContentLoaded', function() {
      document.querySelector('#testMessage').addEventListener(
          'click', testMessage);
      document.querySelector('#testConnect').addEventListener(
          'click', testConnect);
    });
  })();