function loadPost(post, data) {
	post.empty();

	var title = $("<input id='title' type='text'>");
	addRow(post, 'Titulo:', title);
	var price = $("<input id='price' type='text'>");
	addRow(post, 'Precio:', price);
	var place = $("<input id='place' type='text'>");
	addRow(post, 'Lugar::', place);
	var descrip = $("<textarea id='description' />");
	addRow(post, 'Descripcion:', descrip);

	var button = $("<input type=button />");
	button.text('Submit');
	button.bind("click", function() {
		data.title = title.val();
		data.price = price.val();
		data.place = place.val();
		data.description = descrip.val();
		var entry = { data: data };
		$.ajax({
			url: "post.php",
			data: entry,
			type: 'POST',
			dataType: "json",
			context: document.body
		}).done(function(msg) {
			alert('done');
		});

	});
	button.appendTo(post);
}

function loadCategories(post, data) {
	post.empty();
	if (data.type == '2') {
		var sel = $("<select />");
		addOption(sel, 1, 'antiguedades');
		addOption(sel, 2, 'arte');
		addOption(sel, 3, 'bicicletas');
		addRow(post, 'Categoria:', sel);

		sel.bind("click", function() {
			data.category = sel.val();
			loadPost(post, data);
		});
	}	
}

function preparePost() {
	var post = $("#post");


	var sel = $("<select></select>");
	addOption(sel, 1, 'Venta de casa');
	addOption(sel, 2, 'Venta');
	addRow(post, 'Elige el tipo de anuncio', sel);

	var data = {}; // this will hold the post information
	sel.bind("click", function() {
		data.type = sel.val();
		loadCategories(post, data);
	});

}

$(document).ready(function() {
	preparePost();
});
