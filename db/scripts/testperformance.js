load('random.js');
connect('localhost');
var r = generate(100000);
insertInDb(r);

print(find('db', 'test'));
