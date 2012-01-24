function a() {
   connect('localhost');

   var n = { name: 'John',
				 lastName: 'Smith',
             inner: {
                       a: '1',
                       b: '2'
                    }  
            };

   insert('ns', n);

   print("inserted");
   
  var t = { name: 'John' };
   
   print('doing search');
   var result = find('ns', t);
   print(result);
}

a();
