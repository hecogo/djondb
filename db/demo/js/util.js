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
