var jsontemplate = {
    "name": "$text(10)",
    "lastName": "$text(10)",
    "age": "$number"
};

function init() {
	if (typeof String.prototype.startsWith != 'function') {
  		String.prototype.startsWith = function (str){
	 		return this.indexOf(str) == 0;
  		};
	}
}

function clone(o) {
	var r = {};
	for (var n in o) {
		 r[n] = o[n];
	}
	return r;
}

function randomText(t) {
	var r = "";
	for (var n = 0; n < 10; n++) {
		var c = Math.random()*22;
		r += String.fromCharCode(c+97);
	}
	return r;
}

function value(v) {
	if (v.startsWith("$text")) {
	    v = randomText(10);
	} else if (v.startsWith("$number")) {
	    v = Math.round(Math.random()*20);
	} else {
	    v = n;
	}
	return v;
}


function generate(count) {
	var r = [];
	for (var x = 0; x < count; x++) {
		var o = clone(jsontemplate);
		for (var n in o) {
			var v = o[n];
			o[n] = value(v);
		}
		r.push(o);
	} 

	return r;
}

function insertInDb(r) {
   for (var x = 0; x < r.length; x++) {
      var e = r[x];
      insert('db', 'test', e);
   }
}

init();

