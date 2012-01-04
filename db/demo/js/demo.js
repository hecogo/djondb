function preparePost() {
	var post = $("#post");

	$("<label>Elige el tipo de anuncio</label>").appendTo(post);

	var sel = $("<select></select>");
	sel.appendTo(post);

	$("<option value='1'>Venta de casa</option>").appendTo(sel);
}

$(document).ready(function() {
		preparePost();
});
