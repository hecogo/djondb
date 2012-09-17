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
connect('localhost', 9876);
//connect('ec2-50-16-108-156.compute-1.amazonaws.com');

var r = generate(100);
print("starting inserts");
insertInDb(r);
