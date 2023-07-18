(function() {
  var ws = new WebSocket("ws://localhost:35729");
  ws.onmessage = function(msg) {
    if ((JSON.parse(msg.data)).command == "reload") {
      window.location.reload();
    }
  };

})();
