console.log("BLOCK GAME <3");

var Spielfeld = document.getElementById("Spielfeld");
var Block = document.getElementById("Block");

Block.style.top = "100px";
Block.style.left = "100px";

var getBlockStyle = getComputedStyle(Block); //LEsen style von Block

window.addEventListener("keypress", move);

function move(event) {

    var speed = 30;
    var top = 0;
    var left = 0;

    if (event.key == 's') {
        console.log("ArrowDown is pressed");
        top = speed;
    }
    if (event.key == 'w') {
        console.log("ArrowUp  is pressed");
        top = -speed;
    }
    if (event.key == 'a') {
        console.log("ArrowLeft  is pressed");
        left = -speed;
    }
    if (event.key == 'd') {
        console.log("ArrowRight  is pressed");
        left = speed;
    }

    Block.style.top = (parseInt(getBlockStyle.top) + top) + "px";
    Block.style.left = (parseInt(getBlockStyle.left) + left) + "px";
}