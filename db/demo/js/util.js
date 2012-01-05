(function($) {
 $.QueryString = (function(a) {
	 if (a == "") return {};
	 var b = {};
	 for (var i = 0; i < a.length; ++i)
	 {
	 var p=a[i].split('=');
	 if (p.length != 2) continue;
	 b[p[0]] = decodeURIComponent(p[1].replace(/\+/g, " "));
	 }
	 return b;
	 })(window.location.search.substr(1).split('&'))
 })(jQuery);


function addRow(parentDiv, label, control) {
	var p = $("<P />").appendTo(parentDiv);
	var lbl = $("<label />");
	lbl.text(label);
	lbl.appendTo(p);
	control.appendTo(p);
}

function addOption(sel, val, text) {
	var option = $("<option />");
	option.val(val);
	option.text(text);
	option.appendTo(sel);
}
