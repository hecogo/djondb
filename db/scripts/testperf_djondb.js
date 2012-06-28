function insertInDb(r) {
   startTimer("insert");
   for (var x = 0; x < r.length; x++) {
      var e = r[x];
      insert('db', 'test', e);
   }
   var t = stopTimer("insert");
   var ops = r.length / t;
   print("Time: " + t + ", op x millisec: " + ops * 1000);
}

load('random.js');
connect('localhost');

var r = generate(1000000);
print("starting inserts");
insertInDb(r);
