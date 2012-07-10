function insertInDb(r) {
   startTimer("insert");
   for (var x = 0; x < r.length; x++) {
      var e = r[x];
      db.test.insert(e);
   }
   var t = stopTimer("insert");
   var ops = r.length / t;
   print("Time: " + t + ", op x millisec: " + ops * 1000);
}

load('random.js');
print("starting inserts");

var r = generate(100000);
print("starting inserts");
insertInDb(r);
