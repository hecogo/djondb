function loadResult(post, msg) {
	post.empty();

	$("<h1>Clasificado guardado</h1>").appendTo(post);

	$("<a href='index.html'>Home</a>").appendTo(post);
}

function loadHouseData(post, data) {
	post.empty();

	var title = $("<input id='title' class='title' type='text'>");
	addRow(post, 'Titulo:', title);
	var price = $("<input id='price' class='price money' type='text'>");
	addRow(post, 'Precio:', price);
	var place = $("<input id='place' class='text' type='text'>");
	addRow(post, 'Lugar:', place);
	var descrip = $("<textarea id='description' />");
	addRow(post, 'Descripcion:', descrip);

	var rooms = $("<input id='rooms' class='number'/>");
	addRow(post, 'Cuartos:', rooms);
	var area = $("<input id='area' class='number' />");
	addRow(post, 'Metros cuadrados:', area);
	
	var button = $("<input type=button value='Guardar' />");
	button.bind("click", function() {
		data.title = title.val();
		data.price = price.val();
		data.place = place.val();
		data.description = descrip.val();

		data.rooms = rooms.val();
		data.area = area.val();

		var entry = { data: data };
		$.ajax({
			url: "post.php",
			data: entry,
			type: 'POST',
			dataType: "json",
			context: document.body
		}).done(function(msg) {
			loadResult(post, msg);
		});

	});
	button.appendTo(post);
}

function loadPCData(post, data) {
	post.empty();

	var title = $("<input id='title' class='title' type='text'>");
	addRow(post, 'Titulo:', title);
	var price = $("<input id='price' class='price money' type='text'>");
	addRow(post, 'Precio:', price);
	var place = $("<input id='place' class='text' type='text'>");
	addRow(post, 'Lugar:', place);
	var descrip = $("<textarea id='description' />");
	addRow(post, 'Descripcion:', descrip);

	var button = $("<input type=button value='Guardar' />");
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
			loadResult(post, msg);
		});

	});
	button.appendTo(post);
}

function loadCategories(post, data) {
	post.empty();
	if (data.type == 'house') {
		var sel = $("<select />");
		addOption(sel, 'apartament', 'Apartamento');
		addOption(sel, 'house', 'Casa');
		addRow(post, 'Tipo de inmueble:', sel);

		sel.bind("click", function() {
			data.category = sel.val();
			loadHouseData(post, data);
		});
	}

	if (data.type == 'pc') {
		var sel = $("<select />");
		addOption(sel, 'laptop', 'Laptop');
		addOption(sel, 'desktop', 'PC de escritorio');
		addOption(sel, 'accesory', 'Accesorios');
		addRow(post, 'Categoria:', sel);

		sel.bind("click", function() {
			data.category = sel.val();
			loadPCData(post, data);
		});
	}	
}

function preparePost() {
	var post = $("#post");

	var sel = $("<select id='type'></select>");
	addOption(sel, 'house', 'Venta de Inmuebles');
	addOption(sel, 'computer', 'Venta de Computadores');
	addRow(post, 'Elige el tipo de articulo', sel);

	var data = {}; // this will hold the post information
	sel.bind("click", function() {
		data.type = sel.val();
		loadCategories(post, data);
	});

}

$(document).ready(function() {
	preparePost();
});
