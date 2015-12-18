$(document).ready(function () {
	// hydrate the app's state
	$.getJSON('/api/tree/state', function(data) {
		$("#s1").prop('checked', data.on);
	});

	$("#s1").change(function () {
		console.log(this.checked);
		$.ajax({
			url: '/api/tree/state',
			method: 'POST',
			data: JSON.stringify({on: this.checked}),
			dataType: 'json',
			contentType: 'application/json'
		});
	});
});