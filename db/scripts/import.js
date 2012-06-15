load('csv.js');

function readFile(file) {
   var f = read(file);
   var array = CSVToArray(f, ',');
   return array;
}

function jsonFromFile(file) {
   var arr = readFile(file);
   var result = [];
   var headers = arr[0];
   for (var x = 1; x < arr.length; x++) {
      var i = arr[x];
      var row = {};
      for (var y = 0; y < i.length; y++) {
   	row[headers[y]] = arr[x][y];
      }
      result.push(row);
   }
   return result;
}

function imp(file, db, ns) {
   connect('localhost');
   var json = jsonFromFile(file);
   for (var x = 0; x < json.length; x++) {
       var row = json[x];
       insert(db, ns, row); 
   }
}
