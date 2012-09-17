var lastTime;

function initTimer() {
   lastTime = {};
}

function startTimer(key) {
   var d = new Date();
   lastTime[key] = d.getTime();
}

function lap(key) {
   if (lastTime[key]) {
     var d = new Date();
     var time = d.getTime();
     var result = time - lastTime[key];
     return result; 
   } else {
     return 0;
   } 
}

function stopTimer(key) {
   var result = lap(key);
   delete lastTime[key];
   return result;
}

initTimer();
