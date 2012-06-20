load('random.js');
connect('localhost');
var r = generate(100000);
print("starting inserts");
insertInDb(r);

