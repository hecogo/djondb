function prepareShow() {
	var show = $("#show");

	var type = $.QueryString['type'];
	$.ajax({
		url: 'show.php?type=' + type,
		type: 'POST',
		context: document.body

	})
	.done(function(data) {
		data = jQuery.parseJSON(data);
		var table = $("<table />").appendTo(show);
		var tr = $("<tr />").appendTo(table);
		$("<th>Title</th>").appendTo(tr);
		$("<th>Price</th>").appendTo(tr);
		$("<th>Place</th>").appendTo(tr);
		$("<th>Description</th>").appendTo(tr);
		if (type == "1") {
			$("<th>Rooms</th>").appendTo(tr);
			$("<th>Area</th>").appendTo(tr);
			$("<th>Floor</th>").appendTo(tr);
		}

		$.each(data, function(index, elem) {
			var row = $("<tr />").appendTo(table);	
			$("<td>" + elem.title + "</td>").appendTo(row);
			$("<td>" + elem.price + "</td>").appendTo(row);
			$("<td>" + elem.place + "</td>").appendTo(row);
			$("<td>" + elem.description + "</td>").appendTo(row);
			var rooms = $("<td></td>").appendTo(row);
			var area = $("<td></td>").appendTo(row);
			var floor = $("<td></td>").appendTo(row);
			if (elem.rooms) {
				$("<div>" + elem.rooms + "</div>").appendTo(rooms);
			}
			if (elem.area) {
				$("<div>" + elem.area + "</div>").appendTo(area);
			}
			if (elem.pisos) {
				$("<div>" + elem.pisos + "</div>").appendTo(floor);
			}
			if (elem.area) {
				$("<div>" + elem.area + "</div>").appendTo(area);
			}
		});
	});

}

$(document).ready(function() {
	prepareShow();
});
