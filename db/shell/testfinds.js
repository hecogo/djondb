connect('localhost');

// inserts
//
var total = 10000;
var pr = total / 10;
for (var x = 0; x < total; x++) {
	if ((x % pr) == 0) {
		print(x);
	}
	insert("test.perf", "{_id: '" + uuid() + "', name: 'John', lastName: 'Smith'}");
}
