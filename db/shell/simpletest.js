function test(server) {
	connect(server);
	var customer = 
		{ 
			name: "John", 
			lastName: "Smith", 
			address: 
			{
				phone: "555-555-555",
				home: "Avenue 1 111"
			},
			personal:
			{
				age: 38,
				married: true
			}
		};
	insert('testdb', 'customer', customer);
	
	var o = find('testdb', 'customer');
	if (!o) {
		print('Houston we have a problem!');
		return;
	}

	o = find('testdb', 'customer', '$"personal.age" > 30');
	if (!o) {
		print('Houston the filter is not running abort mission!');
		return;
	}
	if (o.length == 0) {
		print('Houston: find is nowhere land!');
		return;
	}

	o = find('testdb', 'customer', '$"name", $"personal.age"', '$"personal.age" > 30');
	if (!o) {
		print('Houston: Our boy has no name and looks like is an unborn baby');
		return;
	}
	
	print('Hey Houston: The rocket is on and running, congrats to the team');

}

