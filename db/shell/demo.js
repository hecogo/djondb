function execute() {
   connect('localhost');

   var a = {
        name: 'test',
        lastName: 'last'
	};

  insert('space', a);
  acomplex = {
        name: 'test',
        lastName: 'last',
		  inner: {
			  innerName: 'iName',
			  innerLastName: 'iLastName'
		  }

	};

  insert('space', acomplex);

  var temp = find('space', { name: 'test' });

  print("Found ", temp);
}

execute();
