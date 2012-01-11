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
		$.each(data, function(index, elem) {
			var row = $("<tr />").appendTo(table);	
			$("<td>" + elem.title + "</td>").appendTo(row);
			$("<td>" + elem.price + "</td>").appendTo(row);
			$("<td>" + elem.place + "</td>").appendTo(row);
		});
	});

}

$(document).ready(function() {
	prepareShow();
});
